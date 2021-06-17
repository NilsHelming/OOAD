//
// Created by Lukas Lübberding on 16.06.21.
//

#ifndef MALEFIZ_WÜRFEL_H
#define MALEFIZ_WÜRFEL_H

#include "cstdlib"

class Würfel {
private:
    int augenzahl;
public:
    Würfel() {}
    void würfeln(){
        augenzahl = rand() % 6 + 1;
    }
    int getAugenzahl(){
        return augenzahl;
    }
};


#endif //MALEFIZ_WÜRFEL_H
