//
// Created by Lukas Lübberding on 16.06.21.
//

#ifndef MALEFIZ_SPIELER_H
#define MALEFIZ_SPIELER_H
#include "iostream"
using namespace std;

class Spieler {
private:
    string farbe;
    int alter;
    string name;

public:
    Spieler(string SpFarbe, int SpAlter, string SpName){
        farbe = SpFarbe;
        alter = SpAlter;
        name = SpName;
    }

    const string &getFarbe() const {
        return farbe;
    }

    int getAlter() const {
        return alter;
    }

    const string &getName() const {
        return name;
    }

};


#endif //MALEFIZ_SPIELER_H
