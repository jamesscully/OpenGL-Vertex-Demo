#ifndef BILLBOARDTEXT_H
#define BILLBOARDTEXT_H
#include "vec3D.h"
#include <string>

using std::string;

class BillboardText
{
    public:
        BillboardText(vec3D pos, char* text);
        virtual ~BillboardText();

        vec3D textPosition;
        void* font;
        //char* string;
        char* str;

        void setPos(vec3D pos);
        void setText(char* text);
        void setFont(void* fnt);
        void render();

    protected:

    private:
};

#endif // BILLBOARDTEXT_H
