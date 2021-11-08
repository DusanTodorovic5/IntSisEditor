#ifndef EXPORT_BUTTON_CLASS
#define EXPORT_BUTTON_CLASS

#include <fstream>
#include <iostream>
#include <string>

#include "Button.hpp"
#include "Grid.hpp"
class ExportButton : public Button{
    public:
        ExportButton(int x, int y) : Button(x,y,"Export",""){

        }
        void onClick(){
            std::ofstream file("map.txt");
            Grid* grid = Manager::getManager()->getGrid();
            file << grid->getAgentPos().second << "," << grid->getAgentPos().first << std::endl;
            file << grid->getGoalPos().second << "," << grid->getGoalPos().first << std::endl;
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    std::string t = grid->at(j,i)->getTexture();
                    if (t == "dune")
                        file << "d";
                    else if (t == "road")
                        file << "r";
                    else if (t == "grass" || t == "agent" || t == "x")
                        file << "g";
                    else if (t == "mud")
                        file << "m";
                    else if (t == "water")
                        file << "w";
                    else if (t == "stone")
                        file << "s";
                }
                file << std::endl;
            }
            file.close();
        }
};

#endif
