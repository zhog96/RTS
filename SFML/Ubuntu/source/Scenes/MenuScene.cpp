#include "MenuScene.hpp"
#include "source/UIObjects/Buttons/Button.hpp"
#include "source/UIObjects/Buttons/FunnyButton.h"
#include "SceneEvent.hpp"

#include "source/Tools/DrawArray.h"

#include <vector>

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

int MenuScene::draw() {

    DrawArray::draw();
}

MenuScene::MenuScene() : Scene() {
    for(int i = 0; i < 2; i++)
        textures.emplace_back(sf::Texture());
    textures[Textures::BackGroundT].loadFromFile("../textures/MainMenu/MainMenuBG.jpg");
    textures[Textures::ButtonsT].loadFromFile("../textures/MainMenu/buttons.png");

    DrawArray::setLayerTexture(0, &textures[Textures::BackGroundT]);
    std::vector<sf::Vertex> vertex;
    vertex.emplace_back(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
    vertex.emplace_back(sf::Vertex(sf::Vector2f(1920.f, 0.f), sf::Vector2f(1920.f, 0.f)));
    vertex.emplace_back(sf::Vertex(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(1920.f, 1080.f)));
    vertex.emplace_back(sf::Vertex(sf::Vector2f(0.f, 1080.f), sf::Vector2f(0.f, 1080.f)));
    BGid = DrawArray::addToLayer(sf::Vector2i(0, 0), vertex);

    DrawArray::setLayerTexture(1, &textures[Textures::ButtonsT]);
    std::vector<sf::Vector2i> vec = {DrawArray::addToLayer(sf::Vector2i(1, 0), sf::IntRect(22, 8, 16, 8), sf::IntRect(0, 0, 2, 1))};
    uiobjects.push_back(new FunnyButton(Events::Play, vec, sf::IntRect(0, 0, 64 * 8, 32 * 8)));

    std::vector<sf::Vector2i> vec2 = {DrawArray::addToLayer(sf::Vector2i(1, 0), sf::IntRect(22, 20, 16, 8), sf::IntRect(0, 1, 2, 1))};
    uiobjects.push_back(new FunnyButton(Events::Exit, vec2, sf::IntRect(0, 0, 64 * 8, 32 * 8)));
}

