#include "headers/LocalPro.h"

LocalPro::LocalPro() : Bien() {}
LocalPro::LocalPro(int id, int prix, std::string adresse, int vendeur, float surface, float _vitrine, bool _stockage, bool creer) :
    Bien(id, prix, adresse, vendeur, surface, "l"),
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
                bFile << _vitrine << std::endl;
                bFile << _stockage << std::endl;

                bFile.close();
            }

            else {
                std::cout << "Erreur : Ouverture impossible de biens.txt" << std::endl;
                return;
            }
            std::cout << " --- Local Professionnel ajouté avec succès ! ---" << std::endl;
        }
    }

float LocalPro::getVitrine() {
    return vitrine;
}

bool LocalPro::hasStockage() {
    return stockage;
}

void LocalPro::Affiche() {
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  |            Informations LocalPro             |" << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
    std::cout << "  | Identifiant bien : " << id << std::endl;
    std::cout << "  | Prix : " << prix << std::endl;
    std::cout << "  | Adresse : " << adresse << std::endl;
    std::cout << "  | Vendeur : " << vendeur << std::endl;
    std::cout << "  | Surface : " << surface << std::endl;
    std::cout << "  | Vitrine : " << vitrine << std::endl;
    std::cout << "  | Stockage : " << (stockage ? "Oui" : "Non") << std::endl;
    std::cout << "  ------------------------------------------------" << std::endl;
}