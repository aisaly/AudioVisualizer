
#include <stdlib.h>
#include <GL/glut.h>
#include "fmod.hpp"
//#include <fmod_studio.h>
//#include <fmod_errors.h>
#include <iostream>



/// this is a pointer to the mp3 stream we will be reading from the disk.
//FSOUND_STREAM* g_mp3_stream = NULL;


//------------------------------------------------------------	OnReshape()
//



	FMOD::System *sys;
	FMOD::DSP *dsp ;
	FMOD_RESULT res;


void ERRCHECK(FMOD_RESULT result){
	if(result != FMOD_OK ){
		std::cout <<"failed";
	}

};


void OnReshape(int w, int h)
{
	if (h==0) {
		h=1;
	}

	// set the drawable region of the window
	glViewport(0,0,w,h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// just use a perspective projection
	glOrtho(0,532,0,10,-100,100);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//------------------------------------------------------------	OnDraw()
//
void OnDraw() {

	// clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	// clear the previous transform
	glLoadIdentity();


	//update the FMOD system
	res = sys->update();
	
	void* spectrumData;
	res = dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&spectrumData, 0, 0,0);
	FMOD_DSP_PARAMETER_FFT *fft = (FMOD_DSP_PARAMETER_FFT*)spectrumData;

	
	if(fft){
		std::cout<<" channels:" <<fft->numchannels;
		for(int i=0;i<fft->numchannels;++i){
			glBegin(GL_POLYGON);
			glColor3f(1.0-4*(*fft->spectrum[i]),4*(*fft->spectrum[i]),0);


			glVertex2f(30, 5+ 500*(*fft->spectrum[i]));
			glVertex2f(60, 4+ 500*(*fft->spectrum[i]));
			glVertex2f(300, 1+ 500*(*fft->spectrum[i]));
			glVertex2f(160, 2+ 500*(*fft->spectrum[i]));

			//speck
			//glVertex2f(10+i,0.5+20*(*fft->spectrum[i]));
			glEnd();

		}
	}


	
	

	// FSOUND_DSP_GetSpectrum returns a pointer to an array of 512
	// floats representing the frequencies of the sound. 
	// 
	//const float* spectrum = FMOD::FSOUND_DSP_GetSpectrum();

	// just walk through the array and render end spectrum value
	/*glBegin(GL_LINE_STRIP);
	for(unsigned int i=0;i!=512;++i) 
	{

		glColor3f(1.0,4.0, i/511);
		glVertex2f(10+i,2+i);
		//glColor3f(1.0-4*spectrum[i],4*spectrum[i],0);
		//glVertex2f(10+i,0.5+20*spectrum[i]);
	}
	glEnd();*/

	// currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	glutSwapBuffers();
	//glutPostRedisplay();
}

//------------------------------------------------------------	OnIdle()
//
void OnIdle() {
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
	glutPostRedisplay();
}


//------------------------------------------------------------	OnInit()
//
void OnInit() {
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------	OnExit()
//
void OnExit() {

	// Stop and close the mp3 file
	//FSOUND_Stream_Stop( g_mp3_stream );
	//FSOUND_Stream_Close( g_mp3_stream );

	// kill off fmod
	//FSOUND_Close();
}


//------------------------------------------------------------	main()
//
int main(int argc,char** argv) {

	
	res = FMOD::System_Create(&sys);
	ERRCHECK(res);

	res = sys->init(32, FMOD_INIT_NORMAL, 0);	
	ERRCHECK(res);

	 FMOD::Sound *sound;
  	 FMOD::Channel          *channel = 0;
	
	//DSP stuff for analyzing sound
	 FMOD::ChannelGroup *masterChannelGroup = NULL;
	
	const int windowSize = 1024;

	res = sys->getMasterChannelGroup(&masterChannelGroup);
	ERRCHECK(res);

	res = sys->createDSPByType(FMOD_DSP_TYPE_FFT, &dsp);
	ERRCHECK(res);

	res = dsp->setParameterInt(FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_HANNING);
	ERRCHECK(res);

	res = dsp->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, windowSize*2);
	ERRCHECK(res);

	res = masterChannelGroup->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp);
	ERRCHECK(res);

	//creating the sound
	res = sys->createSound("../media/Hawaii5O.mp3", FMOD_DEFAULT, 0, &sound);
	ERRCHECK(res);

	res = sys->playSound(sound, 0, false, &channel);
	ERRCHECK(res);
	

	
	// initialise glut
	glutInit(&argc,argv);

	// request a depth buffer, RGBA display mode, and we want double buffering
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);

	// set the initial window size
	glutInitWindowSize(640,480);

	// create the window
	glutCreateWindow("Music Visualizer");

	// set the function to use to draw our scene
	glutDisplayFunc(OnDraw);

	// set the function to handle changes in screen size
	glutReshapeFunc(OnReshape);

	// set the idle callback
	glutIdleFunc(OnIdle);

	// run our custom initialisation
	OnInit();

	// set the function to be called when we exit
	atexit(OnExit);

	// this function runs a while loop to keep the program running.
	glutMainLoop();
	return 0;
}

