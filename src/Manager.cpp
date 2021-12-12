#include "Manager.hpp"
Manager* Manager::instance = nullptr;

Manager* Manager::getManager() {
    if (!instance)
        instance = new Manager();
    return instance;
}

Manager::Manager(){
    //texture loading
    textureMap.insert(std::pair<std::string, sf::Texture*>("agent", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("blank", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("dune", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("grass", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("mud", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("road", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("stone", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("water", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("x", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("hole", new sf::Texture()));
    textureMap.insert(std::pair<std::string, sf::Texture*>("roadspace", new sf::Texture()));

    textureMap["agent"]->loadFromFile("img/agent.png");
    textureMap["blank"]->loadFromFile("img/blank.png");
    textureMap["dune"]->loadFromFile("img/dune.png");
    textureMap["grass"]->loadFromFile("img/grass.png");
    textureMap["mud"]->loadFromFile("img/mud.png");
    textureMap["road"]->loadFromFile("img/road.png");
    textureMap["stone"]->loadFromFile("img/stone.png");
    textureMap["water"]->loadFromFile("img/water.png");
    textureMap["x"]->loadFromFile("img/x.png");
    textureMap["roadspace"]->loadFromFile("img/roadSpace.png");
    textureMap["hole"]->loadFromFile("img/hole.png");
    currentPressed = "blank";
    this->window = 0;
    font.loadFromFile("font.ttf");
}
sf::Texture& Manager::getTexture(std::string name) const{
    return *(textureMap.at(name));
}

std::string Manager::getCurrent() const{
    return this->currentPressed;
}

void Manager::setWindow(sf::Window* window){
    this->window = window;
}
sf::Window& Manager::getWindow(){
    return *(this->window);
}

sf::Font& Manager::getFont(){
    return font;
}
void Manager::setCurrent(std::string texture_name){
    this->currentPressed = texture_name;
}

void Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if (sf::Mouse::getPosition(*window).x < 960){
        sf::Sprite sprite;
        sprite.setPosition(sf::Mouse::getPosition(*window).x - 20,sf::Mouse::getPosition(*window).y - 20);
        sprite.setScale(0.15625,0.15625);
        sprite.setTexture(getTexture(currentPressed));
        target.draw(sprite,states);
    }
}
void Manager::addGrid(Grid* grid){
    currentPressed = "blank";
    this->grid = grid;
}
Grid* Manager::getGrid(){
    return grid;
}