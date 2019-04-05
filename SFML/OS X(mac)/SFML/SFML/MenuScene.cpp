#include "MenuScene.hpp"
#include "Button.hpp"
#include "SceneEvent.hpp"

int MenuScene::process() {
    sf::Event event;
    sf::Mouse mouse;
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            changeTo = -1;
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                for(Button b : buttons) {
                    b.process(sf::Vector2<double>(mouse.getPosition()));
                }
            }
        }
    }
    while(!events.empty()) {
        printf("%d %d\n", events.front().id, events.front().eCode);
        events.pop();
    }
    return 0;
}

int MenuScene::draw() {
    for(Button b : buttons) {
        b.draw();
    }
}

MenuScene::MenuScene(sf::RenderWindow &window) : Scene(window) {
    textures.push_back(sf::Texture());
    textures[0].loadFromFile("textures/MainMenu/MainMenuBG.jpg");
    textures.push_back(sf::Texture());
    textures[1].loadFromFile("textures/MainMenu/buttonPressed.png");
    textures.push_back(sf::Texture());
    textures[2].loadFromFile("textures/MainMenu/buttonNotPressed.png");
    std::vector<sf::Texture *> vec({&textures[1], &textures[2]});
    sf::Transform tr;
    tr.translate(630, 400);
    buttons.push_back(Button(1, vec, tr, sf::Vector2<double>(100, 100), events, window));
}

