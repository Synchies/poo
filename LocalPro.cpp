#include "headers/LocalPro.h"

LocalPro::LocalPro() : Bien() {}
LocalPro::LocalPro(int id, int prix, std::string adresse, std::string vendeur, float surface, float _vitrine, bool _stockage, bool creer) :
    Bien(id, prix, adresse, vendeur, surface),
    vitrine(_vitrine),
    stockage(_stockage) {
        if (creer) {
            std::ofstream bFile("files/biens.txt", std::ios::out | std::ios::app);

            if (bFile) {
                bFile << "l" << std::endl;
                bFile << id << std::endl;
                bFile << prix << std::endl;
                bFile << adresse << std::endl;
                bFile << vendeur << std::endl;
                bFile << surface << std::endl;
                bFile << _stockage << std::endl;
                bFile << _vitrine << std::endl;

                bFile.close();
            }

            else std::cout << "Erreur : Ouverture impossible de biens.txt" << std::endl;
        }
    }