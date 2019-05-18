#pragma once

#include <queue>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class UIinformation {
public:
    static bool bPressed[256];
    static bool bClicked[256];
    static bool mPressed[2];
    static bool mClicked[2];
    static float wheel;
    static sf::Vector2f mDeltaClick[2];
    static sf::Vector2f mLastClick[2];
    static sf::Vector2f mDeltaPressed[2];
    static sf::Vector2f mLastPressed[2];
    static sf::Vector2f mPos;
    static sf::RenderWindow *window;
    static tgui::Gui * gui;
};

