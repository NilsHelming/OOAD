//
// Created by Lukas Lübberding on 17.06.21.
//

#ifndef MALEFIZ_SPIELFELDVIEW_H
#define MALEFIZ_SPIELFELDVIEW_H

#include "Spielfeld.h"
using namespace std;

#define NC "\e[0m"
#define RED "\e[0;31m"
#define CYN "\e[0;36m"



class SpielfeldView {
public:
    static void show (Spielfeld spielfeld){
        for (int i = 4; i>=0; i--){
            for (int y = 0; y<10; y++){
                if (spielfeld.getFeld(i,y) == 0){
                    cout << "\t";
                } else {
                    if (spielfeld.getFeld(i, y) == 2) {
                    cout << RED << " " << i << ":" << y << " ";
                    cout << NC;
                    }
                    if (spielfeld.getFeld(i, y) == 3){
                        cout << CYN << " " << i << ":" << y << " ";
                        cout << NC;
                    }
                    if (spielfeld.getFeld(i, y) == 1){
                        cout << NC << " " << i << ":" << y << " ";
                    }
                }
            }
            cout << endl;
        }
    }
};

#endif //MALEFIZ_SPIELFELDVIEW_H
