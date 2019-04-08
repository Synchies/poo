#include "headers/Agence.h"
#include "headers/string2commande.h"
#include "headers/commandes.h"

void help() {
    
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
    //system("PAUSE");


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
                help();
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
        }
    }

    /*// Acheteurs (clients)
    Acheteur* c1 = new Acheteur("Freud", "34 rue des Lauriers");
    Acheteur* c2 = new Acheteur("Hernandez", "98  boulevard Albin Durand");
    Acheteur* c3 = new Acheteur("Stevens", "93  rue de la Boétie");
    Acheteur* c4 = new Acheteur("Gonzales", "125  boulevard Bryas");
    Acheteur* c5 = new Acheteur("Bullock", "117  rue du Général Ailleret");
    Acheteur* c6 = new Acheteur("Brown", "42  rue Jean Vilar");

    // Vendeurs (clients)
    Vendeur* c7 = new Vendeur("Renaut", "125 avenue des Beaux-Arts");
    Vendeur* c8 = new Vendeur("Nikos", "2 impasse de la Jonquille");
    Vendeur* c9 = new Vendeur("Bernard", "89 rue Emile Zola");
    Vendeur* c10 = new Vendeur("Giroux", "141  Avenue De Marlioz");
    Vendeur* c11 = new Vendeur("Richard", "64  Square de la Couronne");
    Vendeur* c12 = new Vendeur("Lamoureux", "27  rue Banaudon");
    Vendeur* c13 = new Vendeur("Tanguay", "93  rue Léon Dierx");
    Vendeur* c14 = new Vendeur("Asselin", "110  rue Bonneterie");
    Vendeur* c15 = new Vendeur("Dupont", "8 chemin Boueux");

    // Ajout de tous les clients à l'agence
    a->AjoutClient(*c1);
    a->AjoutClient(*c2);
    a->AjoutClient(*c3);
    a->AjoutClient(*c4);
    a->AjoutClient(*c5);

    a->AjoutClient(*c6);
    a->AjoutClient(*c7);
    a->AjoutClient(*c8);
    a->AjoutClient(*c9);
    a->AjoutClient(*c10);

    a->AjoutClient(*c11);
    a->AjoutClient(*c12);
    a->AjoutClient(*c13);
    a->AjoutClient(*c14);
    a->AjoutClient(*c15);
    // Fin ajout

    // Appartements(id, prix, adresse, vendeur, surface, nbPieces, etage, totalapparts, garage, cave, balcon)
    Appartement* b1 = new Appartement(0, 120000, "5 avenue du Truc", "Nikos", 50, 2, 1, 18, 0, 1, 1);
    Appartement* b2 = new Appartement(1, 290000, "7 chemin de l'Evangile", "Lamoureux", 110, 4, 2, 6, 1, 1, 1);
    Appartement* b3 = new Appartement(2, 70000, "54 impasse Montparnasse", "Giroux", 18.4, 1, 0, 90, 0, 0, 0);

    // Maisons(id, prix, adresse, vendeur, surface, nbPieces, garage, jardin, piscine)
    Maison* b4 = new Maison(3, 480000, "17 place de la Concorde", "Richard", 145, 4, 1, 1, 1);
    Maison* b5 = new Maison(4, 550000, "16 impasse Pasteur", "Renaut", 170, 5, 1, 1, 1);
    Maison* b6 = new Maison(5, 190000, "99 rue des Seaux", "Tanguay", 65, 3, 0, 1, 0);

    // Terrains(id, prix, adresse, vendeur, surface, constructible)
    Terrain* b7 = new Terrain(6, 860000, "Place des Hommes Grands", "Bernard", 3600, 1);
    Terrain* b8 = new Terrain(7, 130000, "1 chemin des Bruyères", "Asselin", 780, 0);
    Terrain* b9 = new Terrain(8, 90000, "4 rue Louis de Funès", "Lamoureux", 130, 1);

    // Locaux(id, prix, adresse, vendeur, surface, taillevitrine, stockage)
    LocalPro* b10 = new LocalPro(9, 150000, "3 rue de la Poudreuse", "Giroux", 62.5, 7, 1);
    LocalPro* b11 = new LocalPro(10, 80000, "17 avenue Réno", "Renaut", 27, 3.7, 1);
    LocalPro* b12 = new LocalPro(11, 2400000, "8 avenue des Champs Elysées", "Giroux", 241, 30, 1);

    // Ajout de tous les biens à l'agence
    a->AjoutAppartement(*b1);
    a->AjoutAppartement(*b2);
    a->AjoutAppartement(*b3);
    a->AjoutMaison(*b4);
    a->AjoutMaison(*b5);
    a->AjoutMaison(*b6);
    a->AjoutTerrain(*b7);
    a->AjoutTerrain(*b8);
    a->AjoutTerrain(*b9);
    a->AjoutLocal(*b10);
    a->AjoutLocal(*b11);
    a->AjoutLocal(*b12);
    // Fin ajout*/

    /*// Deux acheteurs font une visite + proposition d'achat
    c3->AjoutVisite(b1->getId(), 1, 140000);
    c7->AjoutVisite(b5->getId(), 1, 70000);
    c3->Affiche();*/

    std::cout << "A bientôt !" << std::endl;
    return EXIT_SUCCESS;
}