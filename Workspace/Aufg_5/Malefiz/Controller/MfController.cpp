#include <iostream>

#include "MfController.h"

void clearConsole();
int translate(char);
int translate(int);
std::string translate(std::shared_ptr<Feld>);
std::shared_ptr<Feld> getFeld(std::shared_ptr<Spielfeld> sFeld,int x, int y);

void MfController::gameLoop(){

    int sIndex = -1; //Spieler Index -> wir gehen durch this->spieler der Reihe nach durch!
    //der erste Spieler ist hier also 0 (wir Inkrementieren am Anfang der Schleife!)

    auto zielStein = this->spielfeld->getZielFeld()->getStein();
    while(zielStein == nullptr || !zielStein->istSpielfigur()){
        sIndex = (sIndex+1)%this->spieler.size(); //zum nächsten Spieler wechseln!
        this->zStatus->setSpieler(this->spieler[sIndex]); //setzt den Würfel zurück!

        this->askWuerfel();

        auto vonFeld = this->askVonFeld();
        auto zuFeld = this->askZuFeld(vonFeld);

        auto zuStein = zuFeld->getStein();
        if(zuStein == nullptr){ //nichts besonderes an dem Feld! Einfach loslogen!
            this->spielfeld->switchSteine(vonFeld, zuFeld);
        }else if(zuStein->istSpielfigur()){ //wir sind auf einer (gegnerischen) Spielfigur gelandet!
            auto zuFigur = dynamic_cast<Spielfigur*>(zuStein.get());
            auto ausFeld = zuFigur->getAusgangsposition();
            //platziere geg. Figur auf seiner Ausgangspos.
            this->spielfeld->switchSteine(zuFeld, ausFeld);
            //platziere meine Figur auf die nun leere Zielposition.
            this->spielfeld->switchSteine(vonFeld, zuFeld);
        }else if(zuStein->istSperrstein()){ //wir möchten auf einen Sperrstein bewegen.
            auto sperrFeld = this->askSperrFeld(zuFeld, vonFeld);

            //bewege Sperrfeld aus dem Weg
            this->spielfeld->switchSteine(zuFeld, sperrFeld);
            //bewege meine Figur auf das ursprüngliche Sperrfeld
            if(sperrFeld.get() != vonFeld.get()) //(nur falls noch nötig!)
                this->spielfeld->switchSteine(vonFeld, zuFeld);
        }

        zielStein = this->spielfeld->getZielFeld()->getStein(); //while-Bedingung!
    }

    auto zielFigur = dynamic_cast<Spielfigur*>(zielStein.get());
    this->zStatus->setPrompt("Game Over! Spieler " + zielFigur->getSpieler()->getName() +" hat gewonnen!\nDrücke eine beliebige Taste, um das Programm zu beenden!");
    system("pause");
}

void MfController::askWuerfel(){
    while(this->zStatus->getWuerfel()->getAugenzahl() == 0){
        this->zStatus->setPrompt("Dr\201cke eine beliebige Taste, um zu w\201rfeln!");
        auto feld = this->spielfeld->getFeld(16,1);
        system("pause");
        this->zStatus->getWuerfel()->wuerfeln();
    }
}

std::shared_ptr<Feld> getFeld(std::shared_ptr<Spielfeld> sFeld,int x, int y){
    if(y == -1){ //Ausgangspositionen!
        std::shared_ptr<Feld> first(nullptr); //die erste passende Ausgangsposition.
        for(int i=0; i<4; ++i){
            for(int n=0; n<5; ++n){
                auto feld = sFeld->getAusgangsposition(i,n);
                if(feld != nullptr && feld->getXPos() == x && feld->getYPos() == y){
                    if(first == nullptr)
                        first = feld; //falls keine gefüllte Ausgangposition gefunden wird
                    auto stein = feld->getStein();
                    if(stein != nullptr && stein->istSpielfigur())
                        return feld; //eine gefüllte Ausgangsposition wurde gefunden!
                }
            }
        }
        return first;
    }else
        return sFeld->getFeld(x,y);
}

