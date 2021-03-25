#pragma once

#include "Countable.h"

class Konto : public Countable {
private:
    std::uint32_t ident;
    //ZEIGER AUF KUNDE
public:
    void print();
};