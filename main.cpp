#include <iostream>
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "gl_textrenderer/gl_textrenderer.h"
#include "gl_gridlines/gl_gridlines.h"

using namespace gl;

const unsigned int SCREEN_WIDTH = 510;
const unsigned int SCREEN_HEIGHT = 510;

struct Square {
    int x_start;
    int x_end;
    int y_start;
    int y_end;
};

std::map<int, Square> create_squares();
void draw_line(int x_start, int x_end, int y_start, int y_end);

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

    gl_gridlines gridlines(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH / 3, {1.0f, 0.5f, 0.2f});

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        gridlines.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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

    Square zero{};
    zero.x_start = 0;
    zero.x_end = SCREEN_WIDTH / 3;
    zero.y_start = 0;
    zero.y_start = SCREEN_HEIGHT / 3;
    squares.insert({0, zero});

    Square one{};
    one.x_start = SCREEN_WIDTH / 3;
    one.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    one.y_start = 0;
    one.y_start = SCREEN_HEIGHT / 3;
    squares.insert({1, one});

    Square two{};
    two.x_start = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    two.x_end = SCREEN_WIDTH;
    two.y_start = 0;
    two.y_start = SCREEN_HEIGHT / 3;
    squares.insert({2, two});

    Square three{};
    three.x_start = 0;
    three.x_end = SCREEN_WIDTH / 3;
    three.y_start = SCREEN_HEIGHT / 3;
    three.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({3, three});

    Square four{};
    four.x_start = SCREEN_WIDTH / 3;
    four.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    four.y_start = SCREEN_HEIGHT / 3;
    four.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({4, four});

    Square five{};
    five.x_start = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    five.x_end = SCREEN_WIDTH;
    five.y_start = SCREEN_HEIGHT / 3;
    five.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    squares.insert({5, five});

    Square six{};
    six.x_start = 0;
    six.x_end = SCREEN_WIDTH / 3;
    six.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    six.y_start = SCREEN_HEIGHT;
    squares.insert({6, six});

    Square seven{};
    seven.x_start = SCREEN_WIDTH / 3;
    seven.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    seven.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    seven.y_start = SCREEN_HEIGHT;
    squares.insert({7, seven});

    Square eight{};
    eight.x_start = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    eight.x_end = SCREEN_WIDTH;
    eight.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    eight.y_start = SCREEN_HEIGHT;
    squares.insert({8, eight});
}

void draw_line(int x_start, int x_end, int y_start, int y_end)
{
    /*
     * A --- B
     * */
    std::array<int, 8> vertices{
            x_start, y_start,   // A
            y_start, y_end,     // B
    };

    std::array<GLuint, 2> indices{
            0, 1,
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(int), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 2 * sizeof(GLuint), (const void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
