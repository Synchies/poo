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

        else {
            std::cout << "Erreur : Ouverture impossible de acheteurs.txt" << std::endl;
            return;
        }
        std::cout << "--- Acheteur ajouté avec succès ! ---" << std::endl;
    }
}

void Acheteur::AjoutVisite(int idBien, bool proposition, int prix) {
    if (isVisited(idBien)) {
        std::cout << "--- Une visite a déjà été effectuée. ---" << std::endl;
        return;
    }

    visites[id] = std::make_pair(proposition, prix);
    std::cout << "--- Visite ajoutée avec succès ! ---" << std::endl;
}

bool Acheteur::isVisited(int idBien) {
    std::map<int, std::pair<bool, int> > ::iterator it = visites.find(idBien);
    if (it != visites.end()) return 1;
    return 0;
}

void Acheteur::supprimerVisite(int idBien) {
    if (isVisited(idBien)) {
        std::map<int, std::pair<bool, int> > ::iterator it = visites.find(idBien);
        visites.erase(idBien);
        std::cout << "--- Visite supprimée avec succès ! ---" << std::endl;
        return;
    }

    std::cout << "--- Aucune visite n'a été trouvée. ---" << std::endl;
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