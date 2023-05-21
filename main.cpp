#include <iostream>
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "gl_textrenderer/gl_textrenderer.h"
#include "gl_gridlines/gl_gridlines.h"

using namespace gl;

const unsigned int SCREEN_WIDTH = 500;
const unsigned int SCREEN_HEIGHT = 500;

struct Square {
    int x_begin;
    int x_end;
    int y_begin;
    int y_end;
};

std::map<int, Square> create_squares();

int main()
{
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "gl_tictactoe", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glbinding::initialize(glfwGetProcAddress);

    std::map<int, Square> squares = create_squares();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

std::map<int, Square> create_squares()
{
    /*
     * 6 | 7 | 8
     * --|---|--
     * 3 | 4 | 5
     * --|---|--
     * 0 | 1 | 2
     * */
    std::map<int, Square> squares = {};

    Square zero;
    zero.x_begin = 0;
    zero.x_end = SCREEN_WIDTH / 3;
    zero.y_begin = 0;
    zero.y_begin = SCREEN_HEIGHT / 3;
    squares.insert({0, zero});

    Square one;
    one.x_begin = SCREEN_WIDTH / 3;
    one.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    one.y_begin = 0;
    one.y_begin = SCREEN_HEIGHT / 3;
    squares.insert({1, one});

    Square two;
    two.x_begin = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    two.x_end = SCREEN_WIDTH;
    two.y_begin = 0;
    two.y_begin = SCREEN_HEIGHT / 3;
    squares.insert({2, two});

    Square three;
    three.x_begin = 0;
    three.x_end = SCREEN_WIDTH / 3;
    three.y_begin = SCREEN_HEIGHT / 3;
    three.y_begin = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({3, three});

    Square four;
    four.x_begin = SCREEN_WIDTH / 3;
    four.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    four.y_begin = SCREEN_HEIGHT / 3;
    four.y_begin = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({4, four});

    Square five;
    five.x_begin = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    five.x_end = SCREEN_WIDTH;
    five.y_begin = SCREEN_HEIGHT / 3;
    five.y_begin = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({5, five});

    Square six;
    six.x_begin = 0;
    six.x_end = SCREEN_WIDTH / 3;
    six.y_begin = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    six.y_begin = SCREEN_HEIGHT;
    squares.insert({6, six});

    Square seven;
    seven.x_begin = SCREEN_WIDTH / 3;
    seven.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    seven.y_begin = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    seven.y_begin = SCREEN_HEIGHT;
    squares.insert({7, seven});

    Square eight;
    eight.x_begin = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    eight.x_end = SCREEN_WIDTH;
    eight.y_begin = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    eight.y_begin = SCREEN_HEIGHT;
    squares.insert({8, eight});
}