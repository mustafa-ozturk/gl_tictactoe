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

enum GAME_STATE
{
    GAME, END
};

class Game
{
public:
    Game() = default;

    ~Game() = default;

    void
    draw_lines(int screen_width, int screen_height, unsigned int shaderProgram);

    int input[3][3] = {
            {-1, -1, -1},
            {-1, -1, -1},
            {-1, -1, -1}
    };

    void
    draw_input(gl_textrenderer& textrenderer, std::map<int, Square>& squares,
               unsigned int shaderProgram);

    void process_input(int last_mouse_x, int last_mouse_y,
                       std::map<int, Square>& squares, Player& current_player,
                       int& turn);

    void reset(int& turn, Player& current_player,
               GAME_STATE& current_game_state, int& prev_mouse_state,
               int& curr_mouse_state);

    Player find_winner();

    void set_color_dark();

    void set_color_light();

    float text_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
private:

    void draw_line(int x_start, int x_end, int y_start, int y_end);

    std::string map_player(int input_value);

    Player next_player(Player current_player, int& turn);
};
