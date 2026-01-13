#include <SFML/Graphics.hpp>
#include "Grid.hpp"

int main()
{
    Grid grid;
    grid.reset();

    sf::RenderWindow window(sf::VideoMode({ Grid::SIZE * Grid::TILE_SIZE,
        Grid::SIZE * Grid::TILE_SIZE }),
        "SFML Chess");

    while (window.isOpen())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            grid.handleClick(sf::Mouse::getPosition(window));
            sf::sleep(sf::milliseconds(150)); // petit délai pour éviter les multiples clics
        }

        if (!window.isOpen()) break; // permet de quitter

        window.clear();
        grid.draw(window);
        window.display();
    }
}
