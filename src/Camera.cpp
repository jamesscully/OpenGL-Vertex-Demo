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
    //ctor
}

Camera::~Camera()
{
    //dtor
}

void Camera::changeTPos(float x, float y, float z)
{
    tPos = vec3D(x, y, z);
    updateCamera();
}

void Camera::changeCPos(float x, float y, float z)
{
    cPos = vec3D(x, y, z);
    updateCamera();
}

void Camera::changeOPos(float x, float y, float z)
{
    oPos = vec3D(x, y, z);
    updateCamera();
}

void Camera::updateCamera()
{
    glLoadIdentity();

    gluLookAt(cPos.x, cPos.y, cPos.z,
              tPos.x, tPos.y, tPos.z,
              oPos.x, oPos.y, oPos.z);

}



