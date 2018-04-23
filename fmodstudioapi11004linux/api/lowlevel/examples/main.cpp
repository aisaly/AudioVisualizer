#include <stdlib.h>
#include <GL/glut.h>
#include "fmod.hpp"
//#include <fmod_studio.h>
//#include <fmod_errors.h>
#include <iostream>
#include <math.h>


/// this is a pointer to the mp3 stream we will be reading from the disk.
//FSOUND_STREAM* g_mp3_stream = NULL;


//global vars
FMOD::System *sys;
FMOD::DSP *dsp;
FMOD_RESULT res;
FMOD::Sound *sound;
FMOD::Sound *sound2;
FMOD::Sound *sound3;
FMOD::Channel *channel = 0;
FMOD::Channel *channel2 = 0;
FMOD::Channel *channel3 = 0;
float previous = 0;
float currentPos = 2;
int theme = 1;
double j = 0;

void ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << "failed";
	}
}

//------------------------------------------------------------	OnReshape()
//
void OnReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// just use a perspective projection
	glOrtho(-320, 320, -240, 240, -100, 100);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//------------------------------------------------------------	OnDraw()
//

void OnDraw() {
	char instructions[] = "press any key to begin";
	glColor3f(1, 1, 1);
	for (int k = 0; k<22; k++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instructions[k]);

	}
	// clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// clear the previous transform
	glLoadIdentity();

	//update the FMOD system
	res = sys->update();

	void* spectrumData;
	res = dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&spectrumData, 0, 0, 0);
	FMOD_DSP_PARAMETER_FFT *fft = (FMOD_DSP_PARAMETER_FFT*)spectrumData;

	if (theme == 1) { //flower

		if (fft) {
			for (int i = 0; i<1; i++) {

				double x;
				double y;

				glClearColor(.5, .5, 1, 1);
				//FLOWER	
				glBegin(GL_TRIANGLE_FAN);
				glColor3f(.3, .1, .1);
				glVertex2f(0, -20);
				for (double j = 0; j<6.3; j += 0.78625) {

					x = 30 * cos(j) + 1000 * (*fft->spectrum[i]);
					y = -20 + 30 * sin(j) + 1000 * (*fft->spectrum[i]);
					glVertex2f(x, y);

				}
				glEnd();

				//petals
				glBegin(GL_TRIANGLES);
				glColor3f(.8, .8, 0);

				for (double j = 0; j < 6.3; j += 0.78625) {

					x = 40 * cos(j) * 400 * (*fft->spectrum[i]);
					y = -20 + 40 * sin(j) * 400 * (*fft->spectrum[i]);
					glVertex2f(x, y);
					glVertex2f(x + 40 * cos(j - 0.8), y + 40 * sin(j - 0.8));
					glVertex2f(x - 40 * cos(j + 0.8), y - 40 * sin(j + 0.8));
				}
				glEnd();

				//stem
				glBegin(GL_POLYGON);
				glColor3f(0.2, 0.9, 0.2);

				glVertex2f(-5, -240);
				glVertex2f(-5, -30);
				glVertex2f(5, -30);
				glVertex2f(5, -240);
				glEnd();

				//leaf
				glBegin(GL_POLYGON);
				glColor3f(0.2, 0.9, 0.2);

				glVertex2f(5, -100);
				glVertex2f(5, -120);
				glVertex2f(30, -100);
				glEnd();
			}
		}
	}

	else if (theme == 2 && fft) { //square
		double x;
		double y;
		/*
		if (*fft->spectrum[i] < previous) {
			currentPos = currentPos - 0.25;
		}
		else {
			currentPos = currentPos + 0.25;
		}
		if (currentPos>7) {
			currentPos = 7;
		}
		*/

		// alternating background color
		glClearColor(.8 * cos(j), .8 * sin(2*j), .2, 1.0);
		j += .001;

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
		glColor3f(1.0 - 4 * (*fft->spectrum[0]), 0.5 + 100 * (*fft->spectrum[0]), 0);

		glVertex2f(-5, 50 + 20 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-5, -50 - 20 * 1000 * (*fft->spectrum[0]));
		glVertex2f(5, -50 - 20 * 1000 * (*fft->spectrum[0]));
		glVertex2f(5, 50 + 20 * 1000 * (*fft->spectrum[0]));
		glEnd();

		//2nd level
		glBegin(GL_POLYGON);
		glColor3f(.9 - 4 * (*fft->spectrum[0]), 0.4 + 100 * (*fft->spectrum[0]), 0);

		glVertex2f(-25, 30 + 15 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-25, -30 - 15 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-15, -30 - 15 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-15, 30 + 15 * 1000 * (*fft->spectrum[0]));
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(.9 - 4 * (*fft->spectrum[0]), 0.4 + 100 * (*fft->spectrum[0]), 0);

		glVertex2f(15, 30 + 15 * 1000 * (*fft->spectrum[1]));
		glVertex2f(15, -30 - 15 * 1000 * (*fft->spectrum[1]));
		glVertex2f(25, -30 - 15 * 1000 * (*fft->spectrum[1]));
		glVertex2f(25, 30 + 15 * 1000 * (*fft->spectrum[1]));
		glEnd();

		//3rd level
		glBegin(GL_POLYGON);
		glColor3f(.8 - 4 * (*fft->spectrum[0]), 0.3 + 100 * (*fft->spectrum[0]), 0);

		glVertex2f(-35, 15 + 8 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-35, -15 - 8 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-45, -15 - 8 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-45, 15 + 8 * 1000 * (*fft->spectrum[0]));
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(.8 - 4 * (*fft->spectrum[0]), 0.3 + 100 * (*fft->spectrum[0]), 0);

		glVertex2f(35, 15 + 8 * 1000 * (*fft->spectrum[1]));
		glVertex2f(35, -15 - 8 * 1000 * (*fft->spectrum[1]));
		glVertex2f(45, -15 - 8 * 1000 * (*fft->spectrum[1]));
		glVertex2f(45, 15 + 8 * 1000 * (*fft->spectrum[1]));
		glEnd();

		//4th level
		glBegin(GL_POLYGON);
		glColor3f(.7 - 4 * (*fft->spectrum[0]), 0.2 + 100 * (*fft->spectrum[0]), 0);

		glVertex2f(-55, 15 + 5 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-55, -15 - 5 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-65, -15 - 5 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-65, 15 + 5 * 1000 * (*fft->spectrum[0]));
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(.7 - 4 * (*fft->spectrum[0]), 0.2 + 100 * (*fft->spectrum[0]), 0);

		glVertex2f(55, 15 + 5 * 1000 * (*fft->spectrum[1]));
		glVertex2f(55, -15 - 5 * 1000 * (*fft->spectrum[1]));
		glVertex2f(65, -15 - 5 * 1000 * (*fft->spectrum[1]));
		glVertex2f(65, 15 + 5 * 1000 * (*fft->spectrum[1]));
		glEnd();

		// neighboring specks
		glPointSize(3.0);
		glBegin(GL_POINTS);
		glColor3f(.7 - 4 * (*fft->spectrum[0]), 0.2 + 100 * (*fft->spectrum[0]), 0);
		glVertex2f(75, 10 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-75, 10 * 1000 * (*fft->spectrum[0]));
		glVertex2f(85, 20 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-85, 20 * 1000 * (*fft->spectrum[0]));
		glVertex2f(95, 30 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-95, 30 * 1000 * (*fft->spectrum[0]));
		glVertex2f(75, -10 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-75, -10 * 1000 * (*fft->spectrum[0]));
		glVertex2f(85, -20 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-85, -20 * 1000 * (*fft->spectrum[0]));
		glVertex2f(95, -30 * 1000 * (*fft->spectrum[0]));
		glVertex2f(-95, -30 * 1000 * (*fft->spectrum[0]));
		glEnd();
		glPointSize(1.0);
		//previous = *fft->spectrum[i];
		//speck
		//glVertex2f(10+i,0.5+20*(*fft->spectrum[i]));
	}

	else if (theme == 3 && fft) { // speakers
		float curr0 = *fft->spectrum[0];
		float curr1 = *fft->spectrum[1];
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		double i;
		int x, y;
		if (j < 1) {
			glBegin(GL_POINTS);
			// ------ First 'speaker' -------
			//smallest radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 10 * 1000 * curr0 * cos(i);
				y = 10 * 1000 * curr0 * sin(i);
				glVertex2i(x / 2 - 130, y / 2);
			}
			//middle radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 30 * 1000 * curr0 * cos(i);
				y = 30 * 1000 * curr0 * sin(i);
				glVertex2i(x / 2 - 130, y / 2);
			}
			// largest radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 50 * 1000 * curr0 * cos(i);
				y = 50 * 1000 * curr0 * sin(i);
				glVertex2i(x / 2 - 130, y / 2);
			}
			// ------ Second 'speaker' -------
			//smallest radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 10 * 1000 * curr1 * cos(i);
				y = 10 * 1000 * curr1 * sin(i);
				glVertex2i(x / 2 + 130, y / 2);
			}
			//middle radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 50 * 1000 * curr1 * cos(i);
				y = 50 * 1000 * curr1 * sin(i);
				glVertex2i(x / 2 + 130, y / 2);
			}
			// largest radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 80 * 1000 * curr1 * cos(i);
				y = 80 * 1000 * curr1 * sin(i);
				glVertex2i(x / 2 + 130, y / 2);
			}
			glEnd();
		}
		else {
			glBegin(GL_POINTS);
			if (cos(j) > .67) {
				glColor3f(curr0 * 700, .5, .5);
			}
			else if (cos(j) > .33) {
				glColor3f(.5, curr0 * 700, .5);
			}
			else {
				glColor3f(.5, .5, curr0 * 700);
			}
			// ------ First 'speaker' -------
			//smallest radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 50 * 1000 * curr0 * cos(i);
				y = 50 * 1000 * curr0 * sin(i);
				glVertex2i(x / 2 - 130, y / 2);
			}
			//middle radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 80 * 1000 * curr0 * cos(i);
				y = 80 * 1000 * curr0 * sin(i);
				glVertex2i(x / 2 - 130, y / 2);
			}
			// largest radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 100 * 1000 * curr0 * cos(i);
				y = 100 * 1000 * curr0 * sin(i);
				glVertex2i(x / 2 - 130, y / 2);
			}
			// ------ Second 'speaker' -------
			//smallest radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 50 * 1000 * curr1 * cos(i);
				y = 50 * 1000 * curr1 * sin(i);
				glVertex2i(x / 2 + 130, y / 2);
			}
			//middle radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 80 * 1000 * curr1 * cos(i);
				y = 80 * 1000 * curr1 * sin(i);
				glVertex2i(x / 2 + 130, y / 2);
			}
			// largest radius
			for (i = 0; i < 6.29; i += 0.001)
			{
				x = 100 * 1000 * curr1 * cos(i);
				y = 100 * 1000 * curr1 * sin(i);
				glVertex2i(x / 2 + 130, y / 2);
			}
			glEnd();
		}
		j += .01;
	}

	else if (theme == 4) { // tunnel trip
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		double i;
		int x, y;
		float curr0 = *fft->spectrum[0];
		float curr1 = *fft->spectrum[1];
		for (i = 0; i < 6.29; i += 0.001)
		{
			x = 500 * 1000 * curr1 * cos(i);
			y = 500 * 1000 * curr1 * sin(i);

			//Crazy tunnel
			glVertex2i(x /2, y / 2);
			glVertex2i(x / 3, y / 3);
			glVertex2i(x / 4, y / 4);

			glColor3f(curr0 * 700, .5, .5);

			j += .01;
		}
		glEnd();

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
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780, 780, -420, 420);
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
		theme = 2;
		break;

	case '3':
		theme = 3;
		break;

	case '4':
		theme = 4;
		break;

	case '5': //hawaii
		channel->setPaused(false);
		channel3->setPaused(true);
		channel2->setPaused(true);
		break;

	case '6': //singing
		channel->setPaused(true);
		channel3->setPaused(true);
		channel2->setPaused(false);
		break;

	case '7'://sunny
		channel->setPaused(true);
		channel2->setPaused(true);
		channel3->setPaused(false);
		break;
	case 27:
		exit(0);
		break;
	}

	glutPostRedisplay();
}

