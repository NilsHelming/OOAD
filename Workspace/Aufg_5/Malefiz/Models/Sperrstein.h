#pragma once

class Sperrstein;

#include <string>

#include "Stein.h"
#include "Feld.h"

class Sperrstein : public Stein {
    std::string getFarbe() const {return "ffffff";}
    bool istSpielfigur() const {return false;}
    bool istSperrstein() const {return true;}
};