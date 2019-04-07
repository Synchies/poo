#include "headers/Appartement.h"

Appartement::Appartement() : Bien() {}
Appartement::Appartement(int id, int prix, std::string adresse, std::string vendeur, float surface, int _nbPieces, int _etage, int _totalApparts, bool _garage, bool _cave, bool _balcon) :
    Bien(id, prix, adresse, vendeur, surface),
    nbPieces(_nbPieces),
    etage(_etage),
    totalApparts(_totalApparts),
    garage(_garage),
    cave(_cave),
    balcon(_balcon) {

        std::ofstream bFile("files/biens.txt", std::ios::out | std::ios::app);

        if (bFile) {
            bFile << "a" << std::endl;
            bFile << id << std::endl;
            bFile << prix << std::endl;
            bFile << adresse << std::endl;
            bFile << vendeur << std::endl;
            bFile << surface << std::endl;
            bFile << _nbPieces << std::endl;
            bFile << _etage << std::endl;
            bFile << _garage << std::endl;
            bFile << _cave << std::endl;
            bFile << _balcon << std::endl;

            bFile.close();
        }

        else std::cout << "Erreur : Ouverture impossible de biens.txt" << std::endl;

    }