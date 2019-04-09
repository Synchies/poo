#include "headers/Agence.h"
#include "headers/string2commande.h"

void helpList() {
    std::cout << "____________________________________________________________________________________________" << std::endl;
    std::cout << "Liste des commandes disponibles :" << std::endl;
    std::cout << "  - @nouveauClient : permet de créer un nouveau client (vendeur/acheteur)." << std::endl;
    std::cout << "  - @nouveauBien : créez un nouveau bien (appartement/maison/terrain/local professionnel)." << std::endl;
    std::cout << "  - @listeBiens : liste tous les biens. Filtre disponible : par type de bien." << std::endl;
    std::cout << "Liste des commandes en cours de développement :" << std::endl;
    std::cout << "  - @listeClients : liste tous les clients. Filtre disponible : par type de client." << std::endl;
    std::cout << "  - @rechercherBien : recherche particulière à partir de paramètres donnés." << std::endl;
    std::cout << "  - @rechercherClient : recherche particulière à partir de paramètres donnés." << std::endl;
    std::cout << "____________________________________________________________________________________________" << std::endl;
}

int main() {
    bool continuer = true;
    Agence A = Agence("UnToitPourTous");

    A.AjoutClient("lire");
    A.AjoutBien("lire");

    // MESSAGE D'ACCUEIL
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "| Bienvenue sur le logiciel de gestion de UnToitPourTous.                                       |" << std::endl;
    std::cout << "| Vous devez taper des commandes pour utiliser ce logiciel.                                     |" << std::endl;
    std::cout << "| /!\\ Pour toute information sur les commandes existantes, utilisez la commande \"@help\" /!\\     |" << std::endl;
    std::cout << "| Pour QUITTER le logiciel, tapez \"@quit\"                                                       |" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;

    // LE PROGRAMME TOURNE ET ATTEND DES COMMANDES TANT QUE L'UTILISATEUR N'A PAS APPELE LA COMMANDE POUR QUITTER
    while(continuer) {

        // Saisie des commandes
        std::string commande;
        std::cout << "Entrez la commande de votre choix : ";
        std::getline(std::cin, commande);

        // Une fois la commande saisie, traitement de la commande
        switch (string2commande(commande)) {
            case invalide:
                std::cout << "Commande invalide, tapez @help pour voir la liste des commandes disponibles." << std::endl; 
                break;
            case help:
                helpList();
                break;
            case quit:
                continuer = false;
                break;
            case nouveauClient:
                A.AjoutClient("nouveau");
                break;
            case nouveauBien:
                A.AjoutBien("nouveau", (A.getLastIdBien())+1);
                break;
            case listeBiens:
                A.listeBiens();
                break;
            case listeClients:
                A.listeClients();
                break;
            case rechercheClient:
                A.rechercherClient();
                break;
            case rechercheBien:
                A.rechercherBien();
                break;
        }
    }

    std::cout << "A bientôt !" << std::endl;
    return EXIT_SUCCESS;
}