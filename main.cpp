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

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int last_mouse_x = 0;
int last_mouse_y = 0;

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

    Square square;
    std::map<int, Square> squares = square.create_squares(SCREEN_WIDTH,
                                                          SCREEN_HEIGHT);

    Shader shader;
    unsigned int shaderProgram = shader.get_shader_program();
    glUseProgram(shaderProgram);
    glm::mat4 projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, 0.0f,
                                      (float) SCREEN_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1,
                       GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 1.0f, 1.0f);

    END_GAME_STATES current_player = END_GAME_STATES::X_WINS;
    GAME_STATE current_game_state = GAME_STATE::GAME;
    int turn = 0;

    gl_textrenderer end_text_renderer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                      "assets/UbuntuMono-R.ttf", 20,
                                      {0.0f, 1.0f, 0.8f, 1.0f});

    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // this is terrible to do just for changing color
        // FIXME: add color param to draw call of gl_textrenderer
        gl_textrenderer textrenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                     "assets/UbuntuMono-R.ttf", 208,
                                     {game.get_text_color()[0],
                                      game.get_text_color()[1],
                                      game.get_text_color()[2],
                                      game.get_text_color()[3]});
        const END_GAME_STATES end_state = game.find_winner();

        game.set_curr_mouse_state(
                glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1));
        switch (current_game_state)
        {
            case GAME_STATE::GAME:
                if (turn == 9 || end_state != END_GAME_STATES::DRAW)
                {
                    current_game_state = GAME_STATE::END;
                }
                game.process_input(last_mouse_x, last_mouse_y, squares,
                                   current_player, turn);
                game.set_color_light();

                game.draw_input(textrenderer, squares, shaderProgram);
                game.draw_lines(shaderProgram);
                break;
            case GAME_STATE::END:
                if (game.get_curr_mouse_state() == GLFW_PRESS &&
                    game.get_prev_mouse_state() == GLFW_RELEASE)
                {
                    game.reset(turn, current_player, current_game_state);
                    break;
                }
                game.set_color_dark();

                game.draw_input(textrenderer, squares, shaderProgram);
                game.draw_lines(shaderProgram);
                game.draw_endgame_text(end_state, end_text_renderer);
        }
        game.set_prev_mouse_state(game.get_curr_mouse_state());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    last_mouse_x = (int) xpos;
    last_mouse_y = (int) SCREEN_HEIGHT - (int) ypos;
}