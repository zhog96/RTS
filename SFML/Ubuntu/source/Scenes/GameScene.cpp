#include "GameScene.h"
#include "source/UIObjects/Buttons/Button.hpp"
#include "source/UIObjects/Buttons/FunnyButton.h"
#include "SceneEvent.hpp"
#include "source/UIObjects/Buttons/Tile.h"

#include "source/UIObjects/DrawArray.h"
#include "source/UIObjects/Effects/FancyCubes.h"

#include <vector>

int GameScene::process() {
    int aliveCount = 0;
    for(int i = 0; i < uiobjects.size(); i++) {
        if (!uiobjects[i]->destructed()) {
            aliveCount++;
        } else {
            delete uiobjects[i];
        }
    }
    std::vector<UIObject *> vec(aliveCount, NULL);
    for(int i = 0, j = 0; i < uiobjects.size(); i++) {
        if (!uiobjects[i]->destructed()) {
            vec[j] = uiobjects[i];
            j++;
        }
    }
    uiobjects = vec;

    for(int i = 0; i < uiobjects.size(); i++) {
        uiobjects[i]->process();
    }


    //TODO Move to Mouse class
    bool click = UIinformation::clicked;
    sf::Vector2i mouse = sf::Vector2i(UIinformation::mPos);
    if(click) {
        std::vector<sf::Vector2i> vec = {DrawArray::addToLayer(1, sf::IntRect(-100, -100, 2, 2),
                                                               sf::IntRect(0, 0, 4, 4))};
        uiobjects.push_back(new FancyCubes(2, &vec, mouse, 10));
    }



    std::queue<SceneEvent> *events = UIinformation::events;

    while(!events->empty()) {
        SceneEvent event = events->front();
        events->pop();
        if (event.eCode == SceneEvent::Pressed && event.id == Events::Exit) {
            changeTo = UIinformation::Scenes::MenuScene;
        }
    }

    draw();

    return 0;
}

int GameScene::draw() {
    //???
}

GameScene::GameScene() : Scene() {
    for(int i = 0; i < 2; i++)
        textures.emplace_back(sf::Texture());
    textures[Textures::BackGroundT].loadFromFile("../textures/GameScene/GameSceneBG.png");
    textures[Textures::textureSheet].loadFromFile("../textures/GameScene/textureSheet.png");

    sf::Font font;
    font.loadFromFile("../fonts/arial.ttf");
    fonts.emplace_back(font);

    DrawArray::setLayerTexture(0, &textures[Textures::BackGroundT]);
    std::vector<sf::Vertex> vertex;
    vertex.emplace_back(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
    vertex.emplace_back(sf::Vertex(sf::Vector2f(1920.f, 0.f), sf::Vector2f(1920.f, 0.f)));
    vertex.emplace_back(sf::Vertex(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(1920.f, 1080.f)));
    vertex.emplace_back(sf::Vertex(sf::Vector2f(0.f, 1080.f), sf::Vector2f(0.f, 1080.f)));
    BGid = DrawArray::addToLayer(0, vertex);

    DrawArray::setLayerTexture(1, &textures[Textures::textureSheet]);
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 25; j++) {
            std::vector<sf::Vector2i> placeholder;
            std::vector<sf::Vector2i> vec2 = {DrawArray::addToLayer(1, sf::IntRect(i * 32, j * 32, 1 * 32, 1 * 32), sf::IntRect(2 * 32, 0 * 32, 1 * 32, 1 * 32))};
            uiobjects.push_back(new Tile(Events::Exit, &vec2, &placeholder));
        }
    }

    DrawArray::setLayerTexture(2, &textures[Textures::textureSheet]);
    std::vector<sf::Vertex> vertex2;
    vertex2.emplace_back(sf::Vertex(sf::Vector2f(0.f, 720.f), sf::Vector2f(0.f, 0.f)));
    vertex2.emplace_back(sf::Vertex(sf::Vector2f(1920.f, 720.f), sf::Vector2f(64.f, 0.f)));
    vertex2.emplace_back(sf::Vertex(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(64.f, 32.f)));
    vertex2.emplace_back(sf::Vertex(sf::Vector2f(0.f, 1080.f), sf::Vector2f(0.f, 32.f)));
    Panelid = DrawArray::addToLayer(2, vertex2);

    DrawArray::setLayerTexture(3, &textures[Textures::textureSheet]);
    sf::Text text = sf::Text("Exit", fonts[0], 120);
    text.setFillColor(sf::Color::White);
    std::vector<sf::Vector2i> vec2t = {DrawArray::addTextToLayer(3, text)};
    std::vector<sf::Vector2i> vec2 = {DrawArray::addToLayer(3, sf::IntRect(1850 - 16 * 32, 1030 - 8 * 32, 16 * 32, 8 * 32), sf::IntRect(0 * 32, 2 * 32, 2 * 32, 1 * 32))};
    uiobjects.push_back(new FunnyButton(Events::Exit, &vec2, &vec2t));


}

