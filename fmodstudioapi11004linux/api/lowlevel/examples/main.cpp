
#include <stdlib.h>
#include <GL/glut.h>
#include "fmod.hpp"
//#include <fmod_studio.h>
//#include <fmod_errors.h>
#include <iostream>
#include <math.h>

// global declaration
int x, y;
float i, j;
FMOD::System *sys;
FMOD::DSP *dsp;
FMOD_RESULT res;

void ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << "failed";
	}

};

// Initialization function
void myInit(void)
{
	// Reset background color with black (since all three argument is 0.0)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set picture color to green (in RGB model)
	// as only argument corresponding to G (Green) is 1.0 and rest are 0.0
	glColor3f(1.0, 1.0, 1.0);

	// Set width of point to one unit
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set window size in X- and Y- direction
	gluOrtho2D(-780, 780, -420, 420);
}

// Function to display animation
void display(void)
{
	//update the FMOD system
	res = sys->update();

	void* spectrumData;
	res = dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&spectrumData, 0, 0, 0);
	FMOD_DSP_PARAMETER_FFT *fft = (FMOD_DSP_PARAMETER_FFT*)spectrumData;

	if (fft) {
		// Loop to create animation
		// j is incremented by small value to make motion smoother
		for (j = 0; j < 100; j += 0.01)
		{
			float curr0 = *fft->spectrum[0];
			float curr1 = *fft->spectrum[1];
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_POINTS);

			if (j < 3) {
				// ------ First 'speaker' -------
				//smallest radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 10 * 1000 * curr0 * cos(i);
					y = 10 * 1000 * curr0 * sin(i);
					glVertex2i(x / 2 - 250, y / 2);
				}
				//middle radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 50 * 1000 * curr0 * cos(i);
					y = 50 * 1000 * curr0 * sin(i);
					glVertex2i(x / 2 - 250, y / 2);
				}
				// largest radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 80 * 1000 * curr0 * cos(i);
					y = 80 * 1000 * curr0 * sin(i);
					glVertex2i(x / 2 - 250, y / 2);
				}
				// ------ Second 'speaker' -------
				//smallest radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 10 * 1000 * curr1 * cos(i);
					y = 10 * 1000 * curr1 * sin(i);
					glVertex2i(x / 2 + 250, y / 2);
				}
				//middle radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 50 * 1000 * curr1 * cos(i);
					y = 50 * 1000 * curr1 * sin(i);
					glVertex2i(x / 2 + 250, y / 2);
				}
				// largest radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 80 * 1000 * curr1 * cos(i);
					y = 80 * 1000 * curr1 * sin(i);
					glVertex2i(x / 2 + 250, y / 2);
				}
			}
			else if (j < 800) {
				if (cos(j) > .67) {
					glColor3f(1.0, 1.0, 1.0);
				}
				else if (cos(j) > .33) {
					glColor3f(1.0, 1.0, 1.0);
				}
				else {
					glColor3f(1.0, 1.0, 1.0);
				}
				// ------ First 'speaker' -------
				//smallest radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 50 * 1000 * curr0 * cos(i);
					y = 50 * 1000 * curr0 * sin(i);
					glVertex2i(x / 2 - 250, y / 2);
				}
				//middle radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 80 * 1000 * curr0 * cos(i);
					y = 80 * 1000 * curr0 * sin(i);
					glVertex2i(x / 2 - 250, y / 2);
				}
				// largest radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 120 * 1000 * curr0 * cos(i);
					y = 120 * 1000 * curr0 * sin(i);
					glVertex2i(x / 2 - 250, y / 2);
				}
				// ------ Second 'speaker' -------
				//smallest radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 50 * 1000 * curr1 * cos(i);
					y = 50 * 1000 * curr1 * sin(i);
					glVertex2i(x / 2 + 250, y / 2);
				}
				//middle radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 80 * 1000 * curr1 * cos(i);
					y = 80 * 1000 * curr1 * sin(i);
					glVertex2i(x / 2 + 250, y / 2);
				}
				// largest radius
				for (i = 0; i < 6.29; i += 0.001)
				{
					x = 120 * 1000 * curr1 * cos(i);
					y = 120 * 1000 * curr1 * sin(i);
					glVertex2i(x / 2 + 250, y / 2);
				}
			}
			glEnd();
			glFlush();
			res = sys->update();
			std::cout << curr0 << " " << curr1 << std::endl;
		}
	}
}

// Driver Program
int main(int argc, char** argv)
{
	res = FMOD::System_Create(&sys);
	ERRCHECK(res);

	res = sys->init(32, FMOD_INIT_NORMAL, 0);
	ERRCHECK(res);

	FMOD::Sound *sound;
	FMOD::Channel *channel = 0;

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
	res = sys->createSound("media/Hawaii5O.mp3", FMOD_DEFAULT, 0, &sound);
	ERRCHECK(res);

	res = sys->playSound(sound, 0, false, &channel);
	ERRCHECK(res);

	glutInit(&argc, argv);

	// Display mode which is of RGB (Red Green Blue) type
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Declares window size
	glutInitWindowSize(1360, 768);

	// Declares window position which is (0, 0)
	// means lower left corner will indicate position (0, 0)
	glutInitWindowPosition(0, 0);

	// Name to window
	glutCreateWindow("Revolution");

	// Call to myInit()
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();
}

