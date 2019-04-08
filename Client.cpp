#include "headers/Client.h"

Client::Client() {}

Client::Client(int _id, std::string _nom, std::string _adresse) :
    id(_id),
    nom(_nom),
    adresse(_adresse) {}

Client::Client(const Client& c) :
    id(c.id),
    nom(c.nom),
    adresse(c.adresse) {}

std::string Client::getNom() {
    return nom;
}

void Client::Affiche() const {
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "|              Informations client             |" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "| Nom : " << nom << std::endl;
    std::cout << "| Adresse : " << adresse << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
}