#pragma once

class SpielfeldView;

#include <memory>

#include "..\Interfaces\View.h"
#include "..\Models\Spielfeld.h"


class SpielfeldView : public View {
private:
    std::shared_ptr<Spielfeld> spielfeld;

public:
    explicit SpielfeldView(std::shared_ptr<Spielfeld>);
    void modelChanged();
    void show();
};