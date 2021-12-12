#include "Button.hpp"

Button::Button(int x, int y, std::string text, std::string texture_name){
    this->text = text;
    this->texture_name = texture_name;
    
    shape.setSize(sf::Vector2f(240,96));
    color = sf::Color(156, 156, 156);
    shape.setFillColor(color);
    shape.setPosition(x,y);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.5);
    this->x = x;
    this->y = y;

}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(shape,states);
    if (texture_name == ""){
        sf::Text text;
        text.setFont(Manager::getManager()->getFont());
        text.setString(this->text);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(40);
        
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
                textRect.top  + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(this->shape.getPosition().x + this->shape.getSize().x/2,
                this->shape.getPosition().y + this->shape.getSize().y/2));
        target.draw(text,states);
    }
    else{
        sf::Text text;
        text.setFont(Manager::getManager()->getFont());
        text.setString(this->text);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(30);
        
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
                textRect.top  + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(this->shape.getPosition().x + this->shape.getSize().x/2 - 35,
                this->shape.getPosition().y + this->shape.getSize().y/2));

        sf::Sprite sprite;
        sprite.setTexture(Manager::getManager()->getTexture(texture_name));
        sprite.setScale(0.25,0.25);
        sprite.setPosition(this->shape.getPosition().x + this->shape.getSize().x/2 + 35,
                this->shape.getPosition().y + this->shape.getSize().y/2 - 32);
        
        
        target.draw(text,states);
        target.draw(sprite,states);
    }
}
bool Button::checkHovered(sf::Vector2i vector) const{
        if (vector.x > this->shape.getGlobalBounds().left && 
                vector.x < this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width){
                if (vector.y > this->shape.getGlobalBounds().top && 
                vector.y < this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height){
                        return true;
                }
        }
        return false;
}
void Button::hovered(){
        shape.setFillColor(sf::Color(115, 115, 115));
}
void Button::hoveredExit(){
        shape.setFillColor(color);
}