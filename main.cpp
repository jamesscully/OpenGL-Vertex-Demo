/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 * Modified by James Scully for Coursework!
 *
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
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

static int slices = 16;
static int stacks = 16;

double rotSpeed = 50;



bool tFpsCounter = false,   //
     tWireframe = true,     //  Bools for toggling FPS/WF/Solid
     tSolid = true;         //

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    gluLookAt(0,5,0, 0, 0,-6, 0, 6, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void renderText(
		float x,
		float y,
		float z,
		void *font,
		char *string) {

  char *c;
  glRasterPos3f(x,y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

int frame=0,time,timebase=0;
double fps;
char fpsCounter[64];

static void drawGrid(float yoffset, int amt) {
    glBegin(GL_LINES);
        glColor3f(0, 0.5, 0);
        for(int x = (amt * -1); x < amt; x++) {

            // x plane
            glVertex3f(x, 0 + yoffset, amt);
            glVertex3f(x, 0 + yoffset, (amt * -1));

            // z plane
            glVertex3f(amt, 0 + yoffset, x);
            glVertex3f((amt * -1), 0 + yoffset, x);
        }
    glEnd();

    glBegin(GL_QUADS);

    glEnd();
}

static void display(void)
{


    char textToDisplay[128];
    int shapeRot = 90;

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;   // time passed
    const double a = t*rotSpeed;

    Camera cam;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0.3,0.3,0.3);
    glEnable(GL_LIGHTING);


    if(tSolid) {
        glPushMatrix();

            glTranslated(-2.4, 0 ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutSolidSphere(1,slices,stacks);
            glShadeModel(GL_FLAT);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0,0.8,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutSolidCone(1,1.8,slices,stacks);
        glPopMatrix();

        glPushMatrix();
            glTranslated(2.4,0.8 ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutSolidCylinder(1, 1.8, slices, stacks);
        glPopMatrix();

        // wire outline
        glColor3d(0.1,0.1,0.1);

        glPushMatrix();
            glDisable(GL_LIGHTING);
            glTranslated(-2.4, 0 ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireSphere(1.01,slices,stacks);
            glShadeModel(GL_FLAT);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0,0.8,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireCone(1.01,1.8,slices,stacks);
        glPopMatrix();

        glPushMatrix();
            glTranslated(2.4,0.8 ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireCylinder(1.01, 1.8, slices, stacks);
        glPopMatrix();
    }

    glColor3d(0,1,0);

    if(tWireframe) {
        glPushMatrix();
            glTranslated(-2.4,0 ,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireSphere(1.025,slices,stacks);
            glShadeModel(GL_FLAT);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0,0.8,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireCone(1.025,1.8,slices,stacks);
        glPopMatrix();

        glPushMatrix();
            glTranslated(2.4,0.8,-6);
            glRotated(shapeRot,1,0,0);
            glRotated(a,0,0,1);
            glutWireCylinder(1.025, 1.825, slices, stacks);
        glPopMatrix();
    }

         if(tFpsCounter) {
        glPushMatrix();
            glLoadIdentity();
            renderText(-0.25, 2.5, -6, GLUT_BITMAP_HELVETICA_18, fpsCounter);
        glPopMatrix();
    }

    sprintf(textToDisplay, "Slices: %d", slices);

    glPushMatrix();
        glLoadIdentity();
        renderText(-0.25, 2, -6, GLUT_BITMAP_HELVETICA_18, textToDisplay);
    glPopMatrix();

    sprintf(textToDisplay, "Stacks: %d", stacks);

    glPushMatrix();
        glLoadIdentity();
        renderText(-0.25, 1.8, -6, GLUT_BITMAP_HELVETICA_18, textToDisplay);
    glPopMatrix();

    drawGrid(-2, 40); // draw grid for dem aesthetics

    glutSwapBuffers();
}



static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

        case '.':
            rotSpeed += 10;
        break;

        case ',':
            if(rotSpeed != 0) {rotSpeed -= 10; }
        break;



    }
    glutPostRedisplay();
}


void specialKeys(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F1:
            tSolid = !tSolid;
        break;

        case GLUT_KEY_F2:
            tWireframe = !tWireframe;
        break;

        case GLUT_KEY_F3:
            tFpsCounter = !tFpsCounter;
        break;

        case GLUT_KEY_UP:
            stacks++;
            break;

        case GLUT_KEY_DOWN:
            if(stacks > 3) { stacks--; }
            break;

        case GLUT_KEY_LEFT:
            if(slices > 3) { slices--; }
            break;

        case GLUT_KEY_RIGHT:
            slices++;
            break;

        case GLUT_KEY_HOME:
            slices = 16;
            stacks = 16;
            break;

    }
}

static void idle(void)
{

    frame++;
	time=glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		fps = (frame * 1000.0) / (time-timebase);
		sprintf(fpsCounter, "FPS:%ld", fps);
	 	timebase = time;
		frame = 0;
	}

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
    glutInitWindowSize(1280,960);
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
