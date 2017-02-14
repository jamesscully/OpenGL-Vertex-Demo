#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
    public:
        Camera();
        virtual ~Camera();

        double  tPosX, tPosY, tPosZ,
                cPosX, cPosY, cPosZ,
                uPosX, uPosY, uPosZ;

    protected:

    private:
};

#endif // CAMERA_H
