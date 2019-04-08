#include "MenuScene.hpp"
#include "source/UIObjects/Buttons/Button.hpp"
#include "source/UIObjects/Buttons/FunnyButton.h"
#include "SceneEvent.hpp"

int MenuScene::process() {
    for(int i = 0; i < uiobjects.size(); i++) {
        uiobjects[i]->process();
    }

    std::queue<SceneEvent> *events = UIinformation::events;

    while(!events->empty()) {
        SceneEvent event = events->front();
        events->pop();
        if (event.eCode == SceneEvent::Pressed && event.id == Events::Exit) {
            changeTo = UIinformation::Scenes::Exit;
        } else if (event.eCode == SceneEvent::Pressed && event.id == Events::Play) {
            //changeTo = ???;
        }
    }

    draw();

    return 0;
}

sf::VertexArray quad(sf::Quads, 400);

int MenuScene::draw() {
    sf::Transform tr;
    tr.translate(450, 100);
    sf::Text t("Strategy Game", fonts[Fonts::Arial], 150);
    t.setFillColor(sf::Color::Red);
    UIinformation::window->draw(sprites[Sprites::BackGroundS]);
    UIinformation::window->draw(t, sf::RenderStates(tr));
    for(int i = 0; i < uiobjects.size(); i++) {
        uiobjects[i]->draw();
    }
}

MenuScene::MenuScene() : Scene(){
    for(int i = 0; i < 3; i++)
        textures.emplace_back(sf::Texture());
    textures[Textures::BackGroundT].loadFromFile("../textures/MainMenu/MainMenuBG.jpg");
    textures[Textures::ButtonFocusedT].loadFromFile("../textures/MainMenu/buttonPressed.png");
    textures[Textures::ButtonReleasedT].loadFromFile("../textures/MainMenu/buttonNotPressed.png");

    sprites.emplace_back(sf::Sprite());
    sprites[Sprites::BackGroundS].setTexture(textures[Textures::BackGroundT]);

    for(int i = 0; i < 3; i++)
        fonts.emplace_back(sf::Font());

    fonts[Fonts::Font].loadFromFile("../fonts/font.ttf");
    fonts[Fonts::Arial].loadFromFile("../fonts/arial.ttf");
    std::vector<sf::Texture *> vec({&textures[Textures::ButtonReleasedT], &textures[Textures::ButtonFocusedT]});

    sf::Transform tr, trT;
    tr.translate(630, 400);
    trT.translate(700, 450);
    uiobjects.push_back(new FunnyButton(Events::Play, vec, tr, sf::Vector2<double>(600, 200), std::string("Play"), trT, &fonts[0]));
    sf::Transform tr2, trT2;
    tr2.translate(630, 700);
    trT2.translate(700, 750);
    uiobjects.push_back(new FunnyButton(Events::Exit, vec, tr2, sf::Vector2<double>(600, 200), std::string("Exit"), trT2, &fonts[0]));

}

