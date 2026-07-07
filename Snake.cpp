#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <random>
#include <algorithm>


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
        current_direction = Snake_Direction::RIGHT;
    }
};


class SnakeBody {
public:
    std::vector<std::pair<int, int>> body_position_list;

    void new_body_part(int x_pos, int y_pos) {
        body_position_list.push_back({ x_pos, y_pos });
    }

    void update_list(int pos_x, int pos_y) {
        std::pair<int, int> last_pair = { pos_x, pos_y };

        std::reverse(body_position_list.begin(), body_position_list.end());

        for (size_t i = 0; i < body_position_list.size() - 1; ++i) {
            body_position_list[i] = body_position_list[i + 1];
        }
        body_position_list.back() = last_pair;

        std::reverse(body_position_list.begin(), body_position_list.end());
    }

    void fill_field_snake_body(const std::vector<std::pair<int, int>>& body_position_list, auto& field) {
        for (size_t i = 0; i < body_position_list.size(); ++i) {
            int x_pos = body_position_list[i].first;
            int y_pos = body_position_list[i].second;

            if (i % 2 == 0) {
                field[y_pos][x_pos] = 2;
            }
            else {
                field[y_pos][x_pos] = 1;
            }
        }
    }

    void clear_tail(auto& field) {
        if (!body_position_list.empty()) {
            int tail_x = body_position_list.back().first;
            int tail_y = body_position_list.back().second;
            field[tail_y][tail_x] = 0;
        }
    }

    SnakeBody(int pos_x, int pos_y) {
        new_body_part(pos_x - 1, pos_y);
        new_body_part(pos_x - 2, pos_y);
    }
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
    const int FPS = 10;

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
    SnakeBody snake_body(5, 5);
    Fruit fruit(false);

    fruit.spawn_fruit(FIELD_WIDTH, FIELD_HEIGHT, field);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right && snake_head.current_direction != SnakeHead::Snake_Direction::LEFT) snake_head.current_direction = SnakeHead::Snake_Direction::RIGHT;
                if (event.key.code == sf::Keyboard::Left && snake_head.current_direction != SnakeHead::Snake_Direction::RIGHT) snake_head.current_direction = SnakeHead::Snake_Direction::LEFT;
                if (event.key.code == sf::Keyboard::Up && snake_head.current_direction != SnakeHead::Snake_Direction::DOWN) snake_head.current_direction = SnakeHead::Snake_Direction::UP;
                if (event.key.code == sf::Keyboard::Down && snake_head.current_direction != SnakeHead::Snake_Direction::UP) snake_head.current_direction = SnakeHead::Snake_Direction::DOWN;
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

        field[snake_head.snake_head_position_y][snake_head.snake_head_position_x] = 0;

        snake_body.clear_tail(field);

        if (snake_head.current_direction == SnakeHead::Snake_Direction::RIGHT) {
            if (snake_head.snake_head_position_x < FIELD_WIDTH - 1) {
                snake_body.update_list(snake_head.snake_head_position_x, snake_head.snake_head_position_y);
                snake_head.snake_head_position_x++;
            }
        }
        else if (snake_head.current_direction == SnakeHead::Snake_Direction::LEFT) {
            if (snake_head.snake_head_position_x > 0) {
                snake_body.update_list(snake_head.snake_head_position_x, snake_head.snake_head_position_y);
                snake_head.snake_head_position_x--;
            }
        }
        else if (snake_head.current_direction == SnakeHead::Snake_Direction::UP) {
            if (snake_head.snake_head_position_y > 0) {
                snake_body.update_list(snake_head.snake_head_position_x, snake_head.snake_head_position_y);
                snake_head.snake_head_position_y--;
            }
        }
        else if (snake_head.current_direction == SnakeHead::Snake_Direction::DOWN) {
            if (snake_head.snake_head_position_y < FIELD_HEIGHT - 1) {
                snake_body.update_list(snake_head.snake_head_position_x, snake_head.snake_head_position_y);
                snake_head.snake_head_position_y++;
            }
        }

        field[snake_head.snake_head_position_y][snake_head.snake_head_position_x] = 1;

        snake_body.fill_field_snake_body(snake_body.body_position_list, field);

        if (snake_head.snake_head_position_x == fruit.fruit_position_x && snake_head.snake_head_position_y == fruit.fruit_position_y) {
            fruit.spawn_fruit(FIELD_WIDTH, FIELD_HEIGHT, field);
            snake_body.new_body_part(snake_head.snake_head_position_x, snake_head.snake_head_position_y);
        }

        window.display();
    }
    return 0;
}
