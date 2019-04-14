#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "UIObject.hpp"
#include "source/Scenes/SceneEvent.hpp"

class UIObject {
protected:
    std::vector<sf::Vector2i> drawIds;
    std::vector<sf::Vector2i> textIds;
    int id;
    bool focused;
    bool forDelete;
public:
    UIObject(int id, std::vector<sf::Vector2i> *drawIds, std::vector<sf::Vector2i> *textIds = NULL);
    virtual int process() = 0;
    int destructed();
};
