#include "headers/Vendeur.h"

Vendeur::Vendeur() : Client() {}
Vendeur::Vendeur(int id, std::string nom, std::string adresse, std::string typeClient, bool creer) : Client(id, nom, adresse, typeClient) {

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

    std::cout << "--- Vendeur ajouté avec succès ! ---" << std::endl;
}

void Vendeur::AjoutBien(int id, Bien bien) {
    biens[bien.getId()] = bien;
}

void Vendeur::Affiche(bool afficherBiens) const {
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "|        Informations client (Vendeur)         |" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "| Identifiant : " << id << std::endl;
    std::cout << "| Nom : " << nom << std::endl;
    std::cout << "| Adresse : " << adresse << std::endl;

    if (afficherBiens) {
        std::cout << "  ----------------------------------------------" << std::endl;
        std::cout << "  |               Biens en vente               |" << std::endl;
        std::cout << "  ----------------------------------------------" << std::endl;

        // parcourt des biens mis en vente par le vendeur
        std::map<int, Bien> ::const_iterator it;
        for (it = biens.begin(); it != biens.end(); it++) it->second.Affiche();
    }
    std::cout << "------------------------------------------------" << std::endl;
}