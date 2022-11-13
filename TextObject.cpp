#include "TextObject.h"
#include <GL/glut.h>
#include <GL/freeglut.h>

TextObject::TextObject( std::string text ):
	Object( Type::TEXT ), _text(text)
{

}

void TextObject::draw()
{
	float* pos = getPos();

	glColor3f(1.f, 1.f, 1.f);
	glRasterPos2f(pos[0], pos[1]);

	const unsigned char* c = reinterpret_cast< const unsigned char*> ( _text.c_str() );
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, c );
	
}

void TextObject::update(float dt)
{

}