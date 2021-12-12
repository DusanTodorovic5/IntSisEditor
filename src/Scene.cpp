#include "Scene.hpp"
#include "Node.hpp"
#include "Manager.hpp"
#include <iostream>
Scene::Scene(){
    currHovered = nullptr;
}
void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for (int i=0;i<nodes.size();i++){
        target.draw(*(nodes[i]),states);
    }
    target.draw(*(Manager::getManager()),states);
}
void Scene::add(Node* node){
    nodes.push_back(node);
}
void Scene::clicked(){
    if (currHovered != nullptr){
        currHovered->clicked();
    }
}
void Scene::mouseMoved(sf::Vector2i vector){
    for (int i=0;i<nodes.size();i++){
        if (nodes[i]->checkHovered(vector)){
            if (currHovered && currHovered != nodes[i]){
                currHovered->hoveredExit();
                currHovered = nodes[i];
                currHovered->hovered();
            }
            else if (!currHovered){
                currHovered = nodes[i];
                currHovered->hovered();
            }
            return;
        }
    }
    if (currHovered != nullptr)
        currHovered->hoveredExit();
    currHovered = nullptr;
}
Grid* Scene::getGrid(){
    return grid;
}
void Scene::setGrid(Grid* g){
    grid = g;
}   
Scene::~Scene(){
    for (int i=0;i<nodes.size();i++){
        delete nodes[i];
    }
}