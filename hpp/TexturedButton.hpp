#ifndef TEXTURE_BUTTON
#define TEXTURE_BUTTON
#include "Button.hpp"
class TextureButton : public Button{
    public:
        TextureButton(int x, int y, std::string text, std::string texture_name) : Button(x,y,text,texture_name){
            this->texture_name = texture_name;
        }
        void clicked(){
            Manager::getManager()->setCurrent(texture_name);
        }
    private:
        std::string texture_name;
};

#endif