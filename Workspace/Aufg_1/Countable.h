//
// Created by Lukas Lübberding on 24.03.21.
//
#include <iostream>
#ifndef AB01_COUNTABLE_H
#define AB01_COUNTABLE_H
static std::uint32_t ncount=0;

class Countable {
private:
    std::uint32_t ident;
    //static std::uint32_t ncount;

public:
    Countable():ident(ncount){
        std::cout << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(this)
        << std::dec << " Object " << ident << "/" << ncount++ << " created.\n";
    }

    ~Countable() {
        std::cout << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(this)
        << std::dec << " Object " << ident << " destroyed.\n";
    }

    std::uint64_t identifier() const { return ident; }

};
#endif //AB01_COUNTABLE_H
