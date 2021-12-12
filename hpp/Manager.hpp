#ifndef MANAGER_CLASS
#define MANAGER_CLASS
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
class Grid;
class Manager : public sf::Drawable{
    public:
        sf::Texture& getTexture(std::string name) const;
        std::string getCurrent() const;
        void setCurrent(std::string texture_name);
        static Manager* getManager();
        sf::Window& getWindow();
        void setWindow(sf::Window* window);
        sf::Font& getFont();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void addGrid(Grid* grid);
        Grid* getGrid();
    private:
        static Manager* instance;
        Manager();
        std::map<std::string, sf::Texture*> textureMap;
        std::string currentPressed;
        sf::Window* window;
        sf::Font font;
        Grid* grid;
};

#endif