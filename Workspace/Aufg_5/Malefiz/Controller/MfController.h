#pragma once

class MfController;

#include <vector>
#include <memory>

#include "..\Interfaces\Controller.h"
#include "..\Models\Spieler.h"
#include "..\Models\Spielfeld.h"
#include "..\Models\Wuerfel.h"
#include "..\Views\SpielfeldView.h"
#include "..\Views\AusgangspositionsView.h"
#include "..\Views\ZugStatusView.h"

class MfController : public Controller {
private:
    std::vector<std::shared_ptr<Spieler>> spieler;
    std::shared_ptr<Spielfeld> spielfeld;
    std::shared_ptr<ZugStatus> zStatus;

    std::shared_ptr<SpielfeldView> sFeldView;
    std::shared_ptr<AusgangspositionsView> aPosView;
    std::shared_ptr<ZugStatusView> zStatView;
public:
    MfController();
    void viewChanged();
    void gameLoop();

private:
    void askWuerfel();
    std::shared_ptr<Feld> askVonFeld();
    std::shared_ptr<Feld> askZuFeld(std::shared_ptr<Feld> vonFeld);
    std::shared_ptr<Feld> askSperrFeld(std::shared_ptr<Feld> vonFeld, std::shared_ptr<Feld> leerFeld);
};