#include <SFML/Graphics.hpp>
#include "Grid.hpp"

int main()
{
    Grid grid;
    grid.reset();
    sf::RenderWindow window(sf::VideoMode({ 1080, 1080 }), "SFML works!");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        grid.draw(window);
        window.display();
    }
}