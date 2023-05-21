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

enum Player {
    O, X
};


std::map<int, Square> create_squares();
void draw_line(int x_start, int x_end, int y_start, int y_end);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool is_mouse1_pressed(GLFWwindow* window);
Player next_player(Player current_player);
unsigned int create_shader_program(const std::string& vertex_source, const std::string& fragment_source);

int last_mouse_x = 0;
int last_mouse_y = 0;


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
    glfwSetCursorPosCallback(window, mouse_callback);

    glbinding::initialize(glfwGetProcAddress);

    std::map<int, Square> squares = create_squares();

    gl_gridlines gridlines(SCREEN_WIDTH, SCREEN_HEIGHT, 10, {1.0f, 0.5f, 0.2f});
    gl_textrenderer textrenderer(SCREEN_WIDTH, SCREEN_HEIGHT, "assets/UbuntuMono-R.ttf", 208, {1.0f, 1.0f, 1.0f, 1.1f});

    unsigned int shaderProgram = create_shader_program(vertex_shader_source, fragment_shader_source);
    glUseProgram(shaderProgram);
    glm::mat4 projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, 0.0f, (float) SCREEN_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 1.0f, 1.0f);

    int input[3][3] = {
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1}
    };

    Player current_player = Player::X;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        gridlines.draw();
        if (is_mouse1_pressed(window))
        {
            // first column inputs
            if (last_mouse_x >= squares[0].x_start && last_mouse_x <= squares[0].x_end)
            {
                if (last_mouse_y >= squares[0].y_start && last_mouse_y <= squares[0].y_end)
                {
                    if (input[0][0] < 0)
                    {
                        input[0][0] = current_player;
                        current_player = next_player(current_player);
                    }
                }
                if (last_mouse_y >= squares[3].y_start && last_mouse_y <= squares[3].y_end)
                {
                    if (input[1][0] < 0)
                    {
                        input[1][0] = current_player;
                        current_player = next_player(current_player);
                    }
                }
                if (last_mouse_y >= squares[6].y_start && last_mouse_y <= squares[6].y_end)
                {
                    if (input[2][0] < 0)
                    {
                        input[2][0] = current_player;
                        current_player = next_player(current_player);
                    }
                }
            }

            // second column inputs
            if (last_mouse_x >= squares[1].x_start && last_mouse_x <= squares[1].x_end)
            {
                if (last_mouse_y >= squares[0].y_start && last_mouse_y <= squares[0].y_end)
                {
                    if (input[0][1] < 0)
                    {
                        input[0][1] = current_player;
                        current_player = next_player(current_player);
                    }
                }
                if (last_mouse_y >= squares[3].y_start && last_mouse_y <= squares[3].y_end)
                {
                    if (input[1][1] < 0)
                    {
                        input[1][1] = current_player;
                        current_player = next_player(current_player);
                    }
                }
                if (last_mouse_y >= squares[6].y_start && last_mouse_y <= squares[6].y_end)
                {
                    if (input[2][1] < 0)
                    {
                        input[2][1] = current_player;
                        current_player = next_player(current_player);
                    }
                }
            }

            // third column inputs
            if (last_mouse_x >= squares[2].x_start && last_mouse_x <= squares[2].x_end)
            {
                if (last_mouse_y >= squares[0].y_start && last_mouse_y <= squares[0].y_end)
                {
                    if (input[0][2] < 0)
                    {
                        input[0][2] = current_player;
                        current_player = next_player(current_player);
                    }
                }
                if (last_mouse_y >= squares[3].y_start && last_mouse_y <= squares[3].y_end)
                {
                    if (input[1][2] < 0)
                    {
                        input[1][2] = current_player;
                        current_player = next_player(current_player);
                    }
                }
                if (last_mouse_y >= squares[6].y_start && last_mouse_y <= squares[6].y_end)
                {
                    if (input[2][2] < 0)
                    {
                        input[2][2] = current_player;
                        current_player = next_player(current_player);
                    }
                }
            }
        }

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
            textrenderer.render_text(input[0][0] == 1 ? "X" : "O", squares[0].x_start + 38, squares[0].y_start + 20);
        }
        // 1
        if (input[0][1] >= 0)
        {
            textrenderer.render_text(input[0][1] == 1 ? "X" : "O", squares[1].x_start + 38, squares[1].y_start + 20);
        }
        // 2
        if (input[0][2] >= 0)
        {
            textrenderer.render_text(input[0][2] == 1 ? "X" : "O", squares[2].x_start + 38, squares[2].y_start + 20);
        }
        // 3
        if (input[1][0] >= 0)
        {
            textrenderer.render_text(input[1][0] == 1 ? "X" : "O", squares[3].x_start + 38, squares[3].y_start + 20);
        }
        // 4
        if (input[1][1] >= 0)
        {
            textrenderer.render_text(input[1][1] == 1 ? "X" : "O", squares[4].x_start + 38, squares[4].y_start + 20);
        }
        // 5
        if (input[1][2] >= 0)
        {
            textrenderer.render_text(input[1][2] == 1 ? "X" : "O", squares[5].x_start + 38, squares[5].y_start + 20);
        }
        // 6
        if (input[2][0] >= 0)
        {
            textrenderer.render_text(input[2][0] == 1 ? "X" : "O", squares[6].x_start + 38, squares[6].y_start + 20);
        }
        // 7
        if (input[2][1] >= 0)
        {
            textrenderer.render_text(input[2][1] == 1 ? "X" : "O", squares[7].x_start + 38, squares[7].y_start + 20);
        }
        // 8
        if (input[2][2] >= 0)
        {
            textrenderer.render_text(input[2][2] == 1 ? "X" : "O", squares[8].x_start + 38, squares[8].y_start + 20);
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    last_mouse_x = (int)xpos;
    last_mouse_y = (int)SCREEN_HEIGHT - (int)ypos;
}

bool is_mouse1_pressed(GLFWwindow* window)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        return true;
    }
    return false;
}

Player next_player(Player current_player)
{
    if (current_player == Player::X)
    {
        return Player::O;
    }
    else
    {
        return Player::X;
    }
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