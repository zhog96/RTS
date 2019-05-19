#pragma once

#include <string>
#include <vector>
#include <map>
#include "../Element/Button.h"

enum ShemesEnum {None, Exit, Menu, Lobby, Play};

class Shemes {
public:
    static void loadTextures();
    static int shemeChange;
    static std::vector<Button> elements;
    static std::vector<Button> elementsPause;
    static std::map<std::string, sf::Texture> textures;
    static void cleanShemes();
};
