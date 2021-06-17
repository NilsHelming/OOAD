#include <iostream>

#include "ZugStatusView.h"

ZugStatusView::ZugStatusView(std::shared_ptr<ZugStatus> _status) : status(_status) {
    this->status->addView(this);
    this->status->getWuerfel()->addView(this);
}

void ZugStatusView::modelChanged(){
    this->updateControllers(); //TODO: überprüfe, ob wir uns tatsächlich updaten müssen!
}

void ZugStatusView::show(){
    //Beispiel:
    //Spieler 1 ist an der Reihe! Würfel: [5].
    //<Prompt>

    if(this->status->getSpieler() == nullptr){
        std::cout << "Error: Spieler nicht definiert!" << std::endl;
        return;
    }

    int augenzahl = this->status->getWuerfel()->getAugenzahl();

    std::cout << "Spieler " << this->status->getSpieler()->getName() << " ist an der Reihe! ";
    if(augenzahl == 0)
        std::cout << "W\201rfel: [?]" << std::endl;
    else
        std::cout << "W\201rfel: [" << augenzahl << "]" << std::endl;
    std::cout << this->status->getPrompt() << std::endl;
}