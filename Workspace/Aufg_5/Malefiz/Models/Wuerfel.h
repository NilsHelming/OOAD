#pragma once

class Wuerfel;

#include <ctime>

#include "..\Interfaces\Model.h"

class Wuerfel : public Model {
private:
    int augenzahl = 0; //0 = Ungewürfelt
public:
    int getAugenzahl() const {return augenzahl;}
    void wuerfeln(){
        srand((unsigned int)time(NULL));
        this->augenzahl = rand() % 6 + 1;
        this->updateViews();
    }
    void reset(){
        this->augenzahl = 0;
        this->updateViews();
    }
};