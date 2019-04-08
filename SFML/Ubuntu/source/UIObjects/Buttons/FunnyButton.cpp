#include "FunnyButton.h"
#include <math.h>

int FunnyButton::motion() {
    //printf("Time::delta : %d\n", Time::delta);
    if(focused) {
        double dt = Time::delta / 1000.0;
        trans = startTr;
        trans.translate(3 * sin(phi), 3 * sin(phi));
        textTrans = startTextTr;
        textTrans.translate(1.5 * sin(phi), 1.5 * sin(phi));
        phi += 0.01 * dt;
        if(phi > 1000.0 || phi < -1000.0) phi = asin(sin(phi));
    } else {
        trans = startTr;
        textTrans = startTextTr;
    }
}

FunnyButton::FunnyButton(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size, std::string text, sf::Transform textTrans, sf::Font *font) : Button(id, textures, trans, size, text, textTrans, font) {
    printf("Created funnybutton, id : %d\n", id);
    currSprite = &sprites[0];
    phi = 0.0;
    startTr = trans;
    startTextTr = textTrans;
}
