#include "headers/Vendeur.h"

Vendeur::Vendeur() : Client() {}
Vendeur::Vendeur(std::string nom, std::string adresse) : Client(nom, adresse) {
    std::ofstream bFile("files/vendeurs.txt", std::ios::out | std::ios::app);

    if (bFile) {
        bFile << nom << std::endl;
        bFile << adresse << std::endl;

        bFile.close();
    }

    else std::cout << "Erreur : Ouverture impossible de vendeurs.txt" << std::endl;
}

void Vendeur::AjoutBien(int id) {
    biens.push_back(id);
}