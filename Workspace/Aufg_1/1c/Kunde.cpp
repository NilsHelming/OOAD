#include <iostream>
#include <string>

#include "Konto.h"
#include "Kunde.h"

void Kunde::print(){
    std::cout << this->tostring() << " --> " << konto.lock()->tostring() << std::endl;
}

std::string Kunde::tostring(){
    return "Kunde (" + this->name + ", Object " + std::to_string(this->identifier()) + ")";
}

Kunde::Kunde(const std::string& name){
    this->name = name;
}
Kunde::Kunde(const Kunde& src){
    *this = src;
}
Kunde& Kunde::operator= (const Kunde& src){
    if (this == &src)
        return *this;
    this->name = src.name;
    this->SetKonto(std::make_shared<Konto>(*(src.konto.lock())));
    // this->konto = nullptr;
    //XXXXX
    return *this;
}

void Kunde::SetKonto(std::shared_ptr<Konto> _konto){
    this->konto = _konto;
}