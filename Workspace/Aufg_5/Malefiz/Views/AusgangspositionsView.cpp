#include "AusgangspositionsView.h"

AusgangspositionsView::AusgangspositionsView(std::shared_ptr<Spielfeld> _spielfeld)
    : spielfeld(_spielfeld) {
    this->spielfeld->addView(this);

    for(int i=0; i<4; ++i){//alle Spieler
        for(int n=0; n<5; ++n){//alle Ausgangspositionen
            auto feld = this->spielfeld->getAusgangsposition(i,n);
            if(feld != nullptr)
                feld->addView(this);
        }
    }

}


void AusgangspositionsView::modelChanged(){
    this->updateControllers(); //TODO: überprüfe, ob wir uns tatsächlich updaten müssen!
}


void AusgangspositionsView::show(){
    std::cout << "Belegung der Ausgangspositionen:" << std::endl;

    for(int i=0; i<4; ++i){ //für alle möglichen Spieler
        //Finde Namen des Spielers:
        auto figur = this->spielfeld->getSpielfigur(i,0); //die erste Spielfigur von Spieler i
        if(figur != nullptr){
            std::cout << " * Spieler: " << figur->getSpieler()->getName() << " [";
            for(int n=0; n<5; ++n){
                //falls sich irgendwann die Argumente von getAusgangsposition(i,n)
                //und getSpielfigur(i,n) nicht mehr einig sind, machen wirs so rum:
                figur = this->spielfeld->getSpielfigur(i,n); //n-te Spielfigur von Spieler i
                auto feld = figur->getAusgangsposition();
                std::cout << ((feld->getStein() == nullptr)? "-": "#");
            }
            std::cout << "]" << std::endl;
        }
    }
}