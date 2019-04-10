#include "headers/Agence.h"

// vide le buffer pour les entrées utilisateur
void clearBuffer() {
    std::cin.seekg(0, std::ios::end);

    if (!std::cin.fail())
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    else
        std::cin.clear();
}

// vérifie s'il n'y a pas d'erreur de cin
bool errorCin() {
    if (std::cin.bad()) {
        std::cerr << "Erreur." << std::endl;
        return true;
    }

    else if (std::cin.eof()) {
        std::cout << std::endl << "EOF" << std::endl;
        return true;
    }

    else
        return false;
}

// boucle pour la saisie de l'utilisateur (permet de sécuriser et de redonner sa chance à l'utilisateur)
std::string userInput(std::string message, std::string errorMessage, int minimumSize, std::string numeral = "none") {
    std::string input;
    bool error;
    for (;;) {
        error = 0;
        clearBuffer();
        std::cout << "          --------------------------------" << std::endl;
        std::cout << "          |      Entrée utilisateur      |" << std::endl;
        std::cout << "          --------------------------------" << std::endl;
        std::cout << message;
        std::getline(std::cin, input);

        if (input.size() < minimumSize) {
            std::cerr << errorMessage << std::endl;
            error = 1;
        }

        else if (numeral != "none") {
            if ((numeral == "float" && input.find_first_not_of("0123456789.,") != std::string::npos) ||
                (numeral == "int" && input.find_first_not_of("0123456789") != std::string::npos)) {
                std::cout << "Erreur : vous devez rentrer un nombre." << std::endl;
                error = 1;
            }

            else if (numeral == "bool" && input.find_first_not_of("ouinon") != std::string::npos) {
                std::cout << "Erreur : vous devez entrer oui ou non." << std::endl;
                error = 1;
            }

            else {
                int n = input.length();
                char inputTemp[n+1];
                strcpy(inputTemp, input.c_str());

                if (!input[0]) {
                    std::cout << "Erreur : vous devez rentrer un nombre." << std::endl;
                    error = 1;
                }
            }
        }

        if (!errorCin() && !error) {
            clearBuffer();
            return input;
        }
    }
}

Agence::Agence() {}
Agence::Agence(std::string _nom) :
    nom(_nom) {}

Agence::Agence(const Agence& a) :
    nom(a.nom) {}

// AjoutClient("lire") va lire les clients dans les fichiers, pour charger le programme au lancement. AjoutClient("nimportequoi") va ajouter un client à la base de données (donc écrire dans le fichier).
void Agence::AjoutClient(std::string action, std::string typeClient) {

    if (action == "lire") {
        std::ifstream aFile("files/acheteurs.txt", std::ios::in);
        std::ifstream vFile("files/vendeurs.txt", std::ios::in);

        // contenu de l'entrée utilisateur.
        std::string contenu = "";
        // permet de compter les lignes parcourues.
        int curseur = 0;

        if (aFile) {
            std::string nom, adresse;
            int id;

            while(std::getline(aFile, contenu)) {
                switch (curseur%3) {
                    case 0:
                        id = stoi(contenu);
                        break;
                    case 1:
                        nom = contenu;
                        break;
                    case 2:
                        adresse = contenu;
                        Acheteur acheteur = Acheteur(id, nom, adresse, "A", 0);
                        clients[id] = acheteurs[id] = acheteur;
                        break;
                }

                curseur++;
            }
        }

        if (vFile) {
            std::string nom, adresse;
            int id;
            curseur = 0;

            while (std::getline(vFile, contenu)) {
                switch (curseur%3) {
                    case 0:
                        id = stoi(contenu);
                        break;
                    case 1:
                        nom = contenu;
                        break;
                    case 2:
                        adresse = contenu;
                        Vendeur vendeur = Vendeur(id, nom, adresse, "V", 0);
                        clients[id] = vendeurs[id] = vendeur;
                        break;
                }

                curseur++;
            }
        }
    }

    else {
        // informations du client
        std::string adresseClient;
        std::string nomClient;

        nomClient = userInput("Saisissez le nom du client : ", "Erreur : Vous devez saisir un nom de client valide.", 2);
        adresseClient = userInput("Saisissez l'adresse du client : ", "Erreur : Vous devez saisir une adresse de client valide.", 5);

        if (typeClient == "undefined") {
            typeClient = userInput("Acheteur/Vendeur ? (Tapez A ou V) : ", "Erreur : Vous devez saisir A ou V.", 1);
            while (typeClient != "A" && typeClient != "V" || typeClient.size() > 1) {
                std::cerr << "Erreur : Vous devez saisir A ou V." << std::endl;
                typeClient = userInput("Acheteur/Vendeur ? (Tapez A ou V) : ", "Erreur : Vous devez saisir A ou V.", 1);
            }
        }

        if (typeClient == "A") {
            Acheteur c = Acheteur(getLastIdClient()+1, nomClient, adresseClient, "A");
            clients[c.getId()] = acheteurs[c.getId()] = c;
        }

        else {
            Vendeur c = Vendeur(getLastIdClient()+1, nomClient, adresseClient, "V");
            clients[c.getId()] = vendeurs[c.getId()] = c;
        }
    }
}

