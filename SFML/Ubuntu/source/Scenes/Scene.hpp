#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

#include "SceneEvent.hpp"
#include "source/UIObjects/UIObject.hpp"
#include "source/UIObjects/Buttons/Button.hpp"

class Scene {
protected:
    std::queue<SceneEvent> events;
    std::vector<sf::Texture> textures;
    std::vector<sf::Font> fonts;
    std::vector<UIObject *> uiobjects;
    int changeTo;

public:
    Scene();
    int getChange();
    virtual int process() = 0;
    virtual int draw() = 0;
    ~Scene();
};

