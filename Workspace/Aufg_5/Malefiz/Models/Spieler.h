#pragma once

class Spieler;

#include <string>

#include "..\Interfaces\Model.h"

class Spieler : public Model {
private:
    std::string farbe;
    std::string name;
    int alter;

public:
    Spieler(std::string _n, int _a, std::string _f):name(_n), alter(_a), farbe(_f){}

    std::string getFarbe() const {return farbe;}
    int getAlter() const {return alter;}
    std::string getName() const {return name;}
};