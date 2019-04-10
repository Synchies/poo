#include "headers/Bien.h"

Bien::Bien() {}

Bien::Bien(int _id, int _prix, std::string _adresse, int _vendeur, float _surface) :
    id(_id),
    prix(_prix),
    adresse(_adresse),
    vendeur(_vendeur),
    surface(_surface){}

int Bien::getId() {
    return id;
}

float Bien::getPrix() {
    return prix;
}

std::string Bien::getAdresse() {
    return adresse;
}

int Bien::getVendeur() {
    return vendeur;
}

float Bien::getSurface() {
    return surface;
}

std::string Bien::getType() {
    return type;
}

void Bien::Affiche() const {
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  |              Informations Bien               |" << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  | Identifiant bien : " << id << std::endl;
    std::cout << "  | Prix : " << prix << std::endl;
    std::cout << "  | Adresse : " << adresse << std::endl;
    std::cout << "  | Vendeur : " << vendeur << std::endl;
    std::cout << "  | Surface : " << surface << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
}