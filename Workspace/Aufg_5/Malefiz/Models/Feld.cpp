#include "Feld.h"

#include <iostream>

bool Feld::istErreichbaresFeld(int schritte, std::shared_ptr<Feld> ziel, Feld* rueck){
    auto nachbarfelder = {
        this->spielfeld->getFeld(this->xPos-1, this->yPos),
        this->spielfeld->getFeld(this->xPos+1, this->yPos),
        this->spielfeld->getFeld(this->xPos, this->yPos-1),
        this->spielfeld->getFeld(this->xPos, this->yPos+1),
    };
    for(auto nachbar : nachbarfelder){
        if(nachbar == nullptr || rueck != nullptr && rueck->xPos == nachbar->xPos && rueck->yPos == nachbar->yPos){
            //skip - denn leere Felder und Rückschritte wollen wir nicht machen!
        }else if(schritte == 1){ //falls ich nurnoch einen Schritt habe, gucken, wir ob wir angekommen sind.
           if(ziel->xPos == nachbar->xPos && ziel->yPos == nachbar->yPos)
                return true;
        }else{
            //falls wir nicht über einen Sperrstein hinweg wollen:
            auto stein = nachbar->getStein();
            if(stein == nullptr || !stein->istSperrstein()){
                //prüfe ob wir mit den übrigen schritten vom Nachbar aus zum Ziel kommen!
                //(ohne wieder über unsere eigenen füße zu treten!)
                if(nachbar->istErreichbaresFeld(schritte-1, ziel, this))
                    return true;
            }
        }
    }
    return false;
}