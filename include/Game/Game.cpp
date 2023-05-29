#include "Game.h"

void Game::draw_lines(unsigned int shaderProgram)
{
    glUseProgram(shaderProgram);
    glUniform4f(glGetUniformLocation(shaderProgram, "color"), text_color[0],
                text_color[1], text_color[2], text_color[3]);
    draw_line(0,
              screen_width,
              screen_height / 3,
              screen_height / 3
    );
    draw_line(0,
              screen_width,
              screen_height - screen_height / 3,
              screen_height - screen_height / 3
    );
    // vertical lines
    draw_line(screen_width / 3,
              screen_width / 3,
              0,
              screen_height
    );
    draw_line(screen_width - screen_width / 3,
              screen_width - screen_width / 3,
              0,
              screen_height
    );
}

void Game::draw_line(int x_start, int x_end, int y_start, int y_end)
{
    /*
     * A --- B
     * */
    std::array<int, 8> vertices{
            x_start, y_start,   // A
            x_end, y_end,     // B
    };

    std::array<unsigned int, 2> indices{
            0, 1,
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(int),
                 vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 2 * sizeof(int),
                          (const void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::string Game::map_player(int input_value)
{
    if (input_value == 0)
    {
        return "O";
    }
    if (input_value == 1)
    {
        return "X";
    }
}

void Game::draw_input(gl_textrenderer& textrenderer,
                      std::map<int, Square>& squares,
                      unsigned int shaderProgram)
{
    glUseProgram(shaderProgram);
    glUniform4f(glGetUniformLocation(shaderProgram, "color"), text_color[0],
                text_color[1], text_color[2], text_color[3]);
    // draw X's and O's
    /*
     * 0 | 1 | 2
     * --|---|--
     * 3 | 4 | 5
     * --|---|--
     * 6 | 7 | 8
     * */
    // 0
    if (input[0][0] >= 0)
    {
        textrenderer.render_text(map_player(input[0][0]),
                                 squares[0].x_start + 38,
                                 squares[0].y_start + 20);
    }
    // 1
    if (input[0][1] >= 0)
    {
        textrenderer.render_text(map_player(input[0][1]),
                                 squares[1].x_start + 38,
                                 squares[1].y_start + 20);
    }
    // 2
    if (input[0][2] >= 0)
    {
        textrenderer.render_text(map_player(input[0][2]),
                                 squares[2].x_start + 38,
                                 squares[2].y_start + 20);
    }
    // 3
    if (input[1][0] >= 0)
    {
        textrenderer.render_text(map_player(input[1][0]),
                                 squares[3].x_start + 38,
                                 squares[3].y_start + 20);
    }
    // 4
    if (input[1][1] >= 0)
    {
        textrenderer.render_text(map_player(input[1][1]),
                                 squares[4].x_start + 38,
                                 squares[4].y_start + 20);
    }
    // 5
    if (input[1][2] >= 0)
    {
        textrenderer.render_text(map_player(input[1][2]),
                                 squares[5].x_start + 38,
                                 squares[5].y_start + 20);
    }
    // 6
    if (input[2][0] >= 0)
    {
        textrenderer.render_text(map_player(input[2][0]),
                                 squares[6].x_start + 38,
                                 squares[6].y_start + 20);
    }
    // 7
    if (input[2][1] >= 0)
    {
        textrenderer.render_text(map_player(input[2][1]),
                                 squares[7].x_start + 38,
                                 squares[7].y_start + 20);
    }
    // 8
    if (input[2][2] >= 0)
    {
        textrenderer.render_text(map_player(input[2][2]),
                                 squares[8].x_start + 38,
                                 squares[8].y_start + 20);
    }
}

void Game::process_input(int last_mouse_x, int last_mouse_y,
                         std::map<int, Square>& squares, END_GAME_STATES& current_player,
                         int& turn)
{

    if (curr_mouse_state == GLFW_PRESS && prev_mouse_state == GLFW_RELEASE)
    {
        // first column inputs
        if (last_mouse_x >= squares[0].x_start &&
            last_mouse_x <= squares[0].x_end)
        {
            if (last_mouse_y >= squares[0].y_start &&
                last_mouse_y <= squares[0].y_end)
            {
                if (input[0][0] < 0)
                {
                    input[0][0] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
            if (last_mouse_y >= squares[3].y_start &&
                last_mouse_y <= squares[3].y_end)
            {
                if (input[1][0] < 0)
                {
                    input[1][0] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
            if (last_mouse_y >= squares[6].y_start &&
                last_mouse_y <= squares[6].y_end)
            {
                if (input[2][0] < 0)
                {
                    input[2][0] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
        }

        // second column inputs
        if (last_mouse_x >= squares[1].x_start &&
            last_mouse_x <= squares[1].x_end)
        {
            if (last_mouse_y >= squares[0].y_start &&
                last_mouse_y <= squares[0].y_end)
            {
                if (input[0][1] < 0)
                {
                    input[0][1] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
            if (last_mouse_y >= squares[3].y_start &&
                last_mouse_y <= squares[3].y_end)
            {
                if (input[1][1] < 0)
                {
                    input[1][1] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
            if (last_mouse_y >= squares[6].y_start &&
                last_mouse_y <= squares[6].y_end)
            {
                if (input[2][1] < 0)
                {
                    input[2][1] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
        }

        // third column inputs
        if (last_mouse_x >= squares[2].x_start &&
            last_mouse_x <= squares[2].x_end)
        {
            if (last_mouse_y >= squares[0].y_start &&
                last_mouse_y <= squares[0].y_end)
            {
                if (input[0][2] < 0)
                {
                    input[0][2] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
            if (last_mouse_y >= squares[3].y_start &&
                last_mouse_y <= squares[3].y_end)
            {
                if (input[1][2] < 0)
                {
                    input[1][2] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
            if (last_mouse_y >= squares[6].y_start &&
                last_mouse_y <= squares[6].y_end)
            {
                if (input[2][2] < 0)
                {
                    input[2][2] = current_player;
                    current_player = next_player(current_player,
                                                 turn);
                }
            }
        }
    }
}

END_GAME_STATES Game::next_player(END_GAME_STATES current_player, int& turn)
{
    turn++;
    if (current_player == END_GAME_STATES::X)
    {
        return END_GAME_STATES::O;
    } else
    {
        return END_GAME_STATES::X;
    }
}

void Game::reset(int& turn, END_GAME_STATES& current_player,
                 GAME_STATE& current_game_state)
{
    // reset game
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            input[i][j] = -1;
        }
    }
    turn = 0;
    current_player = END_GAME_STATES::X;
    current_game_state = GAME_STATE::GAME;
    prev_mouse_state = curr_mouse_state;
}

END_GAME_STATES Game::find_winner()
{
    for (int player = 0; player < 2; player++)
    {
        // horizontal checks
        if (input[0][0] == player && input[0][1] == player &&
            input[0][2] == player)
        {
            return static_cast<END_GAME_STATES>(player);
        }
        if (input[1][0] == player && input[1][1] == player &&
            input[1][2] == player)
        {
            return static_cast<END_GAME_STATES>(player);
        }
        if (input[2][0] == player && input[2][1] == player &&
            input[2][2] == player)
        {
            return static_cast<END_GAME_STATES>(player);
        }
        // vertical checks
        if (input[0][0] == player && input[1][0] == player &&
            input[2][0] == player)
        {
            return static_cast<END_GAME_STATES>(player);
        }
        if (input[0][1] == player && input[1][1] == player &&
            input[2][1] == player)
        {
            return static_cast<END_GAME_STATES>(player);
        }
        if (input[0][2] == player && input[1][2] == player &&
            input[2][2] == player)
        {
            return static_cast<END_GAME_STATES>(player);
        }
        // cross checks
        if (input[0][0] == player && input[1][1] == player &&
            input[2][2] == player)
        {
            return static_cast<END_GAME_STATES>(player);
        }
        if (input[0][2] == player && input[1][1] == player &&
            input[2][0] == player)
        {
            return static_cast<END_GAME_STATES>(player);
        }
    }
    return END_GAME_STATES::DRAW;
}

void Game::set_color_dark()
{
    text_color[0] = 0.2f;
    text_color[1] = 0.2f;
    text_color[2] = 0.2f;
    text_color[3] = 0.2f;
}

void Game::set_color_light()
{
    text_color[0] = 1.0f;
    text_color[1] = 1.0f;
    text_color[2] = 1.0f;
    text_color[3] = 1.0f;
}

void
Game::draw_endgame_text(END_GAME_STATES end_state,
                        std::string x_win_text, std::string o_win_text,
                        std::pair<int, int> x_win_text_size,
                        std::pair<int, int> o_win_text_size,
                        std::pair<int, int> end_text_size,
                        std::pair<int, int> draw_text_size,
                        gl_textrenderer& end_text_renderer,
                        std::string end_text, std::string draw_text
)
{
    if (end_state != END_GAME_STATES::DRAW)
    {
        end_text_renderer.render_text(
                (end_state == 1 ? x_win_text
                                : o_win_text),
                screen_width / 2 -
                ((end_state == 1 ? x_win_text_size.first
                                 : o_win_text_size.first)) /
                2,
                screen_height / 2 -
                ((end_state == 1 ? x_win_text_size.second
                                 : o_win_text_size.second)) /
                2 +
                20
        );
        end_text_renderer.render_text(end_text, screen_width / 2 -
                                                end_text_size.first /
                                                2,
                                      screen_height / 2 -
                                      end_text_size.second / 2 + 2);
    } else
    {
        end_text_renderer.render_text(draw_text,
                                      screen_width / 2 -
                                      draw_text_size.first / 2,
                                      screen_height / 2 -
                                      draw_text_size.second / 2 + 20
        );
        end_text_renderer.render_text(end_text,
                                      screen_width / 2 -
                                      end_text_size.first / 2,
                                      screen_height / 2 -
                                      end_text_size.second / 2 + 2
        );
    }
}

Game::Game(int screen_width, int screen_height)
    : screen_width(screen_width), screen_height(screen_height)
{

}
