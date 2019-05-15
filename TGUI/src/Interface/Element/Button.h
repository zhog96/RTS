#pragma once

#ifndef TGUI_BUTTON_H
#define TGUI_BUTTON_H

#include <string>
#include <TGUI/TGUI.hpp>

class Button {
private:
    float phi = 0.0f;
    float maxOmega = 1.0f;
    float omega = 0.0f;
    sf::Vector2f pos;
    tgui::Widget::Ptr buttonP;
public:
    void update();
    Button(tgui::Widget::Ptr buttonP);
};


#endif //TGUI_BUTTON_H
