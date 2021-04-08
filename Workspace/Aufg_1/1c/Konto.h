#pragma once

#include <memory>

class Konto;

#include "Countable.h"
#include "Kunde.h"

class Konto : public Countable {
private:
    std::uint32_t ident;
    std::shared_ptr<Kunde> kunde = nullptr;

public:
    void print();
    std::string tostring();

    Konto(std::uint32_t account);
    Konto(const Konto& src);

    Konto& operator= (const Konto& src);

    void SetKunde(std::shared_ptr<Kunde> kunde);
};