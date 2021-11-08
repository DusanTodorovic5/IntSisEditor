#ifndef GRID_CLASS
#define GRID_CLASS
#include "Field.hpp"
class Grid : public sf::Drawable{
    public:
        Grid(int x=0, int y=0);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void onClick();
        void _export();
        ~Grid();
        int getWidth() const;
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