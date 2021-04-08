#pragma once

#include <memory>

class Kunde;

#include "Countable.h"
#include "Konto.h"

class Kunde : public Countable {
private:
    std::string name;
    std::weak_ptr<Konto> konto;
public:
    void print();
    std::string tostring();

    Kunde(const std::string& name);
    Kunde(const Kunde& src);

    Kunde& operator= (const Kunde& src);

    void SetKonto(std::shared_ptr<Konto> konto);
};