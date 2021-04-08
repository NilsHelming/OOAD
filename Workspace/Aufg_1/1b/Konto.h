#pragma once

#include <memory>

class Konto;

#include "Countable.h"
#include "Kunde.h"

class Konto : public Countable {
private:
    std::uint32_t ident;
    std::unique_ptr<Kunde> kunde = nullptr;

public:
    void print();
    std::string tostring();

    Konto(std::uint32_t account, const std::string& name);
    Konto(const Konto& src);

    Konto& operator= (const Konto& src);

    void SetKunde(const std::string& name);
    void SetKunde(const Kunde& kunde);
};