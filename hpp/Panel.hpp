#ifndef PANEL_CLASS
#define PANEL_CLASS
#include "Node.hpp"
#include "TexturedButton.hpp"
#include "ExportButton.hpp"

class Scene;
class Panel: public Node{
    public:
        Panel(int x, int y, Scene* s = nullptr);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual bool checkHovered(sf::Vector2i) const;
        virtual void hovered();
        virtual void hoveredExit();
        virtual void clicked();
        ~Panel();
    private:
        Button *buttons[10];
        int x;
        int y;
        const int BUTTON_SIZE_X = 240;
        const int BUTTON_SIZE_Y = 96; 
};

#endif