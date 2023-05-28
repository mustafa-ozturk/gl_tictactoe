#include "Square.h"

std::map<int, Square> Square::create_squares(int screen_width,
                                             int screen_height)
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
    zero.x_end = screen_width / 3;
    zero.y_start = screen_height - screen_height / 3;
    zero.y_end = screen_height;
    squares.insert({0, zero});

    Square one{}; // 1
    one.x_start = screen_width / 3;
    one.x_end = screen_width - screen_width / 3;
    one.y_start = screen_height - screen_height / 3;
    one.y_end = screen_height;
    squares.insert({1, one});

    Square two{}; // 2
    two.x_start = screen_width - screen_width / 3;
    two.x_end = screen_width;
    two.y_start = screen_height - screen_height / 3;
    two.y_end = screen_height;
    squares.insert({2, two});

    Square three{};
    three.x_start = 0;
    three.x_end = screen_width / 3;
    three.y_start = screen_height / 3;
    three.y_end = screen_height - screen_height / 3;
    squares.insert({3, three});

    Square four{};
    four.x_start = screen_width / 3;
    four.x_end = screen_width - screen_width / 3;
    four.y_start = screen_height / 3;
    four.y_end = screen_height - screen_height / 3;
    squares.insert({4, four});

    Square five{};
    five.x_start = screen_width - screen_width / 3;
    five.x_end = screen_width;
    five.y_start = screen_height / 3;
    five.y_end = screen_height - screen_height / 3;
    squares.insert({5, five});

    Square six{}; // 6
    six.x_start = 0;
    six.x_end = screen_width / 3;
    six.y_start = 0;
    six.y_end = screen_height / 3;
    squares.insert({6, six});

    Square seven{}; // 7
    seven.x_start = screen_width / 3;
    seven.x_end = screen_width - screen_width / 3;
    seven.y_start = 0;
    seven.y_end = screen_height / 3;
    squares.insert({7, seven});

    Square eight{}; // 8
    eight.x_start = screen_width - screen_width / 3;
    eight.x_end = screen_width;
    eight.y_start = 0;
    eight.y_end = screen_height / 3;
    squares.insert({8, eight});

    return squares;
}
