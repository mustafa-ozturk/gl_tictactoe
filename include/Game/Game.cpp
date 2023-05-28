#include "Game.h"

void Game::draw_lines(int screen_width, int screen_height)
{
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
                      std::map<int, Square>& squares)
{
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
        // TODO: make a function to replace the X or O check
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
