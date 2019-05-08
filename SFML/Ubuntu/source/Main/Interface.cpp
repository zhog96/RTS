#include "Interface.hpp"

#include <stdio.h>
#include <string>
#include <SFML/System.hpp>

#include "source/UIObjects/UIinformation.h"
#include "source/Tools/Time.h"
#include "source/UIObjects/DrawArray.h"
#include "source/GameObjects/GameInformation.h"
#include "source/Scenes/GameScene.h"

sf::RenderWindow Interface::window;
Scene * Interface::scene = NULL;

int Interface::initInterface() {
    window.create(sf::VideoMode(1920, 1080), "SFML window");
    UIinformation::window = &window;
    scene = new MenuScene();
    //Check GPU, keyboard, ...
}

int Interface::run() {
    window.setFramerateLimit(60);

    Time::update();
    Time::update();
    while(window.isOpen()) {

        sf::Event event;
        sf::Mouse mouse;

        UIinformation::clicked = false;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    UIinformation::clicked = true;
                }
            }
        }

        UIinformation::mPos = sf::Vector2<double>(mouse.getPosition(window));

        Time::update();
        scene->process();

        /*if(!q_Core_in.isEmpty()) {
            int k = q_Core_in.top();
            q_Core_in.pop();
            printf("%d\n", k);
        }*/

        window.clear();
        DrawArray::draw();
        scene->draw();//???

        window.display();

        switch (scene->getChange()) {
            case UIinformation::Scenes::MenuScene:
                delete scene;
                DrawArray::clear();
                scene = new MenuScene();
                break;
            case UIinformation::Scenes::GameScene:
                delete scene;
                DrawArray::clear();
                scene = new GameScene();
                break;
            case UIinformation::Scenes::Exit:
                DrawArray::clear();
                GameInformation::IntCoreQ.push(new ICMessage(ICMessage::typesI::STOP, NULL));
                window.close();
                break;
        }
    }
}
