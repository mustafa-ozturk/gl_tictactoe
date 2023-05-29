#pragma once

#include <iostream>
#include <glbinding/gl/gl.h>
#include <GLFW/glfw3.h>
#include "gl_textrenderer/gl_textrenderer.h"
#include "Square/Square.h"

using namespace gl;

enum END_GAME_STATES
{
    O_WINS, X_WINS, DRAW
};

enum GAME_STATE
{
    GAME, END
};

class Game
{
public:
    Game(int screen_width, int screen_height);

    ~Game() = default;

    void
    draw_lines(unsigned int shaderProgram);

    int input[3][3] = {
            {-1, -1, -1},
            {-1, -1, -1},
            {-1, -1, -1}
    };

    void draw_input(gl_textrenderer& textrenderer, std::map<int,
            Square>& squares, unsigned int shaderProgram);

    void process_input(int last_mouse_x, int last_mouse_y,
                       std::map<int, Square>& squares,
                       END_GAME_STATES& current_player,
                       int& turn);

    void reset(int& turn, END_GAME_STATES& current_player,
               GAME_STATE& current_game_state);

    END_GAME_STATES find_winner();

    void set_color_dark();

    void set_color_light();

    void
    draw_endgame_text(END_GAME_STATES end_state,
                      std::string x_win_text, std::string o_win_text,
                      std::pair<int, int> x_win_text_size,
                      std::pair<int, int> o_win_text_size,
                      std::pair<int, int> end_text_size,
                      std::pair<int, int> draw_text_size,
                      gl_textrenderer& end_text_renderer,
                      std::string end_text, std::string draw_text
    );

    float text_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    int curr_mouse_state;
    int prev_mouse_state;
private:
    int screen_width;
    int screen_height;

    void draw_line(int x_start, int x_end, int y_start, int y_end);

    std::string map_player(int input_value);

    END_GAME_STATES next_player(END_GAME_STATES current_player, int& turn);
};
