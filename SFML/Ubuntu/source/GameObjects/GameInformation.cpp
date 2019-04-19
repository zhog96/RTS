#include "GameInformation.h"

std::vector< std::vector<Tile> > GameInformation::playMap(32, std::vector<Tile>(32));
std::vector< Unit > GameInformation::units;
std::vector< Building > GameInformation::buildings;
std::queue< ICMessage > GameInformation::IntCoreQ;
std::queue< ICMessage > GameInformation::CoreIntQ; 