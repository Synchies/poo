#include "headers/Vendeur.h"

Vendeur::Vendeur() : Client() {}
Vendeur::Vendeur(int id, std::string nom, std::string adresse, bool creer) : Client(id, nom, adresse) {

    if (creer) {
        std::ofstream bFile("files/vendeurs.txt", std::ios::out | std::ios::app);

        if (bFile) {
            bFile << id << std::endl;
            bFile << nom << std::endl;
            bFile << adresse << std::endl;

            bFile.close();
        }

        else std::cout << "Erreur : Ouverture impossible de vendeurs.txt" << std::endl;
    }
}

void Vendeur::AjoutBien(int id) {
    biens.push_back(id);
}