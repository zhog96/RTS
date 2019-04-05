#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

#include "SceneEvent.hpp"
#include "source/UIObjects/UIObject.hpp"
#include "source/UIObjects/Button.hpp"

class Scene {
protected:
    std::queue<SceneEvent> events;
    sf::RenderWindow &window;
    std::vector<sf::Texture> textures;
    std::vector<sf::Font> fonts;
    std::vector<Button> buttons;
    int changeTo;
public:
    Scene(sf::RenderWindow &window);
    int getChange();
};

