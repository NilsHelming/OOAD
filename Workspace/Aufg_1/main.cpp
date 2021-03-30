#include <iostream>
#include <memory>
#include "KundeKonto.h"

using namespace std;

unique_ptr<Konto> createOwnerAccount (const string& name, uint32_t account){
    cout << "Go to Bank and create account for Peter." << endl;

    auto c = make_unique<Konto>(account,name);

    {
       c->print();
       cout << " ---> ";
       c->printPointer();
       cout << endl;

       c->printPointer();
       cout << " ---> ";
       c->print();
       cout << endl;
    }
    cout << "Leave the bank and delete complete account" << endl;
    return c; //! konto also rückgabe
}

shared_ptr<Konto> createSharedOwnerAccount (const string& name, uint32_t account){
    cout << "Go to shared Bank and create account for Peter." << endl;

    auto c = make_shared<Konto>(account);
    auto p = make_shared<Kunde>(name);

    c->setKunde(p);
    p->setKonto(c);
    {
        c->print();
        cout << " ---> ";
        p->print();
        cout<<endl;

        c->getSharedKunde()->print();
        cout << " ---> ";
        p->getSharedKonto()->print();
        cout<<endl;
    }
    cout << "Leave the shared bank and delete complete account" << endl;
    return c;
}

shared_ptr<Konto> createPerfectOwnerAccount (const string& name, uint32_t account) {

    cout << "Go to perfect Bank and create account for Peter." << endl;
    auto c = make_shared<Konto>(account, name);
    c->getSharedKunde()->setKonto(c);

    {
        c->print();
    }

    cout << "Leave the perfect bank and delete complete account" << endl;
    return c;
}

int main() {

    auto accountKonto = createOwnerAccount("Peter", 1345);
    auto accountShared = createSharedOwnerAccount("sharedPeter", 4854);
    //! die Pointer zwischen Kunde und Konto bleiben bestehen!
    //auto accountPerfect = createPerfectOwnerAccount("perfectPeter", 12543);

    return 0;
}
