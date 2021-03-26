#include <memory>

#include "Konto.h"


std::unique_ptr<Konto> createOwnerAccount(const std::string& name, std::uint32_t account){
    return std::make_unique<Konto>(account, name);
}

int main(){
    std::cout << "Start" << std::endl;

    auto p = createOwnerAccount("Ernie", 1234);

    p->print();

    std::cout << "End" << std::endl;

    return 0;
}