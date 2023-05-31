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

    void draw_endgame_text(END_GAME_STATES end_state,
                           gl_textrenderer& end_text_renderer);

    std::array<float, 4> get_text_color();

    int curr_mouse_state;
    int prev_mouse_state;

private:
    std::array<float, 4> m_text_color = {1.0f, 1.0f, 1.0f, 1.0f};
    int m_screen_width;
    int m_screen_height;
    std::string m_end_text = "click anywhere to replay";
    std::string m_draw_text = "DRAW!";
    std::string m_x_win_text = "X WINS!";
    std::string m_o_win_text = "O WINS!";

    void draw_line(int x_start, int x_end, int y_start, int y_end);

    std::string map_player(int input_value);

    END_GAME_STATES next_player(END_GAME_STATES current_player, int& turn);
};
