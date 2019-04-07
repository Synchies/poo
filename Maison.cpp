#include "headers/Maison.h"

Maison::Maison() : Bien() {}
Maison::Maison(int id, int prix, std::string adresse, std::string vendeur, float surface, int _nbPieces, bool _garage, bool _jardin, bool _piscine) :
    Bien (id, prix, adresse, vendeur, surface), 
    nbPieces(_nbPieces),
    garage(_garage),
    jardin(_jardin),
    piscine(_piscine) {

        std::ofstream bFile("files/biens.txt", std::ios::out | std::ios::app);

        if (bFile) {
            bFile << "m" << std::endl;
            bFile << id << std::endl;
            bFile << prix << std::endl;
            bFile << adresse << std::endl;
            bFile << vendeur << std::endl;
            bFile << surface << std::endl;
            bFile << _nbPieces << std::endl;
            bFile << _garage << std::endl;
            bFile << _jardin << std::endl;
            bFile << _piscine << std::endl;

            bFile.close();
        }

        else std::cout << "Erreur : Ouverture impossible de biens.txt" << std::endl;
    }