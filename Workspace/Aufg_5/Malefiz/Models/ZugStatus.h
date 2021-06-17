#pragma once

class ZugStatus;

#include <string>
#include <memory>

#include "..\Interfaces\Model.h"
#include "Wuerfel.h"
#include "Spieler.h"

class ZugStatus : public Model {
private:
    std::shared_ptr<Wuerfel> wuerfel;
    std::shared_ptr<Spieler> spieler;
    std::string prompt;

public:
    ZugStatus() : wuerfel(std::make_shared<Wuerfel>()) {}

    std::shared_ptr<Wuerfel> getWuerfel(){return this->wuerfel;}
    std::shared_ptr<Spieler> getSpieler(){return this->spieler;}
    std::string getPrompt() {return this->prompt;}

    void setSpieler(std::shared_ptr<Spieler> sp){
        spieler = sp;
        wuerfel->reset(); //triggert auch nen updateViews() .... aber egal.

        this->updateViews();
    }
    void setPrompt(std::string str){
        prompt = str;
        this->updateViews();
    }
};