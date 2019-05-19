#pragma once

class LobbySheme {
private:
    static void playSmall();
    static void playMedium();
    static void playBig();
    static void playManual();
    static void exit();
public:
    static void update();
    static void loadSheme();
};


