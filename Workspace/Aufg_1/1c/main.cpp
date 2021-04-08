#include <memory>

#include "Konto.h"


std::shared_ptr<Konto> createOwnerAccount(const std::string& name, std::uint32_t account){
    auto konto = std::make_shared<Konto>(account);
    auto kunde = std::make_shared<Kunde>(name);
    konto->SetKunde(kunde);
    kunde->SetKonto(konto);

    konto->print();
    kunde->print();

    return konto;
}


int main(){
    std::cout << "Start" << std::endl;

    auto p = createOwnerAccount("Ernie", 1234);

    std::cout << "End" << std::endl;

    return 0;
}