void Agence::AjoutAppartement(Appartement A) {
    apparts[A.getId()] = A;
    biens[A.getId()] = A;
}

void Agence::AjoutMaison(Maison M) {
    maisons[M.getId()] = M;
    biens[M.getId()] = M;
}

void Agence::AjoutTerrain(Terrain T) {
    terrains[T.getId()] = T;
    biens[T.getId()] = T;
}

void Agence::AjoutLocal(LocalPro L) {
    locaux[L.getId()] = L;
    biens[L.getId()] = L;
}

// AjoutBien("lire") va lire dans le fichiers biens.txt les différents bien, pour initialiser le programme au démarrage. AjoutBien("nimportequoi") va simplement ajouter un bien dans le fichier.
void Agence::AjoutBien(std::string action, int idBien) {
    if (action == "lire") {
        std::ifstream bFile("files/biens.txt", std::ios::in);
        // contenu de l'entrée utilisateur.
        std::string contenu;
        // permet de compter les lignes parcourues.
        int curseur;

        if (bFile) {
            // curseur pour savoir à quel paramètre on se situe, selon le type de bien recontré
            curseur = 0;
            std::string typeBien, adresse;
            int id, nbPieces, etage, totalApparts;
            float surface, vitrine;
            int prix, vendeurId;
            bool garage, cave, balcon, stockage, jardin, piscine, constructible;
            // modulo correspond au nombre de paramètres demandés par la classe.
            int modulo;

            while(std::getline(bFile, contenu)) {
                if (contenu == "a") {
                    modulo = 12;
                    curseur = 0;
                }

                else if (contenu == "m") {
                    modulo = 10;
                    curseur = 0;
                }

                else if (contenu == "t") {
                    modulo = 7;
                    curseur = 0;
                }

                else if (contenu == "l") {
                    modulo = 8;
                    curseur = 0;
                }

                else {
                    switch (modulo) {
                        case 12:
                            switch(curseur%12) {
                                case 0: break;
                                case 1: id = stoi(contenu);
                                break;
                                case 2: prix = stoi(contenu);
                                break;
                                case 3: adresse = contenu;
                                break;
                                case 4: vendeurId = stoi(contenu);
                                break;
                                case 5: surface = stof(contenu);
                                break;
                                case 6: nbPieces = stoi(contenu);
                                break;
                                case 7: etage = stoi(contenu);
                                break;
                                case 8: totalApparts = stoi(contenu);
                                break;
                                case 9: garage = contenu == "1";
                                break;
                                case 10: cave = contenu == "1";
                                break;
                                case 11:
                                    balcon = contenu == "1";
                                    Appartement appart = Appartement(id, prix, adresse, vendeurId, surface, nbPieces, etage, totalApparts, garage, cave, balcon, 0);
                                    AjoutAppartement(appart);
                                    break;
                            }
                            break;
                        case 10:
                            switch(curseur%10) {
                                case 0: break;
                                case 1: id = stoi(contenu);
                                break;
                                case 2: prix = stoi(contenu);
                                break;
                                case 3: adresse = contenu;
                                break;
                                case 4: vendeurId = stoi(contenu);
                                break;
                                case 5: surface = stof(contenu);
                                break;
                                case 6: nbPieces = stoi(contenu);
                                break;
                                case 7: garage = contenu == "1";
                                break;
                                case 8: jardin = contenu == "1";
                                break;
                                case 9:
                                    piscine = contenu == "1";
                                    Maison maison = Maison(id, prix, adresse, vendeurId, surface, nbPieces, garage, jardin, piscine, 0);
                                    AjoutMaison(maison);
                                    break;
                            }
                            break;
                        case 7:
                            switch(curseur%7) {
                                case 0: break;
                                case 1: id = stoi(contenu);
                                break;
                                case 2: prix = stoi(contenu);
                                break;
                                case 3: adresse = contenu;
                                break;
                                case 4: vendeurId = stoi(contenu);
                                break;
                                case 5: surface = stof(contenu);
                                break;
                                case 6:
                                    constructible = contenu == "1";
                                    Terrain terrain = Terrain(id, prix, adresse, vendeurId, surface, constructible, 0);
                                    AjoutTerrain(terrain);
                                    break;
                            }
                            break;
                        case 8:
                            switch(curseur%8) {
                                case 0: break;
                                case 1: id = stoi(contenu);
                                break;
                                case 2: prix = stoi(contenu);
                                break;
                                case 3: adresse = contenu;
                                break;
                                case 4: vendeurId = stoi(contenu);
                                break;
                                case 5: surface = stof(contenu);
                                break;
                                case 6: vitrine = stof(contenu);
                                break;
                                case 7:
                                    stockage = contenu == "1";
                                    LocalPro local = LocalPro(id, prix, adresse, vendeurId, surface, vitrine, stockage, 0);
                                    AjoutLocal(local);
                                    break;
                            }
                            break;
                    }
                }
                curseur++;
            }
        }
    }

    else {
        std::string temp, typeBien, choix;
        std::vector<std::string> types = {"A", "M", "T", "L"};
        int prix, count = 0, idVendeur = -1;
        std::string adresse, vendeur;
        float surface;

        std::cout << "Choisissez, parmi la liste ci-dessous, le type de bien que vous souhaitez ajouter :" << std::endl;
        std::cout << "- Appartement : tapez A" << std::endl;
        std::cout << "- Maison : tapez M" << std::endl;
        std::cout << "- Terrain : tapez T" << std::endl;
        std::cout << "- Local Professionnel : tapez L" << std::endl;

        typeBien = userInput("Saisissez la lettre correspondante : ", "Erreur : Vous devez saisir A, M, T ou L.", 1);
        while (typeBien.size() != 1 || std::find(types.begin(), types.end(), typeBien) == types.end()) {
            std::cerr << "Erreur : Vous devez saisir A, M, T ou L." << std::endl;
            typeBien = userInput("Saisissez la lettre correspondante : ", "Erreur : Vous devez saisir A, M, T ou L.", 1);
        }

        vendeur = userInput("Nom du vendeur : ", "Erreur : vous devez saisir un nom valide.", 2);
        std::map<int, Vendeur> ::iterator itVendeur;;
        std::map<int, Client> VendeursTrouves = findClient(vendeur, 1);
        std::map<int, Client> ::iterator itVendeursTrouves;
        if (VendeursTrouves.size() == 1) {
            itVendeursTrouves = VendeursTrouves.begin();
            idVendeur = itVendeursTrouves->first;
        }

        else if (VendeursTrouves.size() > 1) {
            std::cout << "Plusieurs clients portant ce nom ont été trouvés. Choisissez le client correspondant parmi la liste ci-dessous, en entrant \"id\" (vous entrerez par la suite son identifiant). Si aucun vendeur ne correspond, tapez \"new\" pour créer un profil :" << std::endl;
            for (itVendeursTrouves = VendeursTrouves.begin(); itVendeursTrouves != VendeursTrouves.end(); itVendeursTrouves++) itVendeursTrouves->second.Affiche();
            
            choix = userInput("Saisie (\"id\" ou \"new\") : ", "Erreur : vous devez rentrer \"id\" ou \"new\"", 1);
            while (choix != "new" && choix != "id") {
                std::cout << "Erreur : vous devez rentrer \"id\" ou \"new\"" << std::endl;
                choix = userInput("Saisie (\"id\" ou \"new\") : ", "Erreur : vous devez rentrer \"id\" ou \"new\"", 1);
            }

            if (choix == "new") {
                AjoutClient("nouveau", "V");

                std::map<int, Vendeur> ::iterator it;
                for (it = vendeurs.begin(); it != vendeurs.end(); it++) idVendeur = it->first;
            }

            else {
                std::map<int, Vendeur> ::iterator it = vendeurs.find(idVendeur);

                idVendeur = stoi(userInput("Identifiant du vendeur : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
                while (it == vendeurs.end()) {
                    idVendeur = stoi(userInput("Identifiant du vendeur : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
                    it = vendeurs.find(idVendeur);
                    std::cout << "Erreur : vous devez rentrer un nombre." << std::endl;
                }
            }
        }

        else {
            std::cout << "Ce vendeur n'existe pas. Voulez-vous le créer ? /!\\ nécessaire pour une création de bien /!\\" << std::endl;
            bool creerVendeur = userInput("Réponse (oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 3, "bool") == "oui";

            if (creerVendeur) {
                AjoutClient("nouveau", "V");

                std::map<int, Vendeur> ::iterator it;
                for (it = vendeurs.begin(); it != vendeurs.end(); it++) idVendeur = it->first;
            }

            else {
                std::cout << "Ajout de bien annulé. Le client n'existe pas, et l'utilisateur n'a pas voulu le créer." << std::endl;
                return;
            }
        }

        surface = stof(userInput("Surface : ", "Erreur : vous devez rentrer un nombre.", 1, "float"));
        prix = stoi(userInput("Prix : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
        adresse = userInput("Adresse du bien : ", "Erreur : vous devez saisir une adresse valide", 5);

        std::cout << "--- Détails du bien ---" << std::endl;

        if (typeBien == "A") {
            int nbPieces = stoi(userInput("Nombre de pièces dans l'appartement : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
            int etage = stoi(userInput("Etage de l'appartement : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
            int totalApparts = stoi(userInput("Nombre total d'appartements dans l'immeuble : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));

            bool balcon = userInput("Balcon ? (Taper oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 1, "bool") == "oui";
            bool garage = userInput("Garage ? (Taper oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 1, "bool") == "oui";
            bool cave = userInput("Cave ? (Taper oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 1, "bool") == "oui";

            Appartement appart = Appartement(idBien, prix, adresse, idVendeur, surface, nbPieces, etage, totalApparts, garage, cave, balcon);
            biens[idBien] = apparts[idBien] = appart;
        }

        else if (typeBien == "M") {
            int nbPieces = stoi(userInput("Nombres de pieces : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));

            bool piscine = userInput("Piscine ? (Taper oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 1, "bool") == "oui";
            bool garage = userInput("Garage ? (Taper oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 1, "bool") == "oui";
            bool jardin = userInput("Jardin ? (Taper oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 1, "bool") == "oui";

            Maison maison = Maison(idBien, prix, adresse, idVendeur, surface, nbPieces, garage, jardin, piscine);
            biens[idBien] = maisons[idBien] = maison;
        }

        else if (typeBien == "T") {
            bool constructible = userInput("Constructible ? (Taper oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 1, "bool") == "oui";

            Terrain terrain = Terrain(idBien, prix, adresse, idVendeur, surface, constructible);
            biens[idBien] = terrains[idBien] = terrain;
        }

        else if (typeBien == "L") {
            bool stockage = userInput("Stockage ? (Taper oui/non) : ", "Erreur : vous devez rentrer oui ou non.", 1, "bool") == "oui";
            float vitrine = stof(userInput("Surface vitrine : ", "Erreur : vous devez rentrer un nombre.", 1, "float"));

            LocalPro localpro = LocalPro(idBien, prix, adresse, idVendeur, surface, vitrine, stockage);
            biens[idBien] = locaux[idBien] = localpro;
        }
    }
}

void Agence::supprimerBien(int id) {
    std::map<int, Bien> ::iterator itBien = biens.find(id);
    std::map<int, Appartement> ::iterator itAppart = apparts.find(id);
    std::map<int, Maison> ::iterator itMaison = maisons.find(id);
    std::map<int, Terrain> ::iterator itTerrain = terrains.find(id);
    std::map<int, LocalPro> ::iterator itLocaux = locaux.find(id);

    if (itBien != biens.end()) {
        biens.erase(id);

        if (itAppart != apparts.end()) apparts.erase(id);
        else if (itMaison != maisons.end()) maisons.erase(id);
        else if (itTerrain != terrains.end()) terrains.erase(id);
        else if (itLocaux != locaux.end()) locaux.erase(id);

        remove("/files/biens.txt");
        std::ofstream bFile("files/biens.txt", std::ios::out | std::ios::app);

        std::string type;
        itAppart = apparts.begin();
        itMaison = maisons.begin();
        itTerrain = terrains.begin();
        itLocaux = locaux.begin();

        if (bFile) {
            for (itBien = biens.begin(); itBien != biens.end(); itBien++) {
                type = itBien->second.getType();
                id = itBien->first;

                bFile << type << std::endl;
                bFile << id << std::endl;
                bFile << itBien->second.getPrix() << std::endl;
                bFile << itBien->second.getAdresse() << std::endl;
                bFile << itBien->second.getVendeur() << std::endl;
                bFile << itBien->second.getSurface() << std::endl;

                if (type == "t") {
                    itTerrain = terrains.find(id);

                    bFile << itTerrain->second.isConstructible() << std::endl;
                }
                else if (type == "l") {
                    itLocaux = locaux.find(id);

                    bFile << itLocaux->second.getVitrine() << std::endl;
                    bFile << itLocaux->second.hasStockage() << std::endl;
                }
                else if (type == "m") {
                    itMaison = maisons.find(id);

                    bFile << itMaison->second.getNbPieces() << std::endl;
                    bFile << itMaison->second.hasGarage() << std::endl;
                    bFile << itMaison->second.hasJardin() << std::endl;
                    bFile << itMaison->second.hasPiscine() << std::endl;
                }
                else if (type == "a") {
                    itAppart = apparts.find(id);

                    bFile << itAppart->second.getNbPieces() << std::endl;
                    bFile << itAppart->second.getEtage() << std::endl;
                    bFile << itAppart->second.getTotalApparts() << std::endl;
                    bFile << itAppart->second.hasGarage() << std::endl;
                    bFile << itAppart->second.hasCave() << std::endl;
                    bFile << itAppart->second.hasBalcon() << std::endl;
                }
            }
            bFile.close();
        }
        else std::cout << "Erreur : Ouverture impossible de biens.txt" << std::endl;

        std::cout << "--- Bien supprimé avec succès ! ---" << std::endl;
        return;
    }

    std::cout << "--- Bien introuvable. ---" << std::endl;
}

void Agence::listeBiens() {

    std::string typeBien;
    std::vector<std::string> types = {"A", "M", "T", "L", "B"};

    std::cout << "Choisissez, parmi la liste ci-dessous, le type de bien que vous souhaitez afficher :" << std::endl;
    std::cout << "Liste de tous les biens, tapez B" << std::endl;
    std::cout << "Liste des appartements, tapez A" << std::endl;
    std::cout << "Liste des maisons, tapez M" << std::endl;
    std::cout << "Liste des terrains, tapez T" << std::endl;
    std::cout << "Liste des locaux professionnels, tapez L" << std::endl;

    typeBien = userInput("Saisissez la lettre correspondane : ", "Erreur : vous devez rentrer A, M, T, L ou B.", 1);
    while (typeBien.size() != 1 || std::find(types.begin(), types.end(), typeBien) == types.end()) {
        std::cout << "Erreur : vous devez rentrer A, M, T, L ou B." << std::endl;
        typeBien = userInput("Saisissez la lettre correspondane : ", "Erreur : vous devez rentrer A, M, T, L ou B.", 1);
    }

    if (typeBien == "A") {
        std::map<int, Appartement> ::iterator it;
        for (it = apparts.begin(); it != apparts.end(); it++) it->second.Affiche();
    }

    else if (typeBien == "M") {
        std::map<int, Maison> ::iterator it;
        for (it = maisons.begin(); it != maisons.end(); it++) it->second.Affiche();
    }

    else if (typeBien == "T") {
        std::map<int, Terrain> ::iterator it;
        for (it = terrains.begin(); it != terrains.end(); it++) it->second.Affiche();
    }

    else if (typeBien == "L") {
        std::map<int, LocalPro> ::iterator it;
        for (it = locaux.begin(); it != locaux.end(); it++) it->second.Affiche();
    }

    else if (typeBien == "B") {
        std::map<int, Bien> ::iterator it;
        for (it = biens.begin(); it != biens.end(); it++) it->second.Affiche();
    }

    else {
        std::cout << "Une erreur est survenue, veuillez réessayer." << std::endl;
    }
}

void Agence::listeClients() {
    std::string typeClient;
    std::vector<std::string> types = {"A", "V", "ALL"};

    std::cout << "Choisissez, parmi la liste ci-dessous, le type de clients que vous souhaitez afficher :" << std::endl;
    std::cout << "Liste de tous les clients, tapez ALL" << std::endl;
    std::cout << "Liste des acheteurs, tapez A" << std::endl;
    std::cout << "Liste des vendeurs, tapez V" << std::endl;

    typeClient = userInput("Saisissez la lettre correspondante : ", "Erreur : Vous devez saisir A, V, ALL.", 1);
    while (typeClient.size() != 1 && std::find(types.begin(), types.end(), typeClient) == types.end()) {
        std::cerr << "Erreur : Vous devez saisir A, V, ALL." << std::endl;
        typeClient = userInput("Saisissez la lettre correspondante : ", "Erreur : Vous devez saisir A, V, ALL.", 1);
    }

    if (typeClient == "A") {
        std::map<int, Acheteur> ::iterator it;
        for (it = acheteurs.begin(); it != acheteurs.end(); it++) it->second.Affiche(0);
    }

    else if (typeClient == "V") {
        std::map<int, Vendeur> ::iterator it;
        for (it = vendeurs.begin(); it != vendeurs.end(); it++) it->second.Affiche(0);
    }

    else if (typeClient == "ALL") {
        std::map<int, Client> ::iterator it;
        for (it = clients.begin(); it != clients.end(); it++) it->second.Affiche();
    }

    else {
        std::cout << "Une erreur est survenue, veuillez réessayer." << std::endl;
    }
}

void Agence::rechercherClient() {
    std::string parametre;

    std::cout << "Vous souhaitez filtrer par : " << std::endl;
    std::cout << "  - Identifiant client : tapez I" << std::endl;
    std::cout << "  - Nom du client : entrez le nom" << std::endl;

    parametre = userInput("Entrez votre choix : ", "Erreur : vous devez rentrer I ou un nom.", 1);
    while (parametre != "I" && parametre.size() < 2) {
        std::cout << "Erreur : vous devez rentrer I ou un nom." << std::endl;
        parametre = userInput("Entrez votre choix : ", "Erreur : vous devez rentrer I ou un nom.", 1);
    }

    if (parametre == "I") {
        parametre = userInput("Identifiant client : ", "Erreur : vous devez rentrer un nombre.", 1, "int");
        std::map<int, Client> ::iterator it = clients.find(stoi(parametre));
        if (it != clients.end()) it->second.Affiche();
        else std::cout << "Aucun résultat !" << std::endl;
        return;
    }

    else {
        std::map<int, Client> ::iterator it;
        int count = 0;
        for (it = clients.begin(); it != clients.end(); it++) {
            if (parametre == it->second.getNom()) {
                it->second.Affiche();
                count++;
            }
        }

        if (count == 0) std::cout << "Aucun résultat !" << std::endl;
        return;
    }
}

void Agence::rechercherBien() {
    std::string parametre;

    std::cout << "Vous souhaitez filtrer par : " << std::endl;
    std::cout << "  - Surface : tapez S" << std::endl;
    std::cout << "  - Prix : tapez P" << std::endl;

    parametre = userInput("Entrez votre choix : ", "Erreur : vous devez rentrer S ou P.", 1);
    while (parametre != "P" && parametre != "S") {
        std::cout << "Erreur : vous devez rentrer S ou P." << std::endl;
        parametre = userInput("Entrez votre choix : ", "Erreur : vous devez rentrer S ou P.", 1);
    }

    if (parametre == "S") {
        std::cout << "Nous vous proposerons des surfaces allant jusqu'à +/- 20% de la surface recherchée" << std::endl;
        parametre = userInput("Surface : ", "Erreur : vous devez rentrer un nombre.", 1, "float");

        std::map<int, Bien> ::iterator it;
        float parametreSurface = stof(parametre);
        float parametreSurfaceMin = parametreSurface - 0.2*parametreSurface;
        float parametreSurfaceMax = parametreSurface + 0.2*parametreSurface;
        int count = 0;

        for (it = biens.begin(); it != biens.end(); it++) {
            if (parametreSurfaceMin <= it->second.getSurface() && parametreSurfaceMax >= it->second.getSurface()) {
                it->second.Affiche();
                count++;
            }
        }

        if (count == 0) std::cout << "Aucun résultat !" << std::endl;
        return;
    }

    else if (parametre == "P") {
        std::cout << "Nous vous proposerons des prix allant jusqu'à +/- 20% du prix recherché" << std::endl;
        parametre = userInput("Prix : ", "Erreur : vous devez rentrer un nombre.", 1, "int");

        std::map<int, Bien> ::iterator it;
        float parametrePrix = stof(parametre);
        float parametrePrixMin = parametrePrix - 0.2*parametrePrix;
        float parametrePrixMax = parametrePrix + 0.2*parametrePrix;
        int count = 0;

        for (it = biens.begin(); it != biens.end(); it++) {
            if (parametrePrixMin <= it->second.getPrix() && parametrePrixMax >= it->second.getPrix()) {
                it->second.Affiche();
                count++;
            }
        }

        if (count == 0) std::cout << "Aucun résultat !" << std::endl;
        return;
    }
    
    else std::cout << "Une erreur est survenue, veuillez réessayer." << std::endl;
}

void Agence::ajouterVisite() {
    int idClient = stoi(userInput("Identifiant du client acheteur : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
    std::map<int, Acheteur> ::iterator itClient = acheteurs.find(idClient);

    if (itClient == acheteurs.end()) {
        std::cout << "Le client n'existe pas, voulez-vous le créer ? /!\\ Nécessaire pour la saisie d'une visite /!\\" << std::endl;
        if (userInput("Saisissez votre choix (tapez oui/non) : ", "Erreur : vous devez saisir oui ou non.", 1, "bool") == "non") {
            std::cout << "Le client n'existe pas et l'utilisateur n'a pas voulu le créer. Retour au menu principal." << std::endl;
            return;
        }

        AjoutClient("nouveau", "A");

        std::map<int, Acheteur> ::iterator it;
        for (it = acheteurs.begin(); it != acheteurs.end(); it++) idClient = it->first;
    }

    int idBien = stoi(userInput("Identifiant du bien : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
    std::map<int, Bien> ::iterator itBien = biens.find(idBien);

    if (itBien == biens.end()) {
        std::cout << "Le bien n'existe pas, voulez-vous le créer ? /!\\ Nécessaire pour la saisie d'une visite /!\\" << std::endl;
        if (userInput("Saisissez votre choix (tapez oui/non) : ", "Erreur : vous devez saisir oui ou non.", 1, "bool") == "non") {
            std::cout << "Le bien n'existe pas et l'utilisateur n'a pas voulu le créer. Retour au menu principal." << std::endl;
            return;
        }

        AjoutBien("nouveau");

        std::map<int, Bien> ::iterator it;
        for (it = biens.begin(); it != biens.end(); it++) idBien = it->first;
    }

    bool proposition = userInput("Proposition d'achat ? (Taper oui/non) : ", "Erreur : vous devez saisir oui ou non", 1, "bool") == "oui";
    int prix = proposition ? stoi(userInput("Montant de la proposition : ", "Erreur : vous devez rentrer un nombre.", 1, "int")) : -1;

    itClient->second.AjoutVisite(idBien, proposition, prix);
}

void Agence::realiserVente() {
    std::cout << "Munissez-vous de l'identifiant du client acheteur, ainsi que l'identifiant du bien." << std::endl;

    int idBien, idClient;
    std::map<int, Bien> ::iterator itBien = biens.end();
    std::map<int, Acheteur> ::iterator itClient = acheteurs.end();

    while (itBien == biens.end()) {
        idBien = stoi(userInput("Saisissez l'identifiant du bien : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
        itBien = biens.find(idBien);
        if (itBien == biens.end()) std::cout << "Ce bien n'existe pas." << std::endl;
    }

    while (itClient == acheteurs.end()) {
        idClient = stoi(userInput("Saisissez l'identifiant du client : ", "Erreur : vous devez rentrer un nombre.", 1, "int"));
        itClient = acheteurs.find(idClient);
        if (itClient == acheteurs.end()) std::cout << "Cet acheteur n'existe pas." << std::endl;
    }

    if (itClient->second.isVisited(idBien)) {
        std::map<int, Vendeur> ::iterator itVendeur = vendeurs.find(itBien->second.getVendeur());
        if (itVendeur != vendeurs.end()) {
            std::map<int, Bien> ::iterator itBienVendeur = itVendeur->second.getBiens().find(idBien);
            if (itBienVendeur != itVendeur->second.getBiens().end()) {
                itVendeur->second.getBiens().erase(idBien);
                supprimerBien(idBien);
                itClient->second.supprimerVisite(idBien);
                std::cout << "--- La vente a été réalisée avec succès ! ---" << std::endl;
                return;
            }
            else std::cout << "--- Ce bien n'est pas en vente par ce vendeur. ---" << std::endl;
        }
        else std::cout << "--- Vendeur introuvable. ---" << std::endl;
    }
    else std::cout << "--- Aucune visite ne correspond à ce client et à ce bien. Retour au menu principal. ---" << std::endl;

}

int Agence::getLastIdBien() {
    std::map<int, Bien> ::iterator it = biens.end();
    return it->first;
}

int Agence::getLastIdClient() {
    std::map<int, Client> ::iterator it = clients.end();
    return it->first;
}

std::map<int, Client> Agence::findClient(std::string nom, bool vendeur) {
    std::map<int, Client> ::iterator it;
    std::map<int, Client> listeClientsTrouves;

    for (it = clients.begin(); it != clients.end(); it++) {
        if (vendeur) {
            if (it->second.isVendeur() && it->second.getNom() == nom) listeClientsTrouves[it->first] = it->second;
        }

        else {
            if (it->second.getNom() == nom) listeClientsTrouves[it->first] = it->second;
        }
    }

    return listeClientsTrouves;
}