#include "Panel.hpp"
Panel::Panel(int x, int y){
    this->x = x;
    this->y = y;
    int j = 0;
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Agent", "agent");
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Goal", "x");
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Grass", "grass");
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Dune", "dune");
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Mud", "mud");
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Road", "road");
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Stone", "stone");
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Water", "water");
    buttons[j++] = new TextureButton(960, BUTTON_SIZE_Y * j, "Delete", "blank");
    buttons[j++] = new ExportButton(960, BUTTON_SIZE_Y * j);
}

void Panel::onClick(){
    buttons[sf::Mouse::getPosition(
        Manager::getManager()->getWindow()).y/BUTTON_SIZE_Y]->onClick();
}
void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for (int i=0;i<10;i++){
        target.draw(*buttons[i],states);
    }
}