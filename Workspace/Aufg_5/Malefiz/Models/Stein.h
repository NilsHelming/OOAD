#pragma once

class Stein;

#include <string>

#include "..\Interfaces\Model.h"

class Stein : public Model {
public:
    virtual ~Stein() = default;
    virtual std::string getFarbe() const = 0;
    virtual bool istSpielfigur() const = 0;
    virtual bool istSperrstein() const = 0;
};