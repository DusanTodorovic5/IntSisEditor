#include "Field.hpp"

Field::Field(int x, int y){
    this->sprite.setTexture(Manager::getManager()->getTexture("blank"));
    this->sprite.setPosition(sf::Vector2f(x,y));
    this->sprite.setScale(0.25,0.25);
    this->color = sprite.getColor();
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite,states);
}
std::string Field::getTexture() const{
    return this->texture;
}
void Field::setTexture(std::string texture){
    this->sprite.setTexture(Manager::getManager()->getTexture(texture));
    this->texture = texture;
}
bool Field::checkHovered(sf::Vector2i vector) const{
    if (vector.x > sprite.getGlobalBounds().left && vector.x < sprite.getGlobalBounds().width + sprite.getGlobalBounds().left){
        if (vector.y > sprite.getGlobalBounds().top && vector.y < sprite.getGlobalBounds().height + sprite.getGlobalBounds().top){
            return true;
        }
    }
    return false;
}
void Field::hovered(){
    sprite.setColor(sf::Color(207, 207, 207));
}
void Field::hoveredExit(){
    sprite.setColor(this->color);
}
void Field::clicked(){
    this->sprite.setTexture(Manager::getManager()->getTexture(
        Manager::getManager()->getCurrent()
    ));
    this->texture = Manager::getManager()->getCurrent();
}