#include "PlayerObject.h"


PlayerObject::PlayerObject(float size[2]):
	Object( Object::RECTANGLE )
{
	_move = PlayerObject::MOVE::NONE;
	_recSize[0] = size[0];
	_recSize[1] = size[1];
}

void PlayerObject::draw(){
	float* pos = getPos(); //0, 1 - x, y
	glBegin(GL_QUADS);

	float leftUp[2];
	leftUp[0] = pos[0] - _recSize[0] / 2.f;
	leftUp[1] = pos[1] + _recSize[1] / 2.f;

	float rightUp[2];
	rightUp[0] = pos[0] + _recSize[0] / 2.f;
	rightUp[1] = pos[1] + _recSize[1] / 2.f;

	float rightDown[2];
	rightDown[0] = pos[0] + _recSize[0] / 2.f;
	rightDown[1] = pos[1] - _recSize[1] / 2.f;

	float leftDown[2];
	leftDown[0] = pos[0] - _recSize[0] / 2.f;
	leftDown[1] = pos[1] - _recSize[1] / 2.f;

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(leftUp[0], leftUp[1], 0.0);
	glVertex3f(rightUp[0], rightUp[1], 0.0);
	glVertex3f(rightDown[0], rightDown[1], 0.0);
	glVertex3f(leftDown[0], leftDown[1], 0.0);
	glEnd();

}

void PlayerObject::update( float dt )
{
	//int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
	//int screenHeight
	float move = dt * vel();
	float* pos;
	pos = getPos();
	int drawHeight = 720;
	if (_move == MOVE::UP)
	{
		float tmpPos = pos[1];
		tmpPos += move;
		float tmpLastPos = (tmpPos + _recSize[1] / 2);
		if (tmpLastPos > float(drawHeight))
		{
			tmpPos = float(drawHeight) - _recSize[1] / 2;
		}

		setY(tmpPos);
	}
	else if (_move == MOVE::DOWN)
	{
		float tmpPos = pos[1];
		tmpPos -= move;
		float tmpLastPos = (tmpPos - _recSize[1] / 2);
		if (tmpLastPos < 0)
		{
			tmpPos = _recSize[1] / 2;
		}

		setY(tmpPos);
	}
	else
	{
		////
	}

	/*_move = MOVE::NONE;*/
}
