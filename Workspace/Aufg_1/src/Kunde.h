#pragma once

#include "Countable.h"

class Kunde : public Countable {
private:
    std::string name;
    //ZEIGER AUF KONTO
public:
    void print();
};