void menu(int item) {
	keyboard((unsigned char)item, 0, 0);
}

int main(int argc, char** argv) {


	res = FMOD::System_Create(&sys);
	ERRCHECK(res);

	res = sys->init(32, FMOD_INIT_NORMAL, 0);
	ERRCHECK(res);

	//DSP stuff for analyzing sound
	FMOD::ChannelGroup *masterChannelGroup = NULL;

	const int windowSize = 1024;

	res = sys->getMasterChannelGroup(&masterChannelGroup);
	ERRCHECK(res);

	res = sys->createDSPByType(FMOD_DSP_TYPE_FFT, &dsp);
	ERRCHECK(res);

	res = dsp->setParameterInt(FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_HANNING);
	ERRCHECK(res);

	res = dsp->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, windowSize * 2);
	ERRCHECK(res);

	res = masterChannelGroup->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp);
	ERRCHECK(res);

	//creating the sound
	res = sys->createSound("media/Hawaii5O.mp3", FMOD_LOOP_NORMAL, 0, &sound);
	res = sys->createSound("media/singing.wav", FMOD_LOOP_NORMAL, 0, &sound2);
	res = sys->createSound("media/bensound-sunny.mp3", FMOD_LOOP_NORMAL, 0, &sound3);
	ERRCHECK(res);

	res = sys->playSound(sound, 0, false, &channel);
	res = sys->playSound(sound2, 0, true, &channel2);
	res = sys->playSound(sound3, 0, true, &channel3);
	ERRCHECK(res);



	// initialise glut
	glutInit(&argc, argv);

	// request a depth buffer, RGBA display mode, and we want double buffering
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);

	// set the initial window size
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	// create the window
	glutCreateWindow("Music Visualizer");

	// run our custom initialisation
	OnInit();

	// set the function to use to draw our scene
	glutDisplayFunc(OnDraw);

	// set function to handle keyboard events
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
	glutAddMenuEntry("[2]   Bars", '2');
	glutAddMenuEntry("[3]   Speakers", '3');
	glutAddMenuEntry("[4]   Tunnel", '4');
	glutAddMenuEntry("[5]   Play Hawaii5O.mp3", '5');
	glutAddMenuEntry("[6]   Play singing.wav", '6');
	glutAddMenuEntry("[7]   Play sunny.wav", '7');

	glutAddMenuEntry("", 0);
	glutAddMenuEntry("[Esc] Quit", 27);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// set the function to be called when we exit
	atexit(OnExit);

	// this function runs a while loop to keep the program running.
	glutMainLoop();
	return 0;
}
