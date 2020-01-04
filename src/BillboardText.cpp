#include "BillboardText.h"
#include "GL/glut.h"

BillboardText::BillboardText(vec3D pos, char* text)
{
    setPos(pos);
    font = GLUT_BITMAP_HELVETICA_18;
    str = text;
}

BillboardText::~BillboardText()
{
    //dtor
}

void BillboardText::setPos(vec3D position) {
    textPosition = position;
}

void BillboardText::setText(char* text)
{
    str = text;
}

void BillboardText::setFont(void* fnt)
{
    font = fnt;
}

void BillboardText::render()
{

    char *c;
    glRasterPos3f(textPosition.x,textPosition.y,textPosition.z);
      for (c=str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
      }
}

