#pragma once
#include "Object.h"
class TextObject :
    public Object
{
public:
    TextObject( std::string text );

    void draw() override;
    void update(float dt) override;
    void setText(const std::string &txt) { _text = txt; }

private:

    std::string _text;

};

