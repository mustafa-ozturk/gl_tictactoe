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
