
#include <stdlib.h>
#include <GL/glut.h>
#include "fmod.hpp"
//#include <fmod_studio.h>
//#include <fmod_errors.h>
#include <iostream>
#include<math.h>


/// this is a pointer to the mp3 stream we will be reading from the disk.
//FSOUND_STREAM* g_mp3_stream = NULL;


//------------------------------------------------------------	OnReshape()
//



	FMOD::System *sys;
	FMOD::DSP *dsp ;
	FMOD_RESULT res;
	float previous =0;
	float currentPos =2;

	int theme=1;

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
	char instructions[] = "press any key to begin";
	glColor3f(1,1,1);
	glRasterPos2i(50,5);
	for(int k=0; k<22;k++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instructions[k]);		

	}
	// clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	// clear the previous transform
	glLoadIdentity();


	//update the FMOD system
	res = sys->update();
	
	void* spectrumData;
	res = dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&spectrumData, 0, 0,0);
	FMOD_DSP_PARAMETER_FFT *fft = (FMOD_DSP_PARAMETER_FFT*)spectrumData;

	if(theme == 1){ //flower
		
		if(fft){
		

		for(int i=0;i<1;i++){
			
			double x;
			double y;
			

			glClearColor(.5,.5,1,1);
			//FLOWER	
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.3,.1,.1);
			glVertex2f(250, 6);
			for(double j=0;j<6.3;j+=0.78625){	

				x = 250+30*cos(j)+100*(*fft->spectrum[i]);
				y= 6.5+0.7*sin(j)+100*(*fft->spectrum[i]);
				glVertex2f(x,y);
				
			}
			glEnd();

			//petals
			glBegin(GL_TRIANGLES);
			glColor3f(.8,.8,0);
			
			for(double j=0;j<6.3;j+=0.78625){	

				x = 250+70*cos(j)*400*(*fft->spectrum[i]);
				y= 6.5+1.6*sin(j)*400*(*fft->spectrum[i]);
				glVertex2f(x,y);
				glVertex2f(x+40*cos(j-0.8), y+sin(j-0.8));
				glVertex2f(x-40*cos(j+0.8), y-sin(j+0.8));
			}
			glEnd();

			//stem
			glBegin(GL_POLYGON);
			glColor3f(0.2,0.9,0.2);

			glVertex2f(245,0.1);
			glVertex2f(245,6);
			glVertex2f(255, 6);
			glVertex2f(255, 0.1);
			glEnd();

			//leaf
			glBegin(GL_POLYGON);
			glColor3f(0.2,0.9,0.2);

			glVertex2f(250,3);
			glVertex2f(250,2);
			glVertex2f(285, 2.8);
			glEnd();
			}
		}

	}
	else if(theme ==2){ //square


	if(fft){
		

		for(int i=0;i<1;i++){
			
			double x;
			double y;
			if(*fft->spectrum[i] < previous){
				currentPos =currentPos- 0.25;
			}
			else{
				currentPos= currentPos + 0.25;
			}
			if(currentPos>7){
				currentPos=7;
			}

			

			//smooth cube
			/*glBegin(GL_POLYGON);
			glColor3f(1.0-4*(*fft->spectrum[i]),0.5+100*(*fft->spectrum[i]),0);
			
			glVertex2f(300,currentPos);
			glVertex2f(300, currentPos - 3);
			glVertex2f(60, 5.5);
			glVertex2f(60, 2.5);
			glEnd();*/

			//rectangles
			glBegin(GL_POLYGON);
			glColor3f(1.0-4*(*fft->spectrum[i]),0.5+100*(*fft->spectrum[i]),0);
			
			glVertex2f(50, 4+ 200*(*fft->spectrum[i]));
			glVertex2f(50, 1);
			glVertex2f(30, 1);
			glVertex2f(30, 4+ 200*(*fft->spectrum[i]));
			glEnd();

			//rectangles
			glBegin(GL_POLYGON);
			glColor3f(1.0-4*(*fft->spectrum[i]),0.5+100*(*fft->spectrum[i]),0);
			
			glVertex2f(90, 5+ 500*(*fft->spectrum[i]));
			glVertex2f(90, 1);
			glVertex2f(70, 1);
			glVertex2f(70, 5+ 500*(*fft->spectrum[i]));
			glEnd();

			//rectangles
			glBegin(GL_POLYGON);
			glColor3f(1.0-4*(*fft->spectrum[i]),0.5+100*(*fft->spectrum[i]),0);
			
			glVertex2f(130, 3+ 200*(*fft->spectrum[i]));
			glVertex2f(130, 1);
			glVertex2f(110, 1);
			glVertex2f(110, 3+ 200*(*fft->spectrum[i]));
			glEnd();
			
			previous = *fft->spectrum[i];
			//speck
			//glVertex2f(10+i,0.5+20*(*fft->spectrum[i]));
			}

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


void
keyboard(unsigned char key, int x, int y)
{
    GLint params[2];
    
    switch (key) {
    case '1':
        theme = 1;
        break;
        
    case '2':
       std::cout<<"t";
	theme = 2;
        break;
        
    case '3':
       // performance = !performance;
        break;
        
    case 'm':
       
        break;

   case 27:
        exit(0);
        break;
    }
    
    glutPostRedisplay();
}

void menu(int item){
        keyboard((unsigned char)item, 0, 0);
}

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

	glutKeyboardFunc(keyboard);

	// set the function to handle changes in screen size
	glutReshapeFunc(OnReshape);

	// set the idle callback
	glutIdleFunc(OnIdle);
	
	    glutCreateMenu(menu);
    glutAddMenuEntry("Smooth", 0);
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("[1]   Flower Theme", '1');
    glutAddMenuEntry("[2]   Rectangles", '2');
    glutAddMenuEntry("[3]   Toggle face/smooth normals", 'n');
    glutAddMenuEntry("[4]   Toggle bounding box on/off", 'b');
    glutAddMenuEntry("[5]   Toggle frame rate on/off", 'p');

    glutAddMenuEntry("", 0);
    glutAddMenuEntry("[Esc] Quit", 27);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	// run our custom initialisation
	OnInit();

	// set the function to be called when we exit
	atexit(OnExit);

	// this function runs a while loop to keep the program running.
	glutMainLoop();
	return 0;
}

