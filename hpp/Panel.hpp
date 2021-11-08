#ifndef PANEL_CLASS
#define PANEL_CLASS
#include <SFML/Graphics.hpp>
#include "TexturedButton.hpp"
#include "ExportButton.hpp"
const int BUTTON_SIZE_X = 240;
const int BUTTON_SIZE_Y = 96; 
class Panel: public sf::Drawable{
    public:
        Panel(int x, int y);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void onClick();
        ~Panel();
    private:
        Button *buttons[10];
        int x;
        int y;

};

#endif
