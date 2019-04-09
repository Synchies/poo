#include "headers/Terrain.h"

Terrain::Terrain() : Bien() {}
Terrain::Terrain(int id, int prix, std::string adresse, int vendeur, float surface, bool _constructible, bool creer) :
    Bien(id, prix, adresse, vendeur, surface),
    constructible(_constructible) {
        if (creer) {
            std::ofstream bFile("files/biens.txt", std::ios::out | std::ios::app);

            if (bFile) {
                bFile << "t" << std::endl;
                bFile << id << std::endl;
                bFile << prix << std::endl;
                bFile << adresse << std::endl;
                bFile << vendeur << std::endl;
                bFile << surface << std::endl;
                bFile << _constructible << std::endl;

                bFile.close();
            }

            else std::cout << "Erreur : Ouverture impossible de biens.txt" << std::endl;
        }

        std::cout << " --- Terrain ajouté avec succès ! ---" << std::endl;
    }

bool Terrain::isConstructible() {
    return constructible;
}

void Terrain::Affiche() {
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  |             Informations Terrain             |" << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  | Identifiant bien : " << id << std::endl;
    std::cout << "  | Prix : " << prix << std::endl;
    std::cout << "  | Adresse : " << adresse << std::endl;
    std::cout << "  | Vendeur : " << vendeur << std::endl;
    std::cout << "  | Surface : " << surface << std::endl;
    std::cout << "  | Constructible : " << (constructible ? "Oui" : "Non") << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
}