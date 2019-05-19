#include "LobbySheme.h"

#include "Shemes.h"
#include "../UIinformation.h"
#include "../Time.h"
#include "../Element/Button.h"
#include "Map/MapObjects/MapInfo.h"

void LobbySheme::playSmall() {
    MapInfo::nBombs = 10;
    MapInfo::mapSize = {10, 10};
    MapInfo::mapState = UIinformation::gui->get("CheckBox")->cast<tgui::CheckBox>()->isChecked() ? MapInfo::playStates::wave : MapInfo::playStates::playing;
    Shemes::shemeChange = ShemesEnum::Play;
}

void LobbySheme::playMedium() {
    MapInfo::nBombs = 50;
    MapInfo::mapSize = {20, 20};
    MapInfo::mapState = UIinformation::gui->get("CheckBox")->cast<tgui::CheckBox>()->isChecked() ? MapInfo::playStates::wave : MapInfo::playStates::playing;
    Shemes::shemeChange = ShemesEnum::Play;
}

void LobbySheme::playBig() {
    MapInfo::nBombs = 133;
    MapInfo::mapSize = {40, 25};
    MapInfo::mapState = UIinformation::gui->get("CheckBox")->cast<tgui::CheckBox>()->isChecked() ? MapInfo::playStates::wave : MapInfo::playStates::playing;
    Shemes::shemeChange = ShemesEnum::Play;
}

void LobbySheme::playManual() {
    std::string placeholder[3] = {UIinformation::gui->get("BombBox")->cast<tgui::EditBox>()->getText(),
                                  UIinformation::gui->get("YBox")->cast<tgui::EditBox>()->getText(),
                                  UIinformation::gui->get("XBox")->cast<tgui::EditBox>()->getText()};
    try {
        MapInfo::nBombs = std::stoi(placeholder[0]);
        MapInfo::mapSize = {std::stoi(placeholder[2]), std::stoi(placeholder[1])};
        MapInfo::mapState = UIinformation::gui->get("CheckBox")->cast<tgui::CheckBox>()->isChecked() ? MapInfo::playStates::wave : MapInfo::playStates::playing;
    }
    catch (std::invalid_argument &)
    {
        MapInfo::nBombs = 1;
        MapInfo::mapSize = {1, 2};
        MapInfo::mapState = MapInfo::playStates::playing;
    }
    Shemes::shemeChange = ShemesEnum::Play;
}

void LobbySheme::exit() {
    Shemes::shemeChange = ShemesEnum::Menu;
}

void LobbySheme::update() {
    for(int i = 0; i < Shemes::elements.size(); i++) {
        Shemes::elements[i].update();
    }
}

void LobbySheme::loadSheme() {
    printf("Sheme loading start\n");

    Shemes::shemeChange = ShemesEnum::None;

    tgui::Theme theme{"../themes/LobbyTheme.txt"};
    tgui::Theme::setDefault(&theme);

    // Create the background image
    // The picture is of type tgui::Picture::Ptr which is actually just a typedef for std::shared_widget<Picture>
    // The picture will fit the entire window and will scale with it
    auto picture = tgui::Picture::create("../themes/images/LobbyBG.png");
    picture->setSize({"100%", "100%"});
    UIinformation::gui->add(picture);

    //Header
    auto header = tgui::Label::create("Header");
    header->setTextSize(40);
    header->setAutoSize(true);
    header->setText("Choose map size OR Create your own");
    header->setPosition({"14%", "1%"});
    UIinformation::gui->add(header, "Header");

    //Small button
    auto smallButton = tgui::Button::create("Small");
    smallButton->setTextSize(25);
    smallButton->setSize({"10%", "10%"});
    smallButton->setPosition({"10.5%", "16%"});
    UIinformation::gui->add(smallButton, "Small");
    Shemes::elements.emplace_back(Button(smallButton));
    smallButton->setRenderer(theme.getRenderer("Small"));
    //Small button callback
    smallButton->connect("pressed", playSmall);

    //Medium button
    auto mediumButton = tgui::Button::create("Medium");
    mediumButton->setTextSize(25);
    mediumButton->setSize({"10%", "10%"});
    mediumButton->setPosition({"10.5%", "35.5%"});
    UIinformation::gui->add(mediumButton, "Medium");
    Shemes::elements.emplace_back(Button(mediumButton));
    mediumButton->setRenderer(theme.getRenderer("Medium"));
    //Medium button callback
    mediumButton->connect("pressed", playMedium);

    //Big button
    auto bigButton = tgui::Button::create("Big");
    bigButton->setTextSize(25);
    bigButton->setSize({"10%", "10%"});
    bigButton->setPosition({"10.5%", "54.9%"});
    UIinformation::gui->add(bigButton, "Big");
    Shemes::elements.emplace_back(Button(bigButton));
    bigButton->setRenderer(theme.getRenderer("Big"));
    //Big button callback
    bigButton->connect("pressed", playBig);

    //Manual button
    auto manualButton = tgui::Button::create("Own");
    manualButton->setTextSize(25);
    manualButton->setSize({"10%", "10%"});
    manualButton->setPosition({"10.5%", "74.3%"});
    UIinformation::gui->add(manualButton, "Manual");
    Shemes::elements.emplace_back(Button(manualButton));
    manualButton->setRenderer(theme.getRenderer("Manual"));
    //Manual button callback
    manualButton->connect("pressed", playManual);

    //Exit button
    auto exitButton = tgui::Button::create("");
    exitButton->setTextSize(33);
    exitButton->setSize({"7%", "10%"});
    exitButton->setPosition({"92%", "87%"});
    UIinformation::gui->add(exitButton, "Exit");
    Shemes::elements.emplace_back(Button(exitButton));
    exitButton->setRenderer(theme.getRenderer("PauseButton"));
    //Exit button callback
    exitButton->connect("pressed", exit);

    //Type boxes
    auto bombBox = tgui::EditBox::create();
    bombBox->setPosition({"56.5%", "15%"});
    bombBox->setSize({"18%","20%"});
    bombBox->setMaximumCharacters(4);
    bombBox->setTextSize(64);
    UIinformation::gui->add(bombBox, "BombBox");

    auto yBox = tgui::EditBox::create();
    yBox->setPosition({"56.5%", "41%"});
    yBox->setSize({"18%","20%"});
    yBox->setMaximumCharacters(3);
    yBox->setTextSize(81);
    UIinformation::gui->add(yBox, "YBox");

    auto xBox = tgui::EditBox::create();
    xBox->setPosition({"56.5%", "67%"});
    xBox->setSize({"18%","20%"});
    xBox->setMaximumCharacters(3);
    xBox->setTextSize(81);
    UIinformation::gui->add(xBox, "XBox");

    //Check box
    auto checkBox = tgui::CheckBox::create("");
    checkBox->setPosition({"97%", "2%"});
    checkBox->setSize({"2%", "3%"});
    UIinformation::gui->add(checkBox, "CheckBox");

    printf("Sheme loading end\n");
}