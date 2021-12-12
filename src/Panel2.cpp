#include "Panel2.hpp"
#include "Scene.hpp"
Panel2::Panel2(int x, int y, Scene* s){
    this->x = x;
    this->y = y;
    s->add(this);
    int j = 0;
    buttons[j] = new TextureButton(960, BUTTON_SIZE_Y * j, "Agent", "agent"); s->add(buttons[j++]);
    buttons[j] = new TextureButton(960, BUTTON_SIZE_Y * j, "Goal", "x"); s->add(buttons[j++]);
    buttons[j] = new TextureButton(960, BUTTON_SIZE_Y * j, "Hole", "hole"); s->add(buttons[j++]);
    buttons[j] = new TextureButton(960, BUTTON_SIZE_Y * j, "RoadSpace", "roadspace"); s->add(buttons[j++]);
    buttons[j] = new TextureButton(960, BUTTON_SIZE_Y * j, "Delete", "blank"); s->add(buttons[j++]);
    buttons[j] = new ExportButton(960, BUTTON_SIZE_Y * j); s->add(buttons[j++]);
}

void Panel2::draw(sf::RenderTarget& target, sf::RenderStates states) const{
   // for (int i=0;i<10;i++){
    //    target.draw(*buttons[i],states);
   // }
}
Panel2::~Panel2(){
    /*for (int i=0;i<10;i++){
        delete buttons[i];
    }*/
}
bool Panel2::checkHovered(sf::Vector2i) const{
    return false;
}
void Panel2::hovered(){

}
void Panel2::hoveredExit(){

}
void Panel2::clicked(){
    //buttons[sf::Mouse::getPosition(
    //    Manager::getManager()->getWindow()).y/BUTTON_SIZE_Y]->clicked();
}