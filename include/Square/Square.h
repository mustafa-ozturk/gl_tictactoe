#pragma once

#include <iostream>
#include <glbinding/gl/gl.h>
#include <map>

using namespace gl;

class Square
{
public:
    Square() = default;
    ~Square() = default;
    std::map<int, Square>  create_squares(int screen_width, int screen_height);
    int x_start;
    int x_end;
    int y_start;
    int y_end;
};
