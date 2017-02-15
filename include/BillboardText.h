#ifndef BILLBOARDTEXT_H
#define BILLBOARDTEXT_H
#include "vec3D.h"

class BillboardText
{
    public:
        BillboardText(vec3D pos, char* text);
        virtual ~BillboardText();

        vec3D textPosition;
        void* font;
        char* string;

        void setPos(vec3D position);
        void setText(char* text);
        void setFont(void* fnt);
        void render();

    protected:

    private:
};

#endif // BILLBOARDTEXT_H
