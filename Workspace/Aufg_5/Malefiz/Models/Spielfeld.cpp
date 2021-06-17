#include <algorithm>

#include "Spielfeld.h"

Spielfeld::Spielfeld(const std::vector<std::shared_ptr<Spieler>>& spieler){
    this->width = 17;
    this->height = 4;
    int center = 8; //für die Zielposition.
    std::shared_ptr<Feld> nullFeld(nullptr);

//Erstelle Felder (des tatsächlichen Spielfeldes)
    //untere Reihe
    for (int i = 0; i<this->width; ++i)
        this->felder.push_back(std::make_shared<Feld>(this, i, 0, "ff4000", false));

    //mittlere Reihe
    this->felder.push_back(std::make_shared<Feld>(this, 0, 1, "ff4000", false));
    for (int i = 1; i<this->width-1; ++i)
        this->felder.push_back(nullFeld);
    this->felder.push_back(std::make_shared<Feld>(this, this->width-1, 1, "ff4000", false));

    //obere Reihe
    for (int i = 0; i<this->width; ++i)
        this->felder.push_back(std::make_shared<Feld>(this, i, 2, "ff4000", false));

    //Zielfeld (und dessen Reihe)
    for (int i = 0; i<this->width; ++i)
        this->felder.push_back(nullFeld);
    int Zielpos = (this->height-1)*this->width + center;
    felder[Zielpos] = std::make_shared<Feld>(this, center, 3, "ffff00", true);
    this->zielFeld = felder[Zielpos];

//Erstelle Sperrsteine (im Abstand von 4, Zentriert unter dem Ziel.)
    auto sperrstein = std::make_shared<Sperrstein>();
    this->sperrsteine.push_back(sperrstein);
    int len = this->felder.size();
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

