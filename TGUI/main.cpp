#include <stdio.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <unistd.h>
#include <sys/types.h>

#include "src/Interface/Interface.hpp"

int main() {
    Interface::initInterface();
    Interface::run();
    printf("main is done\n");
    //interfaceDaemon();
    return EXIT_SUCCESS;
}