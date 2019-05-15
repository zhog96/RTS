#include "MenuSheme.h"
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <math.h>

#include "Shemes.h"
#include "../UIinformation.h"
#include "../Time.h"
#include "../Element/Button.h"

void MenuSheme::play() {
    Shemes::shemeChange = ShemesEnum::Play;
}

void MenuSheme::exit() {
    Shemes::shemeChange = ShemesEnum::Exit;
}

void MenuSheme::update() {
    //printf("Interface update\n");
    for(int i = 0; i < Shemes::elements.size(); i++) {
        Shemes::elements[i].update();
    }
}

void MenuSheme::loadSheme() {
    printf("Sheme loading start\n");

    Shemes::shemeChange = ShemesEnum::None;

    tgui::Theme theme{"../themes/Black.txt"};
    tgui::Theme::setDefault(&theme);

    // Create the background image
    // The picture is of type tgui::Picture::Ptr which is actually just a typedef for std::shared_widget<Picture>
    // The picture will fit the entire window and will scale with it
    auto picture = tgui::Picture::create("../themes/images/MainMenuBG.jpg");
    picture->setSize({"100%", "100%"});
    UIinformation::gui->add(picture);

    //Header
    auto header = tgui::Label::create("Header");
    header->setTextSize(110);
    header->setAutoSize(true);
    header->setText("Strategy Game");
    header->setPosition({"10%", "5%"});
    UIinformation::gui->add(header, "Header");

    //Play button
    auto playButton = tgui::Button::create("Play");
    playButton->setTextSize(100);
    playButton->setSize({"50%", "25%"});
    playButton->setPosition({"25%", "30%"});
    UIinformation::gui->add(playButton, "Play");
    Shemes::elements.emplace_back(Button(playButton));
    playButton->setRenderer(theme.getRenderer("Button1"));

    //Play button callback
    playButton->connect("pressed", play);

    //Exit button
    auto exitButton = tgui::Button::create("Exit");
    exitButton->setTextSize(100);
    exitButton->setSize({"50%", "25%"});
    exitButton->setPosition({"25%", "65%"});
    UIinformation::gui->add(exitButton, "Exit");
    Shemes::elements.emplace_back(Button(exitButton));
    exitButton->setRenderer(theme.getRenderer("Button2"));

    //Exit button callback
    exitButton->connect("pressed", exit);

    printf("Sheme loading end\n");
}