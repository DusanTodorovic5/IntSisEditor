#include "Grid.hpp"

Grid::Grid(int x, int y){
    this->x = x;
    this->y = y;
    for (int i=0;i<15;i++){
        for (int j=0;j<15;j++){
            grid[i][j] = new Field(x + i*FIELD_SIZE,y + j*FIELD_SIZE);
        }
    }
    agentPos.first = 0;
    agentPos.second = 0;

    grid[0][0]->setTexture("agent");

    goalPos.first = 14;
    goalPos.second = 14;

    grid[14][14]->setTexture("x");
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for (int i=0;i<15;i++){
        for (int j=0;j<15;j++){
            target.draw(*grid[i][j],states);
        }
    }
}

void Grid::onClick(){
    int x = sf::Mouse::getPosition(Manager::getManager()->getWindow()).x/64;
    int y = sf::Mouse::getPosition(Manager::getManager()->getWindow()).y/64;
    if (Manager::getManager()->getCurrent() == "x"){
        grid[goalPos.first][goalPos.second]->setTexture();
        goalPos.first = x;
        goalPos.second = y;
    }
    if (Manager::getManager()->getCurrent() == "agent"){
        grid[agentPos.first][agentPos.second]->setTexture();
        agentPos.first = x;
        agentPos.second = y;
    }
    grid[x][y]->onClick();
}

void Grid::_export(){

}

Grid::~Grid(){

}
int Grid::getWidth() const{
    return x+15*FIELD_SIZE;
}

Field* Grid::at(int i, int j){
    return grid[i][j];
}

std::pair<int,int> Grid::getAgentPos() const{
    return agentPos;
}
std::pair<int,int> Grid::getGoalPos() const{
    return goalPos;
}