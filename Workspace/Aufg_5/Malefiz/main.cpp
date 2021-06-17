#include <iostream>
#include <memory>

#include "Controller\MfController.h"

int main(){
    auto ctrl = MfController();
    ctrl.gameLoop();
    return 0;
}