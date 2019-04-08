#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "UIObject.hpp"
#include "source/Scenes/SceneEvent.hpp"

class UIObject {
protected:
    sf::Vector2<double> size;
    sf::Transform trans;
    std::vector<sf::Sprite> sprites;
    sf::Sprite *currSprite;
    int id;
    bool focused;
public:
    UIObject(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size);
    virtual int draw();
    virtual int process() = 0;
};
