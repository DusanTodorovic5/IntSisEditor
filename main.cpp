#include "Grid.hpp"
#include "Button.hpp"
#include "Panel.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 960), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Grid grid(0,0);
    Panel panel(960,0);
    Manager::getManager()->setWindow(&window);
    Manager::getManager()->addGrid(&grid);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).y < window.getSize().y){
                if (sf::Mouse::getPosition(window).x < grid.getWidth() && sf::Mouse::getPosition(window).y > 0)
                    grid.onClick();
                if (sf::Mouse::getPosition(window).x > 960 && sf::Mouse::getPosition(window).y > 0)
                    panel.onClick();
            }
            
        }

        window.clear();
        window.draw(shape);
        window.draw(grid);
        window.draw(panel);
        window.draw(*(Manager::getManager()));
        window.display();
    }

    return 0;
}