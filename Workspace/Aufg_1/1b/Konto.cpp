#include <iostream>
#include <string>

#include "Konto.h"
#include "Kunde.h"

void Konto::print(){
    std::cout << this->tostring() << " --> " << this->kunde->tostring() << std::endl;
}

std::string Konto::tostring(){
    return "Konto (" + std::to_string(this->ident)+ ", Object " + std::to_string(this->identifier()) + ")";
}

Konto::Konto(std::uint32_t account, const std::string& name){
    this->ident = account;
    this->SetKunde(name);
}

Konto::Konto(const Konto& src){
    *this = src;
}

Konto& Konto::operator= (const Konto& src){
    if (this == &src)
        return *this;

    this->ident = src.ident;
    this->SetKunde(*src.kunde);

    return *this;
}

void Konto::SetKunde(const std::string& name){
    this->kunde = std::make_unique<Kunde>(name, this);
}
void Konto::SetKunde(const Kunde& kunde){
    this->kunde = std::make_unique<Kunde>(kunde);
    this->kunde->SetKonto(this);
}