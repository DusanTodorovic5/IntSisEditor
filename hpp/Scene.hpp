#ifndef SCENE_CLASS
#define SCENE_CLASS

#include <vector>
#include <SFML/Graphics.hpp>
class Grid;
class Manager;
class Node;
class Scene : public sf::Drawable{
    public:
        Scene();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void add(Node*);
        void clicked();
        void mouseMoved(sf::Vector2i);
        Grid* getGrid();
        void setGrid(Grid*);
        ~Scene();
    private:
        std::vector<Node*> nodes;
        Node* currHovered;
        Grid* grid;
};
#endif