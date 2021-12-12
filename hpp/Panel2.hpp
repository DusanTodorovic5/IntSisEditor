#ifndef PANEL2_CLASS
#define PANEL2_CLASS
#include "Node.hpp"
#include "TexturedButton.hpp"
#include "ExportButton.hpp"

class Scene;
class Panel2 : public Node{
    public:
        Panel2(int x, int y, Scene* s = nullptr);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual bool checkHovered(sf::Vector2i) const;
        virtual void hovered();
        virtual void hoveredExit();
        virtual void clicked();
        ~Panel2();
    private:
        Button *buttons[6];
        int x;
        int y;
        const int BUTTON_SIZE_X = 240;
        const int BUTTON_SIZE_Y = 96; 
};

#endif