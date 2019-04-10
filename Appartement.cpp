#include "headers/Appartement.h"

Appartement::Appartement() : Bien() {}
Appartement::Appartement(int id, int prix, std::string adresse, int vendeur, float surface, int _nbPieces, int _etage, int _totalApparts, bool _garage, bool _cave, bool _balcon, bool creer) :
    Bien(id, prix, adresse, vendeur, surface, "a"),
    nbPieces(_nbPieces),
    etage(_etage),
    totalApparts(_totalApparts),
    garage(_garage),
    cave(_cave),
    balcon(_balcon) {
        if (creer) {
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
                bFile << _totalApparts << std::endl;
                bFile << _garage << std::endl;
                bFile << _cave << std::endl;
                bFile << _balcon << std::endl;

                bFile.close();
            }

            else {
                std::cout << "Erreur : impossible d'ouvrir le fichier biens.txt." << std::endl;
                return;
            }
            std::cout << " --- Appartement ajouté avec succès ! ---" << std::endl;
        }
    }

int Appartement::getNbPieces() {
    return nbPieces;
}

int Appartement::getEtage() {
    return etage;
}

int Appartement::getTotalApparts() {
    return totalApparts;
}

bool Appartement::hasGarage() {
    return garage;
}

bool Appartement::hasCave() {
    return cave;
}

bool Appartement::hasBalcon() {
    return balcon;
}

void Appartement::Affiche() {
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  |             Informations Appartement             |" << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  | Identifiant bien : " << id << std::endl;
    std::cout << "  | Prix : " << prix << std::endl;
    std::cout << "  | Adresse : " << adresse << std::endl;
    std::cout << "  | Vendeur : " << vendeur << std::endl;
    std::cout << "  | Surface : " << surface << std::endl;
    std::cout << "  | Nombre de pièces : " << nbPieces << std::endl;
    std::cout << "  | Etage : " << etage << std::endl;
    std::cout << "  | Appartements dans l'immeuble : " << totalApparts << std::endl;
    std::cout << "  | Garage : " << (garage ? "Oui" : "Non") << std::endl;
    std::cout << "  | Cave : " << (cave ? "Oui" : "Non") << std::endl;
    std::cout << "  | Balcon : " << (balcon ? "Oui" : "Non") << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
}