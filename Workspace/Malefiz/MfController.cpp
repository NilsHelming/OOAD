//
// Created by Lukas Lübberding on 16.06.21.
//
#include "iostream"
#include "vector"

#include "Würfel.h"
#include "WürfelView.h"
#include "Spieler.h"
#include "Spielfeld.h"
#include "SpielfeldView.h"

using namespace std;

class MfController {
public:

   static void gameOn() {
       cout << "läuft" << endl;

       //1.Create Würfel
       unique_ptr<Würfel> würfel = make_unique<Würfel>();
       unique_ptr<WürfelView> WView = make_unique<WürfelView>();

       //2.Create Spieler
       string spielerEins, spielerZwei;
       int alterEins, alterZwei;

       cout << "Geben Sie ihr Namen an:";
       cin >> spielerEins;
       cout << spielerEins + " bitte gebe dein Alter ein:";
       cin >> alterEins;
       cout << "Geben Sie ihr Namen an:";
       cin >> spielerZwei;
       cout << spielerZwei + " bitte gebe dein Alter ein:";
       cin >> alterZwei;

       unique_ptr<Spieler> SpEins = make_unique<Spieler>("Rot", alterEins, spielerEins);
       unique_ptr<Spieler> SpZwei = make_unique<Spieler>("Blau", alterZwei, spielerZwei);

       vector<Spieler> spielerListe;
       if (SpEins->getAlter() < SpZwei->getAlter()) {
           spielerListe.push_back(*SpEins);
           spielerListe.push_back(*SpZwei);
       } else {
           spielerListe.push_back(*SpZwei);
           spielerListe.push_back(*SpEins);
       }

       //3. Create Spielfeld
       unique_ptr<Spielfeld> spielfeld = make_unique<Spielfeld>();
       unique_ptr<SpielfeldView> spielfeldView = make_unique<SpielfeldView>();

       int xWahl, yWahl, neuX, neuY, temp;
       int i = 0;
      while (i != 6){
       cout << spielerListe[i].getName() + " du bist dran und würfelst eine: ";
       würfel->würfeln();
       WView->show(*würfel);

        cout << "SpielfeldView:" << endl;
        spielfeldView->show(*spielfeld);

        cout << "welche Spielfigur:";
        cin >> xWahl >> yWahl;
        cout << xWahl << " : " << yWahl << endl;

        cout << "wähle neuen Platz:";
        cin >> neuX >> neuY;
        spielfeld->setzteSpielfigus(i+2,neuX,neuY);
        spielfeld->setzteSpielfigus(1,xWahl, yWahl); //zurücksetzten alter Punkte

        if (neuX == 4 && neuY ==4){
            if (i==0){
                cout << spielerListe[0].getName() << " hat gewonnen!!" << endl;
            }
            if (i==1){
                cout << spielerListe[1].getName() << " hat gewonnen!!" << endl;
            }
            i=6;
        } else {
            i = (i+1)%2;
        }
        }

    }
};