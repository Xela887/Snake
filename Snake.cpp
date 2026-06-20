#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>


class SnakeHead {
public:
    SnakeHead(int pos_x, int pos_y) {
        snake_head_position_x = pos_x;
        snake_head_position_y = pos_y;
        Snake_Direction current_direction = Snake_Direction::RIGHT;
    }

    int snake_head_position_x;
    int snake_head_position_y;

    enum class Snake_Direction {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };
};


class SnakeBody {
public:
    std::vector<std::pair<int, int>> body_position_list;
};


class Fruit {
public:
    int fruit_position_x;
    int fruit_position_y;
};


int main() {
    const int FPS = 20;

    float window_width = 570;
    float window_height = 570;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Snake");
    window.setFramerateLimit(FPS);

    const int FIELD_WIDTH = 11;
    const int FIELD_HEIGHT = 11;
    const int CELL_SIZE = 50;
    const sf::Vector2f FIELD_OFFSET(10, 10);

    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setFillColor(sf::Color(40, 40, 40));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::White);

    sf::Color blockColors[] =
    {
        sf::Color(40, 40, 40),
        sf::Color::Green,
        sf::Color(11, 97, 31),
        sf::Color::Red,
    };

    int field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

    SnakeHead snake_head(5, 5);
    SnakeBody snake_body;
    Fruit fruit;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        for (int y = 0; y < FIELD_HEIGHT; y++) {
            for (int x = 0; x < FIELD_WIDTH; x++) {
                cell.setPosition(
                    FIELD_OFFSET.x + x * CELL_SIZE,
                    FIELD_OFFSET.y + y * CELL_SIZE
                );

                cell.setFillColor(blockColors[field[y][x]]);
                window.draw(cell);
            }
        }

        field[snake_head.snake_head_position_x][snake_head.snake_head_position_y] = 1;

        window.display();
    }
    return 0;
}