std::shared_ptr<Feld> MfController::askVonFeld(){
    this->zStatus->setPrompt("Bitte w\204hle eine Spielfigur zum bewegen aus: (Bsp: A0)");
    while(true){ //wir verlassen diese Schleife, wenn ein passendes Feld gefunden wurde.
        char col;
        int row;
        std::cin >> col >> row;

        std::shared_ptr<Feld> vonFeld = getFeld(this->spielfeld, translate(col), translate(row));

        if(vonFeld != nullptr){ //tatsächlich ein Feld ausgewähl! WUHUU!
            auto stein = vonFeld->getStein();
            if(stein != nullptr && stein->istSpielfigur()){ //auf dem Feld liegt eine Spielfigur!
                auto figur = dynamic_cast<Spielfigur*>(stein.get());
                auto spieler = figur->getSpieler();
                if(spieler.get() == this->zStatus->getSpieler().get()){
                    return vonFeld;
                }
            }
        }
        std::cout << "Fehlerhafte Auswahl! Versuchs noch einmal!" << std::endl;
    }
}
std::shared_ptr<Feld> MfController::askZuFeld(std::shared_ptr<Feld> vonFeld){
    this->zStatus->setPrompt("Bitte w\204hle ein Zielfeld zum bewegen aus: (von "+translate(vonFeld)+")");
    while(true){
        char col;
        int row;
        std::cin >> col >> row;

        std::shared_ptr<Feld> zuFeld = getFeld(this->spielfeld, translate(col), translate(row));

        if(zuFeld != nullptr){ //tatsächlich ein Feld ausgewähl! WUHUU!
            //ist dieses Feld erreichbar?
            if(vonFeld->istErreichbaresFeld(this->zStatus->getWuerfel()->getAugenzahl(), zuFeld, nullptr)){
                //kann ich meine Spielfigur auf diesem spezifischen Feld platzieren?
                //(ist es noch nicht von mir selbst belegt?)
                std::shared_ptr<Stein> zuStein = zuFeld->getStein();
                if(zuStein == nullptr || zuStein->istSperrstein()){
                    return zuFeld;
                }else{//zuStein muss zwangsläufig eine Spielfigur sein!
                    auto zuFigur = dynamic_cast<Spielfigur*>(zuStein.get());
                    auto zuSpieler = zuFigur->getSpieler();
                    if(zuSpieler.get() != this->zStatus->getSpieler().get())
                        return zuFeld;
                }
            }
        }
        std::cout << "Fehlerhafte Auswahl! Versuchs noch einmal!" << std::endl;
    }
}


std::shared_ptr<Feld> MfController::askSperrFeld(std::shared_ptr<Feld> vonFeld, std::shared_ptr<Feld> leerFeld){
    this->zStatus->setPrompt("Bitte bewege den Sperrstein ("+translate(vonFeld)+") auf eine neue Position!");
    while(true){
        char col;
        int row;
        std::cin >> col >> row;

        std::shared_ptr<Feld> zuFeld = getFeld(this->spielfeld, translate(col), translate(row));

        if(zuFeld != nullptr){ //tatsächlich ein Feld ausgewähl! WUHUU!
            //ist das Feld (gegeben einem leeren Spielfeld) verfügbar?
            if(translate(row) > 0 && !zuFeld->istZiel()){ //oberhalb der untersten Reihe / nicht Zielfeld!
                //ist das Feld leer / zukünftig leer?
                auto zuStein = zuFeld->getStein();
                if(zuStein == nullptr || zuFeld.get() == leerFeld.get())
                    return zuFeld;
            }
        }
        std::cout << "Fehlerhafte Auswahl! Versuchs noch einmal!" << std::endl;
    }
}

MfController::MfController(){

    std::cout << "Game Setup!" << std::endl;
    auto sp1 = std::make_shared<Spieler>("1", 15, "ff0000");
    auto sp2 = std::make_shared<Spieler>("2", 13, "00ff00");
    this->spieler.push_back(sp1);
    this->spieler.push_back(sp2);

    this->spielfeld = std::make_shared<Spielfeld>(this->spieler);
    this->zStatus = std::make_shared<ZugStatus>();

    this->sFeldView = std::make_shared<SpielfeldView>(this->spielfeld);
    this->sFeldView->addController(this);

    this->aPosView = std::make_shared<AusgangspositionsView>(this->spielfeld);
    this->aPosView->addController(this);

    this->zStatView = std::make_shared<ZugStatusView>(this->zStatus);
    this->zStatView->addController(this);
    std::cout << "Game Setup End!" << std::endl;

}

void MfController::viewChanged(){
    clearConsole();
    this->sFeldView->show();
    this->aPosView->show();
    this->zStatView->show();
}



int translate(char x){
    return x-'A';
}
int translate(int x){
    return x-1;
}

std::string translate(std::shared_ptr<Feld> feld){
    char x = 'A' + feld->getXPos();
    int y = 1 + feld->getYPos();

    std::string strX(1, x);
    return strX+std::to_string(y);
}

void clearConsole(){
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
    #elif defined (__APPLE__)
        system("clear");
    #endif
}