#include "Object.h"

Object::
Object(Type type)
{
	_type = type;
	_pos[0] = 0;
	_pos[1] = 0;
	_transVelocity = 1;
	_name = "";
}
