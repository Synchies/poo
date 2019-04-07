#include "headers/Bien.h"

Bien::Bien() {}

Bien::Bien(int _id, int _prix, std::string _adresse, std::string _vendeur, float _surface) :
    id(_id),
    prix(_prix),
    adresse(_adresse),
    vendeur(_vendeur),
    surface(_surface) {}

int Bien::getId() {
    return id;
}