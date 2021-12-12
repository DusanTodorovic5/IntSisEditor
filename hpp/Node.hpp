#ifndef NODE_CLASS
#define NODE_CLASS

#include <SFML/Graphics.hpp>
class Node : public sf::Drawable{
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        virtual bool checkHovered(sf::Vector2i) const = 0;
        virtual void hovered() = 0;
        virtual void hoveredExit() = 0;
        virtual void clicked() = 0;
};

#endif