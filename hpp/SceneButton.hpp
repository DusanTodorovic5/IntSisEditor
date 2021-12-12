#ifndef SCENE_BUTTON
#define SCENE_BUTTON
#include "Button.hpp"
#include "SceneManager.hpp"
class SceneButton : public Button{
    public:
        SceneButton(int x, int y, std::string textShow, std::string sceneName) : Button(x,y,textShow,""){
            this->sceneName = sceneName;
        }
        void clicked(){
            SceneManager::manager()->switchScene(sceneName);
        }
    private:
        std::string sceneName;

};

#endif