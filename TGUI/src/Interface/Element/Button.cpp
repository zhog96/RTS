#include <math.h>

#include "Button.h"
#include "../UIinformation.h"
#include "../Time.h"

void Button::update() {
    tgui::Widget * button = buttonP.get();
    if(button != nullptr) {
        button->setPosition(pos + sf::Vector2f(sin(phi), sin(phi)) * 10.f);
        phi += 0.00001 * Time::delta * omega;
        if(button->mouseOnWidget(sf::Vector2f(UIinformation::mPos)
            - button->getParent()->getAbsolutePosition())) {
            omega += 0.00001 * Time::delta;
            if(omega > maxOmega) omega = maxOmega;
        } else {
            omega -= 0.000001 * Time::delta;
            if(omega < 0.0f) omega = 0.0f;
        }
    }
}

Button::Button(tgui::Widget::Ptr buttonP) {
    this->buttonP = buttonP;
    this->pos = buttonP.get()->getPosition();
}
