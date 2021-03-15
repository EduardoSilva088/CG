#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>
#include <iostream>

float angle = 0;
float posx = 0;
float posy = 0;
float posz = 0;

float xScale = 1.0f;
float yScale = 1.0f;
float zScale = 1.0f;
GLenum drawType = GL_FILL;

GLuint buffers[1];

GLuint nrVertex, vertexs;

int timebase;
float frames;

int slices = 100;

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
    for (int i = 0; i < slices; i++){
        glColor3f(0,green,0);
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
    for(int i = 0; i < slices; i++){
        glColor3f(0,green,0);
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
    for(int i = 0; i < slices; i++){
        glColor3f(0,green,0);

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

void drawCylinderVBO(float radius, float height, float slices){

    std::vector<float> vertexB;

    float desl = (2 * M_PI) /slices;
    float y = height/2;
    float angle = 0;

    //cima
    for(int i = 0; i <= slices; i++){
        //1st
        vertexB.push_back(radius * sin(angle + desl));
        vertexB.push_back(y);
        vertexB.push_back(radius * cos(angle + desl));

        //2nd
        vertexB.push_back(0);
        vertexB.push_back(y);
        vertexB.push_back(0);

        //3rd
        vertexB.push_back(radius * sin(angle));
        vertexB.push_back(y);
        vertexB.push_back(radius * cos(angle));

        angle = desl * i;
    }

    angle = 0;
    //baixo
    for(int i = 0; i <= slices; i++){
        //1st
        vertexB.push_back(radius * sin(angle));
        vertexB.push_back(-y);
        vertexB.push_back(radius * cos(angle));

        //2nd
        vertexB.push_back(0);
        vertexB.push_back(-y);
        vertexB.push_back(0);

        //3rd
        vertexB.push_back(radius * sin(angle + desl));
        vertexB.push_back(-y);
        vertexB.push_back(radius * cos(angle + desl));

        angle = desl * i;
    }

    //lateral
    angle = 0;
    for(int i = 0; i <= slices; i++){
        //1st
        vertexB.push_back(radius * sin(angle));
        vertexB.push_back(-y);
        vertexB.push_back(radius * cos(angle));

        //2nd
        vertexB.push_back(radius * sin(angle + desl));
        vertexB.push_back(-y);
        vertexB.push_back(radius * cos(angle + desl));

        //3rd
        vertexB.push_back(radius * sin(angle + desl));
        vertexB.push_back(y);
        vertexB.push_back(radius * cos(angle + desl));

        //4th
        vertexB.push_back(radius * sin(angle + desl));
        vertexB.push_back(y);
        vertexB.push_back(radius * cos(angle + desl));

        //5th
        vertexB.push_back(radius * sin(angle));
        vertexB.push_back(y);
        vertexB.push_back(radius * cos(angle));

        //6th
        vertexB.push_back(radius * sin(angle));
        vertexB.push_back(-y);
        vertexB.push_back(radius * cos(angle));

        angle = desl * i;
    }


    nrVertex = vertexB.size() / 3;

    glBindBuffer(GL_ARRAY_BUFFER, vertexs);
    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(float) * vertexB.size(),
            vertexB.data(),
            GL_STATIC_DRAW
    );
}

void frameRate(){
    char title[50];
    frames++;
    double time = glutGet(GLUT_ELAPSED_TIME);

    if (time - timebase > 1000){
        double fps = frames * 1000.0 / (time - timebase);
        timebase = time;
        frames = 0;

        sprintf(title, "CG@di-UM |  %lf FPS", fps);
        glutSetWindowTitle(title);
    }
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);
    glColor3f(1,1,1);



    glBindBuffer(GL_ARRAY_BUFFER, vertexs);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES, 0, nrVertex);


    frameRate();

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
            slices *= 2;
            drawCylinderVBO(1,2,slices);
            std::cout << "Slices:" << slices << std::endl;
            break;
        case '-':
            slices /= 2;
            drawCylinderVBO(1,2,slices);
            std::cout << "Slices:" << slices << std::endl;
            break;
        case '1':
            drawType = GL_LINE;
            break;
        case '2':
            drawType = GL_FILL;
            break;
        case '3':
            drawType = GL_POINT;
            break;
    }

    glutPostRedisplay();
}

void printInfo() {

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));

}




int main(int argc, char **argv) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("TP04");
    timebase = glutGet(GLUT_ELAPSED_TIME);

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);



// put here the registration of the keyboard callbacks
    glutKeyboardFunc(reactKeyboard);

#ifndef __APPLE__
    glewInit();
#endif


//  OpenGL settings
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glPolygonMode(GL_FRONT, GL_LINE);

    printInfo();

    glGenBuffers(1, &vertexs);
    drawCylinderVBO(1,2,slices);

    timebase = glutGet(GLUT_ELAPSED_TIME);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
