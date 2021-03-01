#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

#include <iostream>

float angle = 0;
float posx = 0;
float posy = 0;
float posz = 0;

float xScale = 1.0f;
float yScale = 1.0f;
float zScale = 1.0f;

GLclampf colorA = 1;
GLclampf colorR = 0.5;
GLclampf colorG = 1;
GLclampf colorB = 0.5;

GLenum drawType = GL_FILL;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here
    glBegin(GL_LINES);
        // X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f( 100.0f, 0.0f, 0.0f);
        // Y Axis in Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f,  100.0f, 0.0f);
        // Z Axis in Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f,  100.0f);
    glEnd();

// put drawing instructions here
    glTranslatef(posx, posy, posz);
    glRotatef(angle, 0,1,0);
    glScalef(xScale,yScale,zScale);

    glBegin(GL_TRIANGLES);

        // Base
        // First Triangle
        glColor3f(1.0f,1.0f,1.0f); // White
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 0.0f,-1.0f);
        glVertex3f(-1.0f, 0.0f,-1.0f);

        //Second Triangle
        glVertex3f(-1.0f, 0.0f,-1.0f);
        glVertex3f(-1.0f, 0.0f,1.0f);
        glVertex3f(1.0f,  0.0f, 1.0f);


        // Front
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glVertex3f( 0.0f, 1.5f, 0.0f);
        glVertex3f(-1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f,  0.0f, 1.0f);

        // Right
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(0.0f, 1.5f, 0.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);

        // Back
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(0.0f, 1.5f, 0.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f);

        // Left
        glColor3f(1.0f,0.0f,0.0f);       // Red
        glVertex3f( 0.0f, 1.5f, 0.0f);
        glVertex3f(-1.0f, 0.0f,-1.0f);
        glVertex3f(-1.0f, 0.0f, 1.0f);
    glEnd();   // Done drawing the pyramid



	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void reactKeyboard(unsigned char c, int x, int y){

    switch(c){
        case 'a':
            posx -= 0.1f;
            break;
        case 'd':
            posx += 0.1f;
            break;
        case 'w':
            posy += 0.1f;
            break;
        case 's':
            posy -= 0.1f;
            break;
        case 32:
            angle += 1.5;
            break;
        case 'z':
            posz += 0.1f;
            break;
        case 'x':
            posz -= 0.1f;
            break;
        case '+':
            yScale += 0.1f;
            break;
        case '-':
            yScale -= 0.1f;
            break;
        case '1':
            drawType = GL_LINE;
            break;
        case '2':
            drawType = GL_FILL;
            break;
        case '3':
            drawType = GL_POINT;

    }

    glutPostRedisplay();
}

void reactMouse(int button,int state, int x, int y){

}

void mouseMove(int x, int y) {

    // Changing the bg color with X and Y pos of the mouse.
    colorR = fabs(sin((x/15) * 3.142/180));
    colorG = fabs(sin((y/15) * 3.142/180));
    colorB = fabs(sin((x-y/20) * 3.142/180));

    // Changing the angle considering mouse X position.
    angle = x/3;

    glClearColor(colorR,colorG,colorB,colorA);
    glutPostRedisplay();



}






int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("TP2");

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks
    glutKeyboardFunc(reactKeyboard);
    //glutMouseFunc(reactMouse);
    //Callback to track mouse position
    glutPassiveMotionFunc(mouseMove);




//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


// enter GLUT's main cycle
	glutMainLoop();


	return 1;
}
