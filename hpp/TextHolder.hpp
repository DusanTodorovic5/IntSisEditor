#ifndef TEXT_HOLDER
#define TEXT_HOLDER

#include "Node.hpp"
#include "Manager.hpp"

class TextHolder : public Node{
    public: 
        TextHolder(int x, int y){
            text.setFont(Manager::getManager()->getFont());
            text.setCharacterSize(120);
            text.setFillColor(sf::Color::White);
            text.setString("Izaberite Editor");
            text.setPosition(sf::Vector2f(x - text.getGlobalBounds().width/2,y - text.getGlobalBounds().height/2));
        }
        virtual bool checkHovered(sf::Vector2i vector) const{
            if (vector.x > text.getGlobalBounds().left && vector.x < text.getGlobalBounds().left + text.getGlobalBounds().width){
                if (vector.y > text.getGlobalBounds().top && vector.y < text.getGlobalBounds().top + text.getGlobalBounds().height){
                return true;
                }
            }
            return false;
        }
        virtual void hovered(){
            text.setFillColor(sf::Color::Yellow);
        }
        virtual void hoveredExit(){
            text.setFillColor(sf::Color::White);
        }
        virtual void clicked(){

        }
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
            target.draw(text,states);
        }
    private:
        sf::Text text;
        int x;
        int y;
};

#endif