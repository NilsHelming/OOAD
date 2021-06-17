#pragma once

class Spielfigur;

#include <memory>

#include "Stein.h"
#include "Spieler.h"
#include "Feld.h"

class Spielfigur : public Stein {
private:
    std::weak_ptr<Spieler> spieler;
    std::weak_ptr<Feld> ausgangsposition;
public:
    Spielfigur(std::shared_ptr<Spieler> _spieler, std::shared_ptr<Feld> _ausgangsposition) :
        spieler(_spieler), ausgangsposition(_ausgangsposition) {}

    std::shared_ptr<Spieler> getSpieler(){return spieler.lock();}
    std::shared_ptr<Feld> getAusgangsposition(){return ausgangsposition.lock();}
    std::string getFarbe() const {return spieler.lock()->getFarbe();}
    bool istSpielfigur() const {return true;}
    bool istSperrstein() const {return false;}
};