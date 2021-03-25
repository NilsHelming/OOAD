#pragma once

#include <iostream>

class Countable {
private:
    std::uint64_t ident;
    static std::uint64_t ncount;

public:
    Countable():ident(ncount) {
        std::cout << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(this)
        << std::dec << " Object " << ident << "/" << ncount++ << " created.\n";
    }
    ~Countable() {
        std::cout << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(this)
        << std::dec << " Object " << ident << " destroyed.\n";
    }

    std::uint64_t identifier() const {
        return ident;
    }
};