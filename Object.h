#pragma once
#include <GL/glut.h>
#include <iostream>

class Object
{
public:
	enum Type
	{
		CIRCLE,
		RECTANGLE,
		TEXT
	};

	Object( Type type );

	inline const Type& getType() { return _type; }

	inline void setPos(float x, float y) { _pos[0] = x; _pos[1] = y; }
	inline void setX(float x) { _pos[0] = x; }
	inline void setY(float y) { _pos[1] = y; }
	inline float* const getPos() { return _pos; }
	inline void setName(std::string name) { _name = name; }
	inline std::string& const getName() { return _name; }
	inline void setVel(float v) { _transVelocity = v; }
	float vel() { return _transVelocity; }

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

private:
	std::string _name;
	Type _type;
	float _pos[2]; //xy center
	
	float _transVelocity; //Pixels por segundo
};
