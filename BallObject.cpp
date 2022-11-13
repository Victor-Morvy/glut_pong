#include "BallObject.h"
#include <math.h>

BallObject::
BallObject(float radius):
    Object(Object::CIRCLE)
{
    _angle = 0;
    _radius = radius;
}

void BallObject::draw()
{
    float cx = getPos()[0];
    float cy = getPos()[1];
    lastPos[0] = cx;
    lastPos[1] = cy;
    float r = _radius;
    int num_segments = 16;
    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

void BallObject::update(float dt)
{
    float dx, dy;

    auto degToRad = [this] (float deg)
    {
        return _angle * 0.0174533;
    };
    
    dy = vel()*sinf(degToRad(_angle));
    dx = vel()*cosf(degToRad(_angle));

    float* pos = getPos();
    lastPos[0] = pos[0];
    lastPos[1] = pos[1];
    pos[0] += dx;
    pos[1] += dy;

    if (_angle > 360.f)
        _angle -= 360.f;
    else if (_angle < 0.f)
        _angle += 360.f;

}
