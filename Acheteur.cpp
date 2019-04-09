#include "headers/Acheteur.h"

Acheteur::Acheteur() : Client() {}
Acheteur::Acheteur(int id, std::string nom, std::string adresse, std::string typeClient, bool creer) : Client(id, nom, adresse, typeClient) {
    if (creer) {
        std::ofstream bFile("files/acheteurs.txt", std::ios::out | std::ios::app);

        if (bFile) {
            bFile << id << std::endl;
            bFile << nom << std::endl;
            bFile << adresse << std::endl;

            bFile.close();
        }

        else std::cout << "Erreur : Ouverture impossible de acheteurs.txt" << std::endl;
    }

    std::cout << "--- Acheteur ajouté avec succès ! ---" << std::endl;
}

void Acheteur::AjoutVisite(int id, bool proposition, int prix) {
    visites[id] = std::make_pair(proposition, prix);
}

void Acheteur::Affiche(bool afficherVisites) const {
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "|        Informations client (Acheteur)        |" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "| Nom : " << nom << std::endl;
    std::cout << "| Adresse : " << adresse << std::endl;
    if (afficherVisites) {
        std::cout << "  ----------------------------------------------" << std::endl;
        std::cout << "  |                  Visites                   |" << std::endl;
        std::cout << "  ----------------------------------------------" << std::endl;

        std::map<int, std::pair<bool, int> > ::const_iterator it;
        for (it = visites.begin(); it != visites.end(); it++) {
            std::cout << "  | Identifiant vente : " << it->first << std::endl;
            std::cout << "  | Proposition d'achat : " << (it->second.first ? "Oui" : "Non") << std::endl;
            std::cout << "  | Montant proposition : " << it->second.second << std::endl;
            std::cout << "  ----------------------------------------------" << std::endl;
        }
    }
    
    std::cout << "------------------------------------------------" << std::endl;
}