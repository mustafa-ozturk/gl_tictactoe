#include <iostream>
#include <unistd.h>
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "gl_textrenderer/gl_textrenderer.h"
#include "gl_gridlines/gl_gridlines.h"
#include "Square/Square.h"
#include "Game/Game.h"
#include "Shader/Shader.h"

using namespace gl;

const unsigned int SCREEN_WIDTH = 510;
const unsigned int SCREEN_HEIGHT = 510;

enum Player
{
    O, X, DRAW
};

enum GAME_STATE
{
    GAME, END
};


std::map<int, Square> create_squares();

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Player next_player(Player current_player, int& turn);

Player find_winner(int input[3][3]);

int last_mouse_x = 0;
int last_mouse_y = 0;

int prev_mouse_state = GLFW_RELEASE;

int main()
{
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                          "gl_tictactoe", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);

    glbinding::initialize(glfwGetProcAddress);

    std::map<int, Square> squares = create_squares();

    gl_gridlines gridlines(SCREEN_WIDTH, SCREEN_HEIGHT, 10, {1.0f, 0.5f, 0.2f});


    Shader shader;
    unsigned int shaderProgram = shader.get_shader_program();
    glUseProgram(shaderProgram);
    glm::mat4 projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, 0.0f,
                                      (float) SCREEN_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1,
                       GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 1.0f, 1.0f);

    int input[3][3] = {
            {-1, -1, -1},
            {-1, -1, -1},
            {-1, -1, -1}
    };

    Player current_player = Player::X;
    GAME_STATE current_game_state = GAME_STATE::GAME;
    int turn = 0;
    float text_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    gl_textrenderer end_text_renderer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                      "assets/UbuntuMono-R.ttf", 20,
                                      {0.0f, 1.0f, 0.8f, 1.0f});
    std::string end_text = "click anywhere to replay";
    auto end_text_size = end_text_renderer.get_text_size(end_text);
    std::string draw_text = "DRAW!";
    auto draw_text_size = end_text_renderer.get_text_size(draw_text);
    std::string x_win_text = "X WINS!";
    auto x_win_text_size = end_text_renderer.get_text_size(x_win_text);
    std::string o_win_text = "O WINS!";
    auto o_win_text_size = end_text_renderer.get_text_size(o_win_text);

    Game game;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // this is terrible to do just for changing color
        // FIXME: add color param to draw call of gl_textrenderer
        gl_textrenderer textrenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                     "assets/UbuntuMono-R.ttf", 208,
                                     {text_color[0], text_color[1],
                                      text_color[2], text_color[3]});

        glUseProgram(shaderProgram);
        int curr_mouse_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
        switch (current_game_state)
        {
            case GAME_STATE::GAME:
                if (curr_mouse_state == GLFW_PRESS &&
                    prev_mouse_state == GLFW_RELEASE)
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
                glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f,
                            1.0f, 1.0f);
                text_color[0] = 1.0f;
                text_color[1] = 1.0f;
                text_color[2] = 1.0f;
                text_color[3] = 1.0f;
                break;
            case GAME_STATE::END:
                if (curr_mouse_state == GLFW_PRESS &&
                    prev_mouse_state == GLFW_RELEASE)
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
                    current_player = Player::X;
                    current_game_state = GAME_STATE::GAME;
                    prev_mouse_state = curr_mouse_state;
                    break;
                }

                glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.2f,
                            0.2f, 0.2f);
                text_color[0] = 0.2f;
                text_color[1] = 0.2f;
                text_color[2] = 0.2f;
                text_color[3] = 0.2f;
        }
        prev_mouse_state = curr_mouse_state;

        game.draw_lines(SCREEN_WIDTH, SCREEN_HEIGHT);

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
            textrenderer.render_text(input[0][0] == 1 ? "X" : "O",
                                     squares[0].x_start + 38,
                                     squares[0].y_start + 20);
        }
        // 1
        if (input[0][1] >= 0)
        {
            textrenderer.render_text(input[0][1] == 1 ? "X" : "O",
                                     squares[1].x_start + 38,
                                     squares[1].y_start + 20);
        }
        // 2
        if (input[0][2] >= 0)
        {
            textrenderer.render_text(input[0][2] == 1 ? "X" : "O",
                                     squares[2].x_start + 38,
                                     squares[2].y_start + 20);
        }
        // 3
        if (input[1][0] >= 0)
        {
            textrenderer.render_text(input[1][0] == 1 ? "X" : "O",
                                     squares[3].x_start + 38,
                                     squares[3].y_start + 20);
        }
        // 4
        if (input[1][1] >= 0)
        {
            textrenderer.render_text(input[1][1] == 1 ? "X" : "O",
                                     squares[4].x_start + 38,
                                     squares[4].y_start + 20);
        }
        // 5
        if (input[1][2] >= 0)
        {
            textrenderer.render_text(input[1][2] == 1 ? "X" : "O",
                                     squares[5].x_start + 38,
                                     squares[5].y_start + 20);
        }
        // 6
        if (input[2][0] >= 0)
        {
            textrenderer.render_text(input[2][0] == 1 ? "X" : "O",
                                     squares[6].x_start + 38,
                                     squares[6].y_start + 20);
        }
        // 7
        if (input[2][1] >= 0)
        {
            textrenderer.render_text(input[2][1] == 1 ? "X" : "O",
                                     squares[7].x_start + 38,
                                     squares[7].y_start + 20);
        }
        // 8
        if (input[2][2] >= 0)
        {
            textrenderer.render_text(input[2][2] == 1 ? "X" : "O",
                                     squares[8].x_start + 38,
                                     squares[8].y_start + 20);
        }

        if (turn == 9 && find_winner(input) == Player::DRAW)
        {
            current_game_state = GAME_STATE::END;
            end_text_renderer.render_text(draw_text,
                                          SCREEN_WIDTH / 2 -
                                          draw_text_size.first / 2,
                                          SCREEN_HEIGHT / 2 -
                                          draw_text_size.second / 2 + 20
            );
            end_text_renderer.render_text(end_text,
                                          SCREEN_WIDTH / 2 -
                                          end_text_size.first / 2,
                                          SCREEN_HEIGHT / 2 -
                                          end_text_size.second / 2 + 2
            );
        } else if (turn != 0 && find_winner(input) != Player::DRAW)
        {
            current_game_state = GAME_STATE::END;
            end_text_renderer.render_text(
                    (find_winner(input) == 1 ? x_win_text : o_win_text),
                    SCREEN_WIDTH / 2 -
                    ((find_winner(input) == 1 ? x_win_text_size.first
                                              : x_win_text_size.first)) / 2,
                    SCREEN_HEIGHT / 2 -
                    ((find_winner(input) == 1 ? x_win_text_size.second
                                              : x_win_text_size.second)) / 2 +
                    20
            );
            end_text_renderer.render_text(end_text, SCREEN_WIDTH / 2 -
                                                    end_text_size.first / 2,
                                          SCREEN_HEIGHT / 2 -
                                          end_text_size.second / 2 + 2);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

std::map<int, Square> create_squares()
{
    /*
     * 0 | 1 | 2
     * --|---|--
     * 3 | 4 | 5
     * --|---|--
     * 6 | 7 | 8
     * */
    std::map<int, Square> squares = {};

    Square zero{}; // 0
    zero.x_start = 0;
    zero.x_end = SCREEN_WIDTH / 3;
    zero.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    zero.y_end = SCREEN_HEIGHT;
    squares.insert({0, zero});

    Square one{}; // 1
    one.x_start = SCREEN_WIDTH / 3;
    one.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    one.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    one.y_end = SCREEN_HEIGHT;
    squares.insert({1, one});

    Square two{}; // 2
    two.x_start = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    two.x_end = SCREEN_WIDTH;
    two.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    two.y_end = SCREEN_HEIGHT;
    squares.insert({2, two});

    Square three{};
    three.x_start = 0;
    three.x_end = SCREEN_WIDTH / 3;
    three.y_start = SCREEN_HEIGHT / 3;
    three.y_end = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({3, three});

    Square four{};
    four.x_start = SCREEN_WIDTH / 3;
    four.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    four.y_start = SCREEN_HEIGHT / 3;
    four.y_end = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({4, four});

    Square five{};
    five.x_start = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    five.x_end = SCREEN_WIDTH;
    five.y_start = SCREEN_HEIGHT / 3;
    five.y_end = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({5, five});

    Square six{}; // 6
    six.x_start = 0;
    six.x_end = SCREEN_WIDTH / 3;
    six.y_start = 0;
    six.y_end = SCREEN_HEIGHT / 3;
    squares.insert({6, six});

    Square seven{}; // 7
    seven.x_start = SCREEN_WIDTH / 3;
    seven.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    seven.y_start = 0;
    seven.y_end = SCREEN_HEIGHT / 3;
    squares.insert({7, seven});

    Square eight{}; // 8
    eight.x_start = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    eight.x_end = SCREEN_WIDTH;
    eight.y_start = 0;
    eight.y_end = SCREEN_HEIGHT / 3;
    squares.insert({8, eight});

    return squares;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    last_mouse_x = (int) xpos;
    last_mouse_y = (int) SCREEN_HEIGHT - (int) ypos;
}

Player next_player(Player current_player, int& turn)
{
    turn++;
    if (current_player == Player::X)
    {
        return Player::O;
    } else
    {
        return Player::X;
    }
}

Player find_winner(int input[3][3])
{
    for (int player = 0; player < 2; player++)
    {
        // horizontal checks
        if (input[0][0] == player && input[0][1] == player &&
            input[0][2] == player)
        {
            return static_cast<Player>(player);
        }
        if (input[1][0] == player && input[1][1] == player &&
            input[1][2] == player)
        {
            return static_cast<Player>(player);
        }
        if (input[2][0] == player && input[2][1] == player &&
            input[2][2] == player)
        {
            return static_cast<Player>(player);
        }
        // vertical checks
        if (input[0][0] == player && input[1][0] == player &&
            input[2][0] == player)
        {
            return static_cast<Player>(player);
        }
        if (input[0][1] == player && input[1][1] == player &&
            input[2][1] == player)
        {
            return static_cast<Player>(player);
        }
        if (input[0][2] == player && input[1][2] == player &&
            input[2][2] == player)
        {
            return static_cast<Player>(player);
        }
        // cross checks
        if (input[0][0] == player && input[1][1] == player &&
            input[2][2] == player)
        {
            return static_cast<Player>(player);
        }
        if (input[0][2] == player && input[1][1] == player &&
            input[2][0] == player)
        {
            return static_cast<Player>(player);
        }
    }

    return Player::DRAW;
}