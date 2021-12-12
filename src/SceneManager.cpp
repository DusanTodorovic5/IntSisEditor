#include "SceneManager.hpp"
#include "Scene.hpp"
#include <iostream>
#include "Manager.hpp"
SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::manager(){
    if (!instance){
        instance = new SceneManager();
    }
    return instance;
}
SceneManager::SceneManager(){
    currScene = "";
}
void SceneManager::switchScene(std::string scene){
    if (scene != currScene){
        currScene = scene;
        Manager::getManager()->addGrid(scenes.at(currScene)->getGrid());
    }
    
}
void SceneManager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if (currScene != "")
    target.draw(*(scenes.at(currScene)),states);
}
void SceneManager::addScene(std::string sceneName, Scene* scene){
    scenes.insert(std::pair<std::string, Scene*>(sceneName,scene));
}
void SceneManager::clicked(){
    if (currScene != "")
        scenes.at(currScene)->clicked();
}
void SceneManager::mouseMoved(sf::Vector2i vector){
    if (currScene != "")
        scenes.at(currScene)->mouseMoved(vector);
}
SceneManager::~SceneManager(){
    for (std::pair<std::string, Scene*> s : this->scenes){
        delete s.second;
    }
}