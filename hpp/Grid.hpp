#ifndef GRID_CLASS
#define GRID_CLASS
#include "Field.hpp"
class Scene;
class Grid : public Node{
    public:
        Grid(int x=0, int y=0,Scene* s = nullptr);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool checkHovered(sf::Vector2i) const;
        void hovered();
        void hoveredExit();
        void clicked();
        ~Grid();
        int getWidth() const;
        int getHeight() const;
        Field* at(int i, int j);
        std::pair<int,int> getAgentPos() const;
        std::pair<int,int> getGoalPos() const;
    private:
        Field* grid[15][15];
        int x;
        int y;
        static const int FIELD_SIZE = 64;
        std::pair<int,int> agentPos;
        std::pair<int,int> goalPos;
};

#endif