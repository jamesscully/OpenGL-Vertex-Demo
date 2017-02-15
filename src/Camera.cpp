#include "Camera.h"
#include "stdio.h"
#include "math.h"
#include <GL/glut.h>


Camera::Camera()
{
    tPos = vec3D(0, 2, -6);
    cPos = vec3D(0, 3, 0);
    oPos = vec3D(0, 1, 0);

    updateCamera();

    printf("%f", tPos.y);

    //ctor
}

Camera::~Camera()
{
    //dtor
}

void Camera::changeTPos(float x, float y, float z)
{
    tPos = vec3D(x, y, z);
}

void Camera::changeCPos(float x, float y, float z)
{
    cPos = vec3D(x, y, z);
    updateCamera();
}

void Camera::changeOPos(float x, float y, float z)
{
    oPos = vec3D(x, y, z);
}

void Camera::updateCamera()
{
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);

    gluLookAt(cPos.x, cPos.y, cPos.z,
              tPos.x, tPos.y, tPos.z,
              oPos.x, oPos.y, oPos.z);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void Camera::rotate(float phi, float theta)
{

    float rad = 2.0f;

    cPos.x = tPos.x + rad * cos(phi) * sin(theta);
    cPos.x = tPos.y + rad * sin(phi) * sin(theta);
    cPos.x = tPos.z + rad * cos(theta);

    updateCamera();

    //vec3D deltaVec = tPos - cPos;
    //cPos.z = (float)(tPos.z + sin(spd)*deltaVec.x + cos(spd)*deltaVec.z);
    //cPos.x = (float)(tPos.x + sin(spd)*deltaVec.x + cos(spd)*deltaVec.z);
}




