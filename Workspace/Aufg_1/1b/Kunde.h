#pragma once

class Kunde;

#include "Countable.h"
#include "Konto.h"

class Kunde : public Countable {
private:
    std::string name;
    Konto* konto = nullptr;
public:
    void print();
    std::string tostring();

    Kunde(const std::string& name, Konto* konto);
    Kunde(const Kunde& src);

    Kunde& operator= (const Kunde& src);

    void SetKonto(Konto* konto);
};