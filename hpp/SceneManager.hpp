#ifndef SCENE_MANAGER
#define SCENE_MANAGER

#include <iostream>
#include <SFML/Graphics.hpp>
class Scene;
class SceneManager : public sf::Drawable{
    public:
        static SceneManager* manager();
        void switchScene(std::string);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void addScene(std::string, Scene*);
        void clicked();
        void mouseMoved(sf::Vector2i vector);
        ~SceneManager();
    private:
        SceneManager();
        static SceneManager* instance;
        std::map<std::string, Scene*> scenes;
        std::string currScene;
};


#endif