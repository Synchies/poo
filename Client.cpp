#include "headers/Client.h"

Client::Client() {}

Client::Client(int _id, std::string _nom, std::string _adresse, std::string _typeClient) :
    id(_id),
    nom(_nom),
    adresse(_adresse),
    typeClient(_typeClient) {}

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
    std::cout << "| Identifiant : " << id << std::endl;
    std::cout << "| Catégorie : " << (typeClient == "V" ? "Vendeur" : "Acheteur") << std::endl;
    std::cout << "| Nom : " << nom << std::endl;
    std::cout << "| Adresse : " << adresse << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
}

bool Client::isVendeur() {
    return typeClient == "V";
}

int Client::getId() {
    return id;
}

std::string Client::getAdresse() {
    return adresse;
}