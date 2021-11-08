#ifndef FIELD_CLASS
#define FIELD_CLASS
#include <SFML/Graphics.hpp>
#include "Manager.hpp"
class Field : public sf::Drawable{
    public:
        Field(int x, int y);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void onClick();
        std::string getTexture() const;
        void setTexture(std::string texture="blank");
    private:
        sf::Sprite sprite;
        std::string texture;
};

#endif