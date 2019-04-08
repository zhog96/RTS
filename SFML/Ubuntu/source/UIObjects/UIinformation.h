#pragma once

#include <queue>
#include <SFML/Graphics.hpp>
#include "source/Scenes/SceneEvent.hpp"

class UIinformation {
public:
    typedef enum {NoAction, Exit, MenuScene} Scenes;
    static bool bPressed[255];
    static sf::Vector2<double> mPos;
    static bool clicked;
    static std::queue<SceneEvent> *events;
    static sf::RenderWindow *window;
};

