#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

float scale = 1.0f;
float angle = 0;
float posx = 0;
float posy = 0;
float posz = 0;



void reactKeyboard(unsigned char key, int x, int y){
	switch (key){
		case '+':
			scale += 0.1;
			break;
		case '-':
			scale -= 0.1;
			break;
		case 'w':
			posz -= 0.1;
			break;
		case 's':
			posz += 0.1;
			break;
		case 'a':
			posx -= 0.1;
			break;
		case 'd':
			posx += 0.1;
			break;
		case 'h':
			angle += 1;
			break;
		case 'l':
			angle -= 1;
			break;
		case 'j':
			posy += 0.1;
			break;
		case 'k':
			posy -= 0.1;
	}
}

void changeSize(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void){
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f);
		
	// put drawing instructions here
	glColor3f(1.0, 1.0, 0);
	glTranslated(posx,posy,posz);
	glRotated(angle, 0,1,0);
	glutWireTeapot(scale);

	
	// End of frame
	glutSwapBuffers();
}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv){
    // put GLUT’s init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("TP1");
    printInfo();


    // put callback registry here
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);
	glutKeyboardFunc(reactKeyboard);

    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // enter GLUT’s main cycle
    glutMainLoop();

	
	return 1;
}