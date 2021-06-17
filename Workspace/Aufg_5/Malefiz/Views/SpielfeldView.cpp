#include <iostream>

#include "SpielfeldView.h"

SpielfeldView::SpielfeldView(std::shared_ptr<Spielfeld> _spielfeld) :
    spielfeld(_spielfeld) {
    this->spielfeld->addView(this);

    for(int x=0; x<this->spielfeld->getWidth(); ++x){
        for(int y=0; y<this->spielfeld->getHeight(); ++y){
            auto feld = this->spielfeld->getFeld(x,y);
            if(feld != nullptr)
                feld->addView(this);
        }
    }
}

void SpielfeldView::modelChanged(){
    this->updateControllers(); //TODO: überprüfe, ob wir uns tatsächlich updaten müssen!
}

void SpielfeldView::show(){
    std::cout << "    ";
    for(int x = 0; x<this->spielfeld->getWidth(); ++x){
        char column = 'A' + x;
        std::cout << column << " "; //column letter
    }
    std::cout << std::endl;

    std::cout << "  +-";
    for(int x = 0; x<this->spielfeld->getWidth(); ++x){
        std::cout << "--";
    }
    std::cout << "+ " << std::endl;

    for(int y=this->spielfeld->getHeight()-1; y>=0; --y){
        std::cout << y+1 << " | "; //row number
        for(int x=0; x<this->spielfeld->getWidth(); ++x){
            auto feld = this->spielfeld->getFeld(x,y);
            if(feld == nullptr)
                std::cout << "  ";
            else{
                auto stein = feld->getStein();
                if(stein == nullptr)
                    std::cout << ((feld->istZiel())?"Z ":"O "); //
                else if(stein->istSperrstein())
                    std::cout << "X ";
                else if(stein->istSpielfigur()){
                    auto spielfigur = dynamic_cast<Spielfigur*>(stein.get());
                    auto spieler = spielfigur->getSpieler();
                    std::cout << spieler->getName().at(0) << " ";
                }else
                    std::cout << "? "; //shouldn't happen!
            }
        }
        std::cout << "|" << std::endl;
    }

    std::vector<char> ausgChars(this->spielfeld->getWidth(), ' ');
    for(int i=0; i<4; ++i){
        for(int n=0; n<5; ++n){
            auto feld = this->spielfeld->getAusgangsposition(i,n);
            if(feld != nullptr){
                char& curr = ausgChars[feld->getXPos()];
                if(curr == ' ' || curr == '^'){
                    auto sFigur = dynamic_cast<Spielfigur*>(feld->getStein().get());
                    curr = (sFigur == nullptr)? '^' : sFigur->getSpieler()->getName().at(0);
                }
                // std::cout << "(" << curr << ")" << std::endl;
            }
        }
    }

    std::cout << "0 | "; //Ausgangspositionsreihe!
    for(char c : ausgChars)
        std::cout << c << " ";
    std::cout << "|" << std::endl;

    std::cout << "  +-";
    for(int x = 0; x<this->spielfeld->getWidth(); ++x){
        std::cout << "--";
    }
    std::cout << "+ " << std::endl;
}