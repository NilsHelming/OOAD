//
// Created by Lukas Lübberding on 24.03.21.
//
#include <iostream>
#include <memory>
#include "Countable.h"
using namespace std;

#ifndef AB01_KUNDEKONTO_H
#define AB01_KUNDEKONTO_H

class Konto;

class Kunde : public Countable {
private:
    string name;
    shared_ptr<Konto> sharedKonto;

public:
    Kunde(const string &name) : name(name) {}

    ~Kunde() {

    }

    void print (){
        cout << "Kunde (" << name << ", Object " << this->identifier() << ")";
    }
    void setKonto(shared_ptr<Konto> konto){
        sharedKonto = konto;
    }

    const shared_ptr<Konto> &getSharedKonto() const {
        return sharedKonto;
    }
};

class Konto : public Countable {
private:
    uint32_t _ident;
    unique_ptr<Kunde> kontoKunde; //! muss Unique
    shared_ptr<Kunde> sharedKunde;

public:
    Konto(uint32_t ident, string name) : _ident(ident) {
        kontoKunde = make_unique<Kunde>(name);
    }
    Konto(uint32_t ident) : _ident(ident){
    }

    ~Konto() {

    }

    void print (){
        cout << "Konto (" << _ident << ", Object " << this->identifier() << ")";
    }
    void printPointer (){
        kontoKunde->print();
    }
    void setKunde(shared_ptr<Kunde> kunde){
        sharedKunde = kunde;
    }

    const shared_ptr<Kunde> &getSharedKunde() const {
        return sharedKunde;
    }
};
#endif //AB01_KUNDEKONTO_H
