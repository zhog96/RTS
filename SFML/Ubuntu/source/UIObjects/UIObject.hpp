#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "UIObject.hpp"
#include "source/Scenes/SceneEvent.hpp"

class UIObject {
protected:
    sf::IntRect size;
    std::vector<sf::Vector2i> drawIds;
    int id;
    bool focused;
public:
    UIObject(int id, std::vector<sf::Vector2i> &drawIds, sf::IntRect size);
    virtual int process() = 0;
};
