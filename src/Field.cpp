#include "Field.hpp"

Field::Field(int x, int y){
    this->sprite.setTexture(Manager::getManager()->getTexture("blank"));
    this->sprite.setPosition(sf::Vector2f(x,y));
    this->sprite.setScale(0.25,0.25);
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite,states);
}

void Field::onClick(){
    this->sprite.setTexture(Manager::getManager()->getTexture(
        Manager::getManager()->getCurrent()
    ));
    this->texture = Manager::getManager()->getCurrent();
}

std::string Field::getTexture() const{
    return this->texture;
}
void Field::setTexture(std::string texture){
    this->sprite.setTexture(Manager::getManager()->getTexture(texture));
    this->texture = texture;
}