#include "Grid.hpp"
#include "Button.hpp"
#include "Panel.hpp"
#include "Panel2.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "TextHolder.hpp"
#include "SceneButton.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 960), "Inteligentni sistemi editor");


    Scene* startScene = new Scene();

    TextHolder* text = new TextHolder(600,300, "Izaberite Editor");
    TextHolder* text2 = new TextHolder(600,860, "Pretisnite ESC da se vratite na ovaj ekran",50);
    startScene->add(text);
    startScene->add(text2);
    SceneButton* b_dz1 = new SceneButton(480,500,"Prvi domaci","dz1");
    SceneButton* b_dz2 = new SceneButton(480,700,"Drugi domaci","dz2");
    startScene->add(b_dz1);
    startScene->add(b_dz2);
    Scene* scene = new Scene();

    Grid* grid = new Grid(0,0,scene);
    Panel* panel = new Panel(960,0,scene);
    Manager::getManager()->setWindow(&window);
    

    Scene* scene2 = new Scene();
    Grid* grid2 = new Grid(0,0,scene2);
    Panel2* panel2 = new Panel2(960,0,scene2);

    window.setFramerateLimit(60);
    SceneManager::manager()->addScene("start",startScene);
    SceneManager::manager()->addScene("dz1",scene);
    SceneManager::manager()->addScene("dz2",scene2);
    SceneManager::manager()->switchScene("start");

    bool f = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).y < window.getSize().y){
                SceneManager::manager()->clicked();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                SceneManager::manager()->switchScene("start");
            }
        }
        if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).y < window.getSize().y){
            SceneManager::manager()->mouseMoved(sf::Mouse::getPosition(window));
        }
        window.clear();
        window.draw(*(SceneManager::manager()));
        window.display();
    }
    delete SceneManager::manager();
    return 0;
}
