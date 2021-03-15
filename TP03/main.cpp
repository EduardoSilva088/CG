#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float angle = 0;
float posx = 0;
float posy = 0;
float posz = 0;

float xScale = 1.0f;
float yScale = 1.0f;
float zScale = 1.0f;

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

void drawCylinder(float radius, float height, float slices){


    float desl = (2 * M_PI) / slices;
    float y = height/2;

    float angle = 0;

    // cima
    glBegin(GL_TRIANGLES);
    float green = 0;
    float deslColor = 1 / slices;
    for (int i = 0; i <= slices; i++){
        glColor3f(0,1,0);
        glVertex3f(radius * sin(angle + desl),y,radius * cos(angle + desl));
        glVertex3f(0,y,0);
        glVertex3f(radius * sin(angle), y, radius * cos(angle));

        angle = desl * i;
        green = deslColor * i;
    }

    glEnd();

    // baixo
    glBegin(GL_TRIANGLES);
    green = 0;
    for(int i = 0; i <= slices; i++){
        glColor3f(0,1,0);
        glVertex3f(radius * sin(angle),-y,radius * cos(angle));
        glVertex3f(0,-y,0);
        glVertex3f(radius * sin(angle + desl), -y, radius * cos(angle+desl));

        angle = desl * i;
        green = deslColor * i;
    }
    glEnd();

    //laterais
    glBegin(GL_TRIANGLES);
    green = 0;
    for(int i = 0; i <= slices; i++){
        glColor3f(0,1,0);

        glVertex3f(radius * sin(angle),-y,radius * cos(angle));
        glVertex3f(radius * sin(angle + desl), -y, radius * cos(angle + desl));
        glVertex3f(radius * sin(angle + desl), y, radius * cos(angle + desl));

        glVertex3f(radius * sin(angle + desl), y, radius * cos(angle + desl));
        glVertex3f(radius * sin(angle),y,radius * cos(angle));
        glVertex3f(radius * sin(angle),-y,radius * cos(angle));

        angle = desl * i;
        green = deslColor * i;
    }
    glEnd();



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


// put drawing instructions here
    glTranslatef(posx, posy, posz);
    glRotatef(angle, 1,0,0);
    glScalef(xScale,yScale,zScale);

    drawCylinder(1, 2, 20);


	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
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






int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("TP03");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
    glutKeyboardFunc(reactKeyboard);



//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
