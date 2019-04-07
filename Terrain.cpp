#include "headers/Terrain.h"

Terrain::Terrain() : Bien() {}
Terrain::Terrain(int id, int prix, std::string adresse, std::string vendeur, float surface, bool _constructible) :
    Bien(id, prix, adresse, vendeur, surface),
    constructible(_constructible) {

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