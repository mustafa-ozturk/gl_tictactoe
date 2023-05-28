#pragma once

#include <iostream>
#include <glbinding/gl/gl.h>

using namespace gl;

class Game
{
public:
    Game() = default;
    ~Game() = default;
    void draw_lines(int screen_width, int screen_height);
    int input[3][3] = {
            {-1, -1, -1},
            {-1, -1, -1},
            {-1, -1, -1}
    };
private:
    void draw_line(int x_start, int x_end, int y_start, int y_end);
};
