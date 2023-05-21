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

const std::string vertex_shader_source = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;

        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * vec4(aPos.xy, 1, 1);
        }
)";

const std::string fragment_shader_source = R"(
        #version 330 core
        out vec4 FragColor;

        uniform vec3 color;

        void main()
        {
            FragColor = vec4(color.xyz, 1.0f);
        }
)";

struct Square {
    int x_start;
    int x_end;
    int y_start;
    int y_end;
};

std::map<int, Square> create_squares();
void draw_line(int x_start, int x_end, int y_start, int y_end);
unsigned int create_shader_program(const std::string& vertex_source, const std::string& fragment_source);

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

    unsigned int shaderProgram = create_shader_program(vertex_shader_source, fragment_shader_source);
    glUseProgram(shaderProgram);
    glm::mat4 projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, 0.0f, (float) SCREEN_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 1.0f, 1.0f);

    std::cout << squares.size() << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        gridlines.draw();

        glUseProgram(shaderProgram);
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 1.0f, 1.0f);
        // horizontal lines
        draw_line(0,
                  SCREEN_WIDTH,
                  SCREEN_HEIGHT / 3,
                  SCREEN_HEIGHT / 3
        );
        draw_line(0,
                  SCREEN_WIDTH,
                  SCREEN_HEIGHT - SCREEN_HEIGHT / 3,
                  SCREEN_HEIGHT - SCREEN_HEIGHT / 3
        );
        // vertical lines
        draw_line(SCREEN_WIDTH / 3,
                  SCREEN_WIDTH / 3,
                  0,
                  SCREEN_HEIGHT
        );
        draw_line(SCREEN_WIDTH - SCREEN_WIDTH / 3,
                  SCREEN_WIDTH - SCREEN_WIDTH / 3,
                  0,
                  SCREEN_HEIGHT
        );

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
    zero.y_end = SCREEN_HEIGHT / 3;
    squares.insert({0, zero});

    Square one{};
    one.x_start = SCREEN_WIDTH / 3;
    one.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    one.y_start = 0;
    one.y_end = SCREEN_HEIGHT / 3;
    squares.insert({1, one});

    Square two{};
    two.x_start = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    two.x_end = SCREEN_WIDTH;
    two.y_start = 0;
    two.y_end = SCREEN_HEIGHT / 3;
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

    Square six{};
    six.x_start = 0;
    six.x_end = SCREEN_WIDTH / 3;
    six.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    six.y_end = SCREEN_HEIGHT;
    squares.insert({6, six});

    Square seven{};
    seven.x_start = SCREEN_WIDTH / 3;
    seven.x_end = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    seven.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    seven.y_end = SCREEN_HEIGHT;
    squares.insert({7, seven});

    Square eight{};
    eight.x_start = SCREEN_WIDTH - SCREEN_WIDTH / 3;
    eight.x_end = SCREEN_WIDTH;
    eight.y_start = SCREEN_HEIGHT - SCREEN_HEIGHT / 3;
    eight.y_end = SCREEN_HEIGHT;
    squares.insert({8, eight});

    return squares;
}

void draw_line(int x_start, int x_end, int y_start, int y_end)
{
    /*
     * A --- B
     * */
    std::array<int, 8> vertices{
            x_start,    y_start,   // A
            x_end,      y_end,     // B
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(int), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 2 * sizeof(int), (const void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int create_shader_program(const std::string& vertex_source, const std::string& fragment_source)
{
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* c_str_vertex = vertex_source.c_str();
    glShaderSource(vertexShader, 1, &c_str_vertex, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* c_str_fragment = fragment_source.c_str();
    glShaderSource(fragmentShader, 1, &c_str_fragment, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}