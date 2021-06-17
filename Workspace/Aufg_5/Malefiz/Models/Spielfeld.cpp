#include <algorithm>

#include "Spielfeld.h"

Spielfeld::Spielfeld(const std::vector<std::shared_ptr<Spieler>>& spieler){
    this->width = 17;
    this->height = 4;
    int center = 8; //für die Zielposition.
    std::shared_ptr<Feld> nullFeld(nullptr);
    //initialisiere den vektor für felder mit nullpointern!
    this->felder = std::vector<std::shared_ptr<Feld>>(this->width * this->height, nullptr);

//Erstelle Felder (des tatsächlichen Spielfeldes)
    //untere Reihe
    int y = 0;
    for(int x=0; x<this->width; ++x)
        this->felder[getIndex(x,y)] = std::make_shared<Feld>(this, x, y, "ff4000", false);

    //mittlere Reihe (setze [0,1] und [width-1,1])
    this->felder[getIndex(            0,1)] = std::make_shared<Feld>(this,             0, 1, "ff4000", false);
    this->felder[getIndex(this->width-1,1)] = std::make_shared<Feld>(this, this->width-1, 1, "ff4000", false);

    //obere Reihe
    y = 2;
    for(int x=0; x<this->width; ++x)
        this->felder[getIndex(x,y)] = std::make_shared<Feld>(this, x, y, "ff4000", false);

    //Zielfeld
    this->zielFeld = std::make_shared<Feld>(this, center, this->height-1, "ffff00", true);
    this->felder[getIndex(center, this->height-1)] = this->zielFeld;

//Erstelle Sperrsteine (im Abstand von 4, Zentriert unter dem Ziel.)
    auto sperrstein = std::make_shared<Sperrstein>();
    this->sperrsteine.push_back(sperrstein);
    this->getFeld(center, 2)->setStein(sperrstein);
    for(int offset = 4; offset+center < this->width; offset+=4){
        sperrstein = std::make_shared<Sperrstein>();
        this->sperrsteine.push_back(sperrstein);
        this->getFeld(center+offset,2)->setStein(sperrstein);

        sperrstein = std::make_shared<Sperrstein>();
        this->sperrsteine.push_back(sperrstein);
        this->getFeld(center-offset,2)->setStein(sperrstein);
    }
//Erstelle Ausgangspositionen (5 pro Spieler) (max 4 Spieler)
//Erstelle Spielfiguren (auf diesen Ausgangspositionen)
    int spielerAnzahl = spieler.size();
    spielerAnzahl = std::min(4, spielerAnzahl);
    for(int i = 0; i<spielerAnzahl ; ++i){ //spieler Index
        auto sp = spieler[i];
        auto farbe = sp->getFarbe();
        //Alle Ausgangspositionen eine Spielers sind an der gleichen Position im Spielfeld.
        int x = center + ((i/2)*4+2) * ((i%2 == 0)? -1:1);//should be one of: 2, 6, 10, 14
        int y = -1; //jede Ausgangsposition ist direkt unter der untersten Reihe.
        for(int n = 0; n<5; ++n){
            auto ausPos = std::make_shared<Feld>(this, x, y, farbe, false);
            this->ausgangspositionen.push_back(ausPos);
            auto spFigur = std::make_shared<Spielfigur>(sp, ausPos);
            this->spielfiguren.push_back(spFigur);
            ausPos->setStein(spFigur);
        }
    }
}

void Spielfeld::switchSteine(std::shared_ptr<Feld> A, std::shared_ptr<Feld> B){
    auto steinA = A->getStein();
    auto steinB = B->getStein();
    A->setStein(steinB);
    B->setStein(steinA);
}

