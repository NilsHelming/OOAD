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

Konto::Konto(std::uint32_t account){
    this->ident = account;
}

Konto::Konto(const Konto& src){
    *this = src;
}

Konto& Konto::operator= (const Konto& src){
    if (this == &src)
        return *this;

    this->ident = src.ident;
    this->SetKunde(std::make_shared<Kunde>(*(src.kunde)));
    // this->SetKunde(*src.kunde);
    //XXXXX

    return *this;
}

void Konto::SetKunde(std::shared_ptr<Kunde> kunde){
    this->kunde = kunde;
}