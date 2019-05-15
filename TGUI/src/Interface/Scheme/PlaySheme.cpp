#include "PlaySheme.h"
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <math.h>

#include "Shemes.h"
#include "../UIinformation.h"
#include "../Time.h"
#include "../Element/Button.h"
#include "Map/Map.h"

bool PlaySheme::paused = false;

void PlaySheme::exit() {
    Map::clean();
    Shemes::shemeChange = ShemesEnum::Menu;
}

void PlaySheme::unpause() {
    paused = !paused;
    UIinformation::gui->get("PauseButton")->setEnabled(!paused);
    UIinformation::gui->get("Continue")->setVisible(paused);
    UIinformation::gui->get("Exit")->setVisible(paused);
    UIinformation::gui->get("Pause")->setVisible(paused);
}

void PlaySheme::update() {
    //printf("Interface update\n");
    if(!paused) {
        for (int i = 0; i < Shemes::elements.size(); i++) {
            Shemes::elements[i].update();
        }
    } else {
        for (int i = 0; i < Shemes::elementsPause.size(); i++) {
            Shemes::elementsPause[i].update();
        }
    }
    if(UIinformation::bClicked[sf::Keyboard::Space]) {
        unpause();
    }

    if(!paused) Map::update();
}

void PlaySheme::loadSheme() {
    printf("Sheme loading start\n");

    paused = false;
    Shemes::shemeChange = ShemesEnum::None;

    tgui::Theme theme{"../themes/Black.txt"};
    tgui::Theme::setDefault(&theme);

    // Create the background image
    // The picture is of type tgui::Picture::Ptr which is actually just a typedef for std::shared_widget<Picture>
    // The picture will fit the entire window and will scale with it
    auto picture = tgui::Picture::create("../themes/images/background.png");
    picture->setSize({"100%", "100%"});
    UIinformation::gui->add(picture);

    //MapCanvas
    auto canvas = tgui::Canvas::create("Canvas");
    canvas->setSize({"100%", "75%"});
    canvas->setPosition({"0%", "0%"});
    UIinformation::gui->add(canvas, "Canvas");

    //ControlPanel
    auto panel = tgui::Panel::create("Panel");
    panel->setSize({"100%", "25%"});
    panel->setPosition({"0%", "75%"});
    UIinformation::gui->add(panel, "Panel");

    //ControlPanelBackground
    auto panelBG = tgui::Picture::create("../themes/images/gamePanel.png");
    panelBG->setSize({"100%", "100%"});
    panelBG->setPosition({"0%, 0%"});
    panel->add(panelBG, "PanelBG");

    //PauseButton
    auto pauseButton = tgui::Button::create("");
    pauseButton->setSize({"10%", "50%"});
    pauseButton->setPosition({"80%", "25%"});
    panel->add(pauseButton, "PauseButton");
    pauseButton->setRenderer(theme.getRenderer("PauseButton"));
    pauseButton->connect("pressed", unpause);
    Shemes::elements.emplace_back(Button(pauseButton));

    //PausePanel
    auto pause = tgui::Panel::create("Pause");
    pause->setSize({"70%", "60%"});
    pause->setPosition({"15%", "20%"});
    pause->setVisible(PlaySheme::paused);
    pause->setRenderer(theme.getRenderer("PausePanel"));
    UIinformation::gui->add(pause, "Pause");
    Shemes::elementsPause.emplace_back(Button(pause));

    //Pause Background
    auto pauseBG = tgui::Picture::create("../themes/images/pause.png");
    pauseBG->setSize({"100%", "100%"});
    pauseBG->setPosition({"0%, 0%"});
    pause->add(pauseBG, "PauseBG");

    //Exit button
    auto exitButton = tgui::Button::create("Exit");
    exitButton->setTextSize(50);
    exitButton->setSize({"60%", "20%"});
    exitButton->setPosition({"20%", "60%"});
    exitButton->setVisible(PlaySheme::paused);
    pause->add(exitButton, "Exit");
    Shemes::elementsPause.emplace_back(Button(exitButton));
    exitButton->setRenderer(theme.getRenderer("Button2"));
    exitButton->connect("pressed", exit);

    //Continue button
    auto continueButton = tgui::Button::create("Continue");
    continueButton->setTextSize(50);
    continueButton->setSize({"60%", "20%"});
    continueButton->setPosition({"20%", "30%"});
    continueButton->setVisible(PlaySheme::paused);
    pause->add(continueButton, "Continue");
    Shemes::elementsPause.emplace_back(Button(continueButton));
    continueButton->setRenderer(theme.getRenderer("Button1"));
    continueButton->connect("pressed", unpause);

    //Map sources loading
    Map::loadMap(canvas.get());

    printf("Sheme loading end\n");
}