//
// Created by Lukas Lübberding on 16.06.21.
//

#ifndef MALEFIZ_WÜRFELVIEW_H
#define MALEFIZ_WÜRFELVIEW_H

#include "Würfel.h"
using namespace std;

class WürfelView {

public:
    static void show(Würfel x){
        cout << x.getAugenzahl() << endl;
    }
};

#endif //MALEFIZ_WÜRFELVIEW_H
