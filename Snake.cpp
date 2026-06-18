#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>


int main() {
    const int FPS = 60;

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
        sf::Color::Red,
    };

    int field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

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

        window.display();
    }
    return 0;
}