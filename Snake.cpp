#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <random>


class SnakeHead {
public:
    enum class Snake_Direction {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

    int snake_head_position_x;
    int snake_head_position_y;
    Snake_Direction current_direction;

    SnakeHead(int pos_x, int pos_y) {
        snake_head_position_x = pos_x;
        snake_head_position_y = pos_y;
        Snake_Direction current_direction = Snake_Direction::RIGHT;
    }
};


class SnakeBody {
public:
    std::vector<std::pair<int, int>> body_position_list;
};


class Fruit {
public:
    int fruit_position_x;
    int fruit_position_y;
    bool fruit_spawned;
     
    void spawn_fruit(int max_width, int max_height, int field[11][11]) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrX(0, max_width - 1);
        std::uniform_int_distribution<> distrY(0, max_height - 1);

        fruit_position_x = distrX(gen);
        fruit_position_y = distrY(gen);

        field[fruit_position_y][fruit_position_x] = 3;
        fruit_spawned = true;
    }

    Fruit(bool fruitspawned) {
        fruit_spawned = fruitspawned;
        fruit_position_x = 0;
        fruit_position_y = 0;
    }
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
    Fruit fruit(false);

    fruit.spawn_fruit(FIELD_WIDTH, FIELD_HEIGHT, field);

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

        field[snake_head.snake_head_position_y][snake_head.snake_head_position_x] = 1;

        window.display();
    }
    return 0;
}
