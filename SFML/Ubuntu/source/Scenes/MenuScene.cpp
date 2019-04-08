#include "MenuScene.hpp"
#include "source/UIObjects/Button.hpp"
#include "SceneEvent.hpp"

int MenuScene::process() {
    sf::Event event;
    sf::Mouse mouse;
    bool click = false;
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            changeTo = -1;
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                click = true;
            }
        }
    }
    for(int i = 0; i < buttons.size(); i++) {
        buttons[i].process(sf::Vector2<double>(mouse.getPosition(window)), click);
        draw();
    }

    while(!events.empty()) {
        SceneEvent event = events.front();
        events.pop();
        if (event.eCode == SceneEvent::Pressed && event.id == 1) {
            changeTo = -1;
        } else if (event.eCode == SceneEvent::Pressed && event.id == 0) {
            changeTo = 1;
        }
    }

    return 0;
}

int MenuScene::draw() {
    sf::Transform tr;
    tr.translate(450, 100);
    sf::Text t("Strategy Game", fonts[1], 150);
    t.setFillColor(sf::Color::Red);
    window.draw(sf::Sprite(textures[0]));
    window.draw(t, sf::RenderStates(tr));
    buttons[0].draw();
    buttons[1].draw();
}

MenuScene::MenuScene(sf::RenderWindow &window) : Scene(window) {
    textures.push_back(sf::Texture());
    textures[0].loadFromFile("../textures/MainMenu/MainMenuBG.jpg");
    textures.push_back(sf::Texture());
    textures[1].loadFromFile("../textures/MainMenu/buttonPressed.png");
    textures.push_back(sf::Texture());
    textures[2].loadFromFile("../textures/MainMenu/buttonNotPressed.png");
    fonts.push_back(sf::Font());
    fonts[0].loadFromFile("../fonts/font.ttf");
    fonts.push_back(sf::Font());
    fonts[1].loadFromFile("../fonts/arial.ttf");
    std::vector<sf::Texture *> vec({&textures[2], &textures[1]});
    sf::Transform tr, trT;
    tr.translate(630, 400);
    trT.translate(700, 450);
    buttons.push_back(Button(0, vec, tr, sf::Vector2<double>(600, 200), std::string("Play"), trT, &fonts[0], events, window));
    sf::Transform tr2, trT2;
    tr2.translate(630, 700);
    trT2.translate(700, 750);
    buttons.push_back(Button(1, vec, tr2, sf::Vector2<double>(600, 200), std::string("Exit"), trT2, &fonts[0], events, window));
}

