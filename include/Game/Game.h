#pragma once

#include <iostream>
#include <glbinding/gl/gl.h>
#include "gl_textrenderer/gl_textrenderer.h"
#include "Square/Square.h"

using namespace gl;

enum Player
{
    O, X, DRAW
};

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
    void draw_input(gl_textrenderer& textrenderer,
                    std::map<int, Square>& squares);
private:
    void draw_line(int x_start, int x_end, int y_start, int y_end);
    std::string map_player(int input_value);
};
