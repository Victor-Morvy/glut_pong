#pragma once
#include "Object.h"
#include <GL/glut.h>

class BallObject :
    public Object
{
public:
    BallObject( float radius);

    void setAngle(float deg) { _angle = deg; }
    float getAngle() { return _angle; }
    float getRadius() { return _radius; }
    float* const getLastPos() { return lastPos; }

    void draw() override;
    void update(float dt) override;

private:
    float _radius;

    float _angle;
    float lastPos[2];
    //void calculateCollision()
};

