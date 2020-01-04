 #ifndef CAMERA_H
#define CAMERA_H

#include "vec3D.h"


class Camera
{
    public:
        Camera();
        virtual ~Camera();

        vec3D tPos, //  target position vector
              cPos, //  camera position vector
              oPos; //  orientation vector (must point upwards of camera)

        void changeTPos(float x, float y, float z);
        void changeCPos(float x, float y, float z);
        void changeOPos(float x, float y, float z);

        void update();

        void rotateX(float speed);
        void rotateY(float speed);


    protected:

    private:
};

#endif // CAMERA_H
