#pragma once

#include <vector>
#include <TGUI/TGUI.hpp>

#include "../DrawArray.h"
#include "../../../Time.h"

class Confetti {
private:
    static std::vector<sf::Vector2i> confetti;
    static std::vector<sf::Vector2f> confettiS;
    static int layer;
    static sf::Vector2f screenSize;
    static long long lastImp;
    static long long freq;
    static bool started;
    static sf::Texture * text;
public:
    static void update();
    static void start(int layer, sf::Vector2f screenSize);
    static void clear();
};
