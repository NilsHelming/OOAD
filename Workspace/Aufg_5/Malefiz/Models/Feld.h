#pragma once

class Feld;

#include <string>
#include <iostream>

#include "..\Interfaces\Model.h"
#include "Stein.h"
#include "Spielfeld.h"

class Feld : public Model {
private:
    std::string farbe;
    bool ziel = false;
    int xPos;
    int yPos;

    std::weak_ptr<Stein> stein;
    Spielfeld* spielfeld;

public:
    Feld(Spielfeld* _sFeld, int _xPos, int _yPos, std::string _farbe, bool _istZiel = false):
        spielfeld(_sFeld), xPos(_xPos), yPos(_yPos), farbe(_farbe), ziel(_istZiel) {}

    bool istZiel() {return ziel;}
    std::string getFarbe() const {return farbe;}
    int getXPos() const {return xPos;}
    int getYPos() const {return yPos;}
    std::shared_ptr<Stein> getStein(){return stein.lock();}
    void setStein(std::shared_ptr<Stein> _stein){
        stein = _stein;
        this->updateViews();
    }
    bool istErreichbaresFeld(int schritte, std::shared_ptr<Feld> ziel, Feld* rueck);

    ~Feld(){}
};