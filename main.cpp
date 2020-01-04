/*
 * Vertex Count Demo!
 *
 *
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <GL/freeglut.h>
#include <Camera.h>
#include <BillboardText.h>
#include "OnscreenText.h"

#define WLENGTH 1280    // define window size
#define WHEIGHT 1024

GLfloat fogColor[4]= {0.0f, 0.1f, 0.0f, 1.0f};      // fog color

static int slices = 16; int stacks = 16;    //  Shape Variables
static double rotSpeed = 50;                //

Camera cam;     // create camera object

bool        tFpsCounter = false,   //
            tWireframe = true,     //  Bools for toggling FPS/WF/Solid
            tSolid = true;


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    //glLoadIdentity();
    glMatrixMode(GL_PROJECTION);

    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutReshapeWindow(WLENGTH, WHEIGHT);

    glViewport(0, 0, width, height);

}

void drawGrid(int amt) {
    int nAmt = (amt * -1);  // create variable for negative amount
    glBegin(GL_LINES);
        glColor3f(0, 0.5, 0);
        for(int x = nAmt; x < amt; x++) {
            // x plane
            glVertex3f(x, 0, amt);
            glVertex3f(x, 0, nAmt);
            // z plane
            glVertex3f(amt, 0, x);
            glVertex3f(nAmt, 0, x);
        }
    glEnd();
}

static void drawFog() {
    glFogi(GL_FOG_MODE, GL_LINEAR);        // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 2.0f);
    glFogf(GL_FOG_END, 20.0f);
    glEnable(GL_FOG);
}


static void display(void)
{
    char textToDisplay[128];
    int shapeRot = 90;

    float shapeHeight = 2;    // for y coords

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;   // time passed
    const double a = t*rotSpeed;

    cam.update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0.3,0.3,0.3);
    glEnable(GL_LIGHTING);

    /*
    //   SOLID SHAPES
    */

    if(tSolid) {
        glPushMatrix();
            glTranslated(-2.4, shapeHeight ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutSolidSphere(1,slices,stacks);

            glShadeModel(GL_FLAT);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0, (shapeHeight + 0.8) ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutSolidCone(1,1.8,slices,stacks);


        glPopMatrix();

        glPushMatrix();
            glTranslated(2.4, (shapeHeight + 0.8) ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutSolidCylinder(1, 1.8, slices, stacks);
        glPopMatrix();

    /*
    //  EDGE HIGHLIGHTING
    */

        glColor3d(0.3,0.3,0.3);

        glPushMatrix();
            glDisable(GL_LIGHTING);
            glTranslated(-2.4, shapeHeight ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireSphere(1.01,slices,stacks);
            glShadeModel(GL_FLAT);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0, (shapeHeight + 0.8) ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireCone(1.01,1.8,slices,stacks);
        glPopMatrix();

        glPushMatrix();
            glTranslated(2.4, (shapeHeight + 0.8) ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireCylinder(1.01, 1.8, slices, stacks);
        glPopMatrix();
    }

    /*
    //  WIREFRAME OVERLAY
    */

    glColor3d(0,1,0);

    if(tWireframe) {
        glPushMatrix();
            glTranslated(-2.4, shapeHeight ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireSphere(1.025,slices,stacks);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0, (shapeHeight + 0.8) ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireCone(1.025,1.8,slices,stacks);
        glPopMatrix();

        glPushMatrix();
            glTranslated(2.4, (shapeHeight + 0.8) ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireCylinder(1.025, 1.825, slices, stacks);
        glPopMatrix();
    }

    /*
    //  TEXT
    */

    glColor3f(1, 1, 1);

    BillboardText txtSlices (vec3D(-1, 1.5, -6), textToDisplay),
                  txtStacks (vec3D(0.5, 1.5, -6), textToDisplay);


    OnscreenText controlText1(0, WHEIGHT - 20, "Increase / Decrease: Slices = A / D | Stacks = W / S | Proportionally: Numpad + and -"),
                 controlText2(0, WHEIGHT - 50, "Toggle: Shapes (F1), Wireframe (F2)"),
                 controlText3(0, WHEIGHT - 75, "Rotation Speed: < and > ");

    glPushMatrix();
        glLoadIdentity();

        sprintf(textToDisplay, "Slices: %d", slices);
        txtSlices.render();

        sprintf(textToDisplay, "Stacks: %d", stacks);
        txtStacks.render();

        controlText1.render();
        controlText2.render();
        controlText3.render();

    glPopMatrix();

    drawFog();
    drawGrid(100); // draw grid for dem aesthetics

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':   exit(0); break;     // quit

        case '+':   slices++; stacks++;                                 break; // increment slices & stacks
        case '-':   if (slices>3 && stacks>3) { slices--; stacks--; }   break; // decrement slices & stacks
        case '.':   rotSpeed += 10;                                     break; // increase rotation
        case ',':   if(rotSpeed != 0) {rotSpeed -= 10; }                break; // slow rotation
        case 'w':   stacks++;                                           break;
        case 's':   if(stacks > 3) { stacks--; }                        break;
        case 'd':   slices++;                                           break;
        case 'a':   if(slices > 3) { slices--; }                        break;

    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F1:    tSolid = !tSolid;               break;
        case GLUT_KEY_F2:    tWireframe = !tWireframe;       break;
        case GLUT_KEY_F3:    tFpsCounter = !tFpsCounter;     break;
        case GLUT_KEY_HOME:  slices = 16; stacks = 16;       break;
    }
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 0.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WLENGTH, WHEIGHT);
    glutInitWindowPosition(2000,300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Vertex Count Demo");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glutSpecialFunc(specialKeys);
    glutIdleFunc(idle);
    glClearColor(0.1,0.1,0.1,1);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glEnable(GL_LINE_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}


