#pragma once

class Spielfeld;

#include <memory>
#include <vector>

#include "..\Interfaces/Model.h"
#include "Spieler.h"
#include "Feld.h"
#include "Spielfigur.h"
#include "Sperrstein.h"

class Spielfeld : public Model {
private:
    int width;
    int height;
    std::shared_ptr<Feld> zielFeld;
    std::vector<std::shared_ptr<Feld>> felder;
    std::vector<std::shared_ptr<Feld>> ausgangspositionen;
    std::vector<std::shared_ptr<Spielfigur>> spielfiguren;
    std::vector<std::shared_ptr<Sperrstein>> sperrsteine;

public:
    Spielfeld(const std::vector<std::shared_ptr<Spieler>> &_spieler);
    std::shared_ptr<Feld> getFeld(int x, int y){
        if(x<0 || x>=width || y<0 || y>=height)
            return nullptr;
        int i = y*width+x;
        return felder[i];
    }
    std::shared_ptr<Feld> getAusgangsposition(int i, int n){
        if(i<0 || n<0 || i*5+n >= ausgangspositionen.size())
            return nullptr;
        return ausgangspositionen[i*5+n];
    }
    std::shared_ptr<Spielfigur> getSpielfigur(int i, int n){
        if(i<0 || n<0 || i*5+n >= spielfiguren.size())
            return nullptr;
        return spielfiguren[i*5+n];
    }
    std::shared_ptr<Sperrstein> getSperrstein(int i){
        if(i<0 || i >= sperrsteine.size())
            return nullptr;
        return sperrsteine[i];
    }
    std::shared_ptr<Feld> getZielFeld(){
        return zielFeld;
    }
    void switchSteine(std::shared_ptr<Feld> A, std::shared_ptr<Feld> B);
    int getWidth() const {return width;}
    int getHeight() const {return height;}
};