#include <iostream>
#include <string>

#include "Konto.h"
#include "Kunde.h"

void Kunde::print(){
    std::cout << this->tostring() << " --> " << this->konto->tostring() << std::endl;
}

std::string Kunde::tostring(){
    return "Kunde (" + this->name + ", Object " + std::to_string(this->identifier()) + ")";
}

Kunde::Kunde(const std::string& name, Konto* konto){
    this->name = name;
    this->konto = konto;
}
Kunde::Kunde(const Kunde& src){
    *this = src;
}
Kunde& Kunde::operator= (const Kunde& src){
    if (this == &src)
        return *this;
    this->name = src.name;
    this->konto = nullptr;
    return *this;
}

void Kunde::SetKonto(Konto* konto){
    this->konto = konto;
}