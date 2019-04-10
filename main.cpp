#include "headers/Agence.h"
#include "headers/string2commande.h"

void helpList() {
    std::cout << "  - @nouveauClient : permet de créer un nouveau client (vendeur/acheteur)." << std::endl;
    std::cout << "  - @nouveauBien : créez un nouveau bien (appartement/maison/terrain/local professionnel)." << std::endl;
    std::cout << "  - @listeBiens : liste tous les biens. Filtre disponible : par type de bien." << std::endl;
    std::cout << "  - @listeClients : liste tous les clients. Filtre disponible : par type de client." << std::endl;
    std::cout << "  - @rechercheBien : recherche particulière à partir de paramètres donnés." << std::endl;
    std::cout << "  - @rechercheClient : recherche particulière à partir de paramètres donnés." << std::endl;
    std::cout << "  - @ajoutVisite : ajouter une visite d'un bien dans le profil d'un client acheteur (la visite comprend la proposition d'achat s'il y en a une ainsi que son prix)." << std::endl;
    std::cout << "  - @vente : réalisez une vente. Supprimera les visites liées au bien dans le profil acheteur, le bien dans la liste des biens disponibles, et dans la liste des biens du vendeur." << std::endl;
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
        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "|                     MENU PRINCIPAL                      |" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
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
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                   LISTE DES COMMANDES                   |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                helpList();
                break;
            case quit:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                        A BIENTOT                        |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                continuer = false;
                break;
            case nouveauClient:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                     CREER UN CLIENT                     |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                A.AjoutClient("nouveau");
                break;
            case nouveauBien:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                      CREER UN BIEN                      |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                A.AjoutBien("nouveau", (A.getLastIdBien())+1);
                break;
            case listeBiens:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                      LISTING BIENS                      |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                A.listeBiens();
                break;
            case listeClients:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                     LISTING CLIENTS                     |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                A.listeClients();
                break;
            case rechercheClient:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                     RECHERCHE CLIENT                    |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                A.rechercherClient();
                break;
            case rechercheBien:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                      RECHERCHE BIEN                     |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                A.rechercherBien();
                break;
            case ajoutVisite:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                     AJOUTER UNE VISITE                  |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                A.ajouterVisite();
                break;
            case vente:
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << "|                     AJOUTER UNE VENTE                   |" << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                A.realiserVente();
                break;
        }

        std::cout << "-----------------------------------------------------------" << std::endl;
    }
    return EXIT_SUCCESS;
}