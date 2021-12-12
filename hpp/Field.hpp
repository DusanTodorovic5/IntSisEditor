#ifndef FIELD_CLASS
#define FIELD_CLASS
#include "Node.hpp"
#include "Manager.hpp"
class Field : public Node{
    public:
        Field(int x, int y);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual bool checkHovered(sf::Vector2i) const;
        virtual void hovered();
        virtual void hoveredExit();
        virtual void clicked();
        void onClick();
        std::string getTexture() const;
        void setTexture(std::string texture="blank");
    private:
        sf::Sprite sprite;
        std::string texture;
        sf::Color color;
};

#endif