//
// Created by Lukas Lübberding on 16.06.21.
//

#ifndef MALEFIZ_SPIELFELD_H
#define MALEFIZ_SPIELFELD_H

#include "iostream"
using namespace std;

class Spielfeld {
private:
    int felder[5][10];
public:
    Spielfeld() {
        //unterste Reihe
        for (int i=0; i<8; i++){
            if (i<4){
                felder[0][i]=2;
            } else {
                felder[0][i]=3;
            }
        }
        //zweite und vierte Reihe
        for (int i=0; i<10; i++){
            felder[1][i] = 1;
            felder[3][i] = 1;
        }
        //dritte Reihe
        felder [2][0] = 1;
        felder [2][9] = 1;
       //fünfte Reihe Ziel
        felder [4][4] = 1;
    }

    int getFeld(int x, int y) {
        return felder[x][y];
    }

    void setzteSpielfigus(int Spieler, int x, int y){
        felder[x][y]=Spieler;
    }

};


#endif //MALEFIZ_SPIELFELD_H
