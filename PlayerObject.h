#pragma once
#include "Object.h"
#include <GL/glut.h>
class PlayerObject :
    public Object
{
public:
    enum MOVE {
        DOWN,
        UP,
        NONE
    };

    PlayerObject( float size[2] );

    inline void setMove(MOVE mv) { _move = mv; }
    inline MOVE getMove() { return _move; }
    inline float* size() { return _recSize; }

private:
    float _recSize[2]; //width and height

    void draw() override;
    void update( float dt ) override;

    MOVE _move;
};

