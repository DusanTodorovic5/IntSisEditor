#ifndef BUTTON_CLASS
#define BUTTON_CLASS
#include <SFML/Graphics.hpp>
#include <string>
#include <Manager.hpp>
#include <iostream>
class Button: public sf::Drawable{
    public:
        Button(int x, int y, std::string text, std::string texture_name);
        virtual void onClick() = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::RectangleShape shape; //240 width //10 dugmeta //height 96
        std::string text;
        std::string texture_name;
        int x;
        int y;


};

#endif