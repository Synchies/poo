#include "headers/Maison.h"

Maison::Maison() : Bien() {}
Maison::Maison(int id, int prix, std::string adresse, int vendeur, float surface, int _nbPieces, bool _garage, bool _jardin, bool _piscine, bool creer) :
    Bien (id, prix, adresse, vendeur, surface), 
    nbPieces(_nbPieces),
    garage(_garage),
    jardin(_jardin),
    piscine(_piscine) {
        if (creer) {
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

        std::cout << " --- Maison ajoutée avec succès ! ---" << std::endl;
    }

int Maison::getNbPieces() {
    return nbPieces;
}

bool Maison::hasGarage() {
    return garage;
}

bool Maison::hasJardin() {
    return jardin;
}

bool Maison::hasPiscine() {
    return piscine;
}

void Maison::Affiche() {
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  |             Informations Maison             |" << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  | Identifiant bien : " << id << std::endl;
    std::cout << "  | Prix : " << prix << std::endl;
    std::cout << "  | Adresse : " << adresse << std::endl;
    std::cout << "  | Vendeur : " << vendeur << std::endl;
    std::cout << "  | Surface : " << surface << std::endl;
    std::cout << "  | Nombre de pièces : " << nbPieces << std::endl;
    std::cout << "  | Garage : " << (garage ? "Oui" : "Non") << std::endl;
    std::cout << "  | Jardin : " << (jardin ? "Oui" : "Non") << std::endl;
    std::cout << "  | Piscine : " << (piscine ? "Oui" : "Non") << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
}