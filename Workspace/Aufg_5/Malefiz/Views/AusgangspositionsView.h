#pragma once

class AusgangspositionsView;

#include <memory>

#include "..\Interfaces\View.h"
#include "..\Models\Spielfeld.h"


class AusgangspositionsView : public View {
private:
    std::shared_ptr<Spielfeld> spielfeld;

public:
    explicit AusgangspositionsView(std::shared_ptr<Spielfeld>);
    void modelChanged();
    void show();
};