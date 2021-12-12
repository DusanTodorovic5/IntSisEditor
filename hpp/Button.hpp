#ifndef BUTTON_CLASS
#define BUTTON_CLASS
#include "Node.hpp"
#include <string>
#include <Manager.hpp>
#include <iostream>
class Button: public Node{
    public:
        Button(int x, int y, std::string text, std::string texture_name);
        virtual void clicked() = 0;
        virtual bool checkHovered(sf::Vector2i) const;
        virtual void hovered();
        virtual void hoveredExit();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    protected:
        sf::RectangleShape shape; //240 width //10 dugmeta //height 96
    private:
        std::string text;
        std::string texture_name;
        int x;
        int y;
        sf::Color color;
};

#endif