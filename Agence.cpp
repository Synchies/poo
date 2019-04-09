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

            while(std::getline(vFile, contenu)) {
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

        // boucle pour la saisie du nom du client (permet de sécuriser et de redonner sa chance à l'utilisateur)
        for (;;) {
            std::cout << "Saisissez le nom du client : ";
            std::getline(std::cin, nomClient);

            if (nomClient.size() < 2)
                std::cerr << "Erreur : Vous devez saisir un nom de client valide." << std::endl;

            else if (!errorCin())
                break;
        }

        // boucle pour la saisie de l'adresse du client (permet de sécuriser et de redonner sa chance à l'utilisateur)
        for (;;) {
            std::cout << "Saisissez l'adresse du client : ";
            std::getline(std::cin, adresseClient);

            if (adresseClient.size() < 5)
                std::cerr << "Erreur : Vous devez saisir une adresse de client valide." << std::endl;

            else if (!errorCin())
                break;
        }

        if (typeClient == "undefined") {
            // boucle pour la saisie du type de client (permet de sécuriser et de redonner sa chance à l'utilisateur)
            for (;;) {
                std::cout << "Acheteur/Vendeur ? (Tapez A ou V) : ";
                std::getline(std::cin, typeClient);

                if (typeClient != "A" && typeClient != "V" || typeClient.size() > 1)
                    std::cerr << "Erreur : Vous devez saisir A ou V." << std::endl;

                else if (!errorCin())
                    break;
            }
        }

        std::map<int, Client> ::iterator it = clients.end();

        if (typeClient == "A") {
            Acheteur c = Acheteur((it->first)+1, nomClient, adresseClient, "A");
            clients[c.getId()] = acheteurs[c.getId()] = c;
        }

        else {
            Vendeur c = Vendeur((it->first)+1, nomClient, adresseClient, "V");
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
        std::string temp;
        std::string typeBien;
        std::vector<std::string> types = {"A", "M", "T", "L"};
        int prix, vendeurId;
        std::string adresse, vendeur;
        float surface;

        std::cout << "Choisissez, parmi la liste ci-dessous, le type de bien que vous souhaitez ajouter :" << std::endl;
        std::cout << "- Appartement : tapez A" << std::endl;
        std::cout << "- Maison : tapez M" << std::endl;
        std::cout << "- Terrain : tapez T" << std::endl;
        std::cout << "- Local Professionnel : tapez L" << std::endl;

        for (;;) {
            std::cout << "Saisissez la lettre correspondante : ";
            std::getline(std::cin, typeBien);

            if (typeBien.size() != 1 || std::find(types.begin(), types.end(), typeBien) == types.end())
                std::cerr << "Erreur : Vous devez saisir A, M, T ou L." << std::endl;

            else if (!errorCin())
                break;
        }

        for (;;) {
            clearBuffer();

            std::cout << "Nom du vendeur : ";
            std::getline(std::cin, vendeur);

            if (vendeur.size() < 2)
                    std::cerr << "Erreur : Vous devez saisir un nom valide." << std::endl;

            else if (!errorCin()) {
                std::map<int, Client> ::iterator it;
                std::map<int, Client> clientsTrouves = findClient(vendeur);
                if (clientsTrouves.size() == 1) {
                    it = clientsTrouves.begin();
                    vendeurId = it->first;
                    break;
                }

                else if (clientsTrouves.size() > 1) {
                    std::cout << "Plusieurs clients portant ce nom ont été trouvés. Choisissez le client correspondant parmi la liste ci-dessous, en entrant son identifiant. Si aucun vendeur ne correspond, tapez \"new\" pour créer un profil :" << std::endl;

                    for (it = clientsTrouves.begin(); it != clientsTrouves.end(); it++) it->second.Affiche(); // on veut appeler Vendeur::Affiche, à revoir
                    std::cout << "Saisie (identifiant, ou \"new\") : ";
                    std::getline(std::cin, temp);

                   if (temp == "new") {
                        // permet de tester si le dernier id est toujours le même (ou non) après le passage de la fonction AjoutClient().
                        int idLastClient = getLastIdClient();
                        AjoutClient("nouveau", "V");

                        if (idLastClient == getLastIdClient()) {
                            std::cout << "Il semble que la création du vendeur ait échouée. Création du bien annulée." << std::endl;
                            return;
                        }

                        vendeurId = idLastClient;
                        break;
                   }

                   if (!errorCin())
                        if (temp.find_first_not_of("0123456789.,") != std::string::npos) {
                            std::cout << "Erreur : vous devez rentrer un nombre." << std::endl;
                            clearBuffer();
                        }

                        else {
                            int n = temp.length();
                            char vendeurIdTemp[n+1];
                            strcpy(vendeurIdTemp, temp.c_str());

                            if (temp[0]) {
                                vendeurId = std::stoi(vendeurIdTemp, nullptr, 10);

                                if (!errorCin()) break;
                            }

                            else
                                std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
                        }
                }

                else {
                    std::cout << "Ce client n'existe pas. Voulez-vous le créer ? /!\\ nécessaire pour une création de bien /!\\" << std::endl;
                    for (;;) {
                        clearBuffer();

                        std::cout << "Réponse (oui/non) : ";
                        std::getline(std::cin, temp);

                        if (temp.find_first_not_of("ouinon") != std::string::npos) {
                            std::cout << "Erreur : vous devez rentrer oui ou non." << std::endl;
                            clearBuffer();
                        }

                        else {
                            if (temp != "oui" && temp != "non")
                                std::cerr << "Erreur : vous devez rentrer oui ou non." << std::endl;

                            else if (!errorCin()) {
                                if (temp == "oui") {
                                    AjoutClient("nouveau", "V");
                                    vendeur = getLastIdClient();
                                    break;
                                }

                                else {
                                    std::cout << "Ajout de bien annulé. Le client n'existe pas, et l'utilisateur n'a pas voulu le créer." << std::endl;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (;;) {
            std::cout << "Surface : ";
            getline(std::cin, temp);

            if (temp.find_first_not_of("0123456789.,") != std::string::npos) {
                std::cout << "Erreur : vous devez rentrer un nombre." << std::endl;
                clearBuffer();
            }

            else {
                int n = temp.length();
                char temp2[n+1];
                strcpy(temp2, temp.c_str());

                if (temp[0]) {
                    surface = strtof(temp2, NULL);

                    if (surface < 5)
                        std::cout << "Erreur : La surface est inférieure au minimum acceptable." << std::endl;

                    else if (!errorCin())
                        break;
                }

                else
                    std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
            }
        }

        clearBuffer();

        for (;;) {

            std::cout << "Prix : ";
            getline(std::cin, temp);

            if (temp.find_first_not_of("0123456789") != std::string::npos) {
                std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
                clearBuffer();
            }

            else {
                int n = temp.length();
                char temp2[n+1];
                strcpy(temp2, temp.c_str());

                if (temp[0]) {
                    prix = std::stoi(temp2, nullptr, 10);

                    if (prix < 1000)
                        std::cout << "Erreur : Le prix est inférieur au minimum acceptable." << std::endl;

                    else if (!errorCin())
                        break;
                }

                else
                    std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
            }
        }

        for (;;) {
            clearBuffer();

            std::cout << "Adresse du bien : ";
            std::getline(std::cin, adresse);

            if (adresse.size() < 5)
                std::cerr << "Erreur : Vous devez saisir une adresse valide." << std::endl;

            else if (!errorCin())
                break;
        }

        std::cout << "--- Détails du bien ---" << std::endl;

        if (typeBien == "A") {
            int nbPieces, etage, totalApparts;
            bool garage, cave, balcon;

            std::map<std::string, int> pea;
            std::map<std::string, int> ::iterator itpea;
            pea["Nombre de pièces dans l'appartement"] = 0;
            pea["Etage de l'appartement"] = 0;
            pea["Nombre total d'appartements dans l'immeuble"] = 0;

            for (itpea = pea.begin(); itpea != pea.end(); itpea++) {
                for (;;) {
                    clearBuffer();

                    std::cout << itpea->first << " : ";
                    getline(std::cin, temp);

                    if (temp.find_first_not_of("0123456789") != std::string::npos) {
                        std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
                        clearBuffer();
                    }

                    else {
                        int n = temp.length();
                        char temp2[n+1];
                        strcpy(temp2, temp.c_str());

                        if (temp[0]) {
                            pea[itpea->first] = std::stoi(temp2, NULL);

                            if (!errorCin())
                                break;
                        }

                        else
                            std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
                    }
                }
            }

            nbPieces = pea["Nombre de pièces dans l'appartement"];
            etage = pea["Etage de l'appartement"];
            totalApparts = pea["Nombre total d'appartements dans l'immeuble"];

            std::map<std::string, bool> gcb;
            std::map<std::string, bool> ::iterator itgcb;
            gcb["Balcon"] = false;
            gcb["Garage"] = false;
            gcb["Cave"] = false;

            for (itgcb = gcb.begin(); itgcb != gcb.end(); itgcb++) {
                for (;;) {
                    clearBuffer();

                    std::cout << itgcb->first << " ? (Taper oui ou non) : ";
                    getline(std::cin, temp);

                    if (temp.find_first_not_of("ouinon") != std::string::npos) {
                        std::cout << "Erreur : vous devez rentrer oui ou non." << std::endl;
                        clearBuffer();
                    }

                    else {
                        if (temp != "oui" && temp != "non")
                            std::cerr << "Erreur : vous devez rentrer oui ou non." << std::endl;

                        else if (!errorCin()) {
                            gcb[itgcb->first] = temp == "oui";
                            break;
                        }
                    }
                }
            }

            balcon = gcb["Balcon"];
            cave = gcb["Cave"];
            garage = gcb["Garage"];

            Appartement appart = Appartement(idBien, prix, adresse, vendeurId, surface, nbPieces, etage, totalApparts, garage, cave, balcon);
            biens[idBien] = apparts[idBien] = appart;
        }

        else if (typeBien == "M") {
            int nbPieces;
            bool garage, piscine, jardin;

            clearBuffer();

            std::cout << "Nombre de pièces dans la maison" << " : ";
            getline(std::cin, temp);

            if (temp.find_first_not_of("0123456789") != std::string::npos) {
                std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
                clearBuffer();
            }

            else {
                int n = temp.length();
                char temp2[n+1];
                strcpy(temp2, temp.c_str());

                if (temp[0] && (!errorCin())) nbPieces = std::stoi(temp2, NULL);
                else std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
            }

            std::map<std::string, bool> pgj;
            std::map<std::string, bool> ::iterator itpgj;
            pgj["Piscine"] = false;
            pgj["Garage"] = false;
            pgj["Jardin"] = false;

            for (itpgj = pgj.begin(); itpgj != pgj.end(); itpgj++) {
                for (;;) {
                    clearBuffer();

                    std::cout << itpgj->first << " ? (Taper oui ou non) : ";
                    getline(std::cin, temp);

                    if (temp.find_first_not_of("ouinon") != std::string::npos) {
                        std::cout << "Erreur : vous devez rentrer oui ou non." << std::endl;
                        clearBuffer();
                    }

                    else {
                        if (temp != "oui" && temp != "non")
                            std::cerr << "Erreur : vous devez rentrer oui ou non." << std::endl;

                        else if (!errorCin()) {
                            pgj[itpgj->first] = temp == "oui";
                            break;
                        }
                    }
                }
            }

            piscine = pgj["Piscine"];
            garage = pgj["Garage"];
            jardin = pgj["Jardin"];

            Maison maison = Maison(idBien, prix, adresse, vendeurId, surface, nbPieces, garage, jardin, piscine);
            biens[idBien] = maisons[idBien] = maison;
        }

        else if (typeBien == "T") {
            bool constructible = false;

            clearBuffer();

            std::cout << "Constructible ? (Taper oui ou non) : ";
            getline(std::cin, temp);

            if (temp.find_first_not_of("ouinon") != std::string::npos) {
                std::cout << "Erreur : vous devez rentrer oui ou non." << std::endl;
                clearBuffer();
            }

            else {
                if (temp != "oui" && temp != "non")
                    std::cerr << "Erreur : vous devez rentrer oui ou non." << std::endl;

                else if (!errorCin()) constructible = temp == "oui";
            }

            Terrain terrain = Terrain(idBien, prix, adresse, vendeurId, surface, constructible);
            biens[idBien] = terrains[idBien] = terrain;
        }

        else if (typeBien == "L") {
            bool stockage;
            float vitrine;

            std::map<std::string, bool> sv;
            std::map<std::string, bool> ::iterator itsv;
            sv["Stockage"] = false;
            sv["Vitrine"] = 0;

            for (itsv = sv.begin(); itsv != sv.end(); itsv++) {
                for (;;) {
                    clearBuffer();

                    std::cout << itsv->first << " ? (Taper oui ou non) : ";
                    getline(std::cin, temp);

                    if (temp.find_first_not_of("ouinon") != std::string::npos) {
                        std::cout << "Erreur : vous devez rentrer oui ou non." << std::endl;
                        clearBuffer();
                    }

                    else {
                        if (temp != "oui" && temp != "non")
                            std::cerr << "Erreur : vous devez rentrer oui ou non." << std::endl;

                        else if (!errorCin()) {
                            sv[itsv->first] = temp == "oui";
                            break;
                        }
                    }
                }
            }

            stockage = sv["Stockage"];
            vitrine = sv["Vitrine"];

            LocalPro localpro = LocalPro(idBien, prix, adresse, vendeurId, surface, vitrine, stockage);
            biens[idBien] = locaux[idBien] = localpro;
        }
    }
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

    for (;;) {
        std::cout << "Saisissez la lettre correspondante : ";
        std::getline(std::cin, typeBien);

        if (typeBien.size() != 1 || std::find(types.begin(), types.end(), typeBien) == types.end())
            std::cerr << "Erreur : Vous devez saisir A, M, T, L ou B." << std::endl;

        else if (!errorCin())
            break;
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

    for (;;) {
        std::cout << "Saisissez la lettre correspondante : ";
        std::getline(std::cin, typeClient);

        if (typeClient.size() != 1 || std::find(types.begin(), types.end(), typeClient) == types.end())
            std::cerr << "Erreur : Vous devez saisir A, V, ALL." << std::endl;

        else if (!errorCin())
            break;
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
    std::string temp;

    std::cout << "Vous souhaitez filtrer par : " << std::endl;
    std::cout << "  - Identifiant client : tapez I" << std::endl;
    std::cout << "  - Nom du client : entrez le nom" << std::endl;

    for (;;) {
        clearBuffer();

        std::cout << "Entrez votre choix : ";
        std::getline(std::cin, temp);

        if (!errorCin() && (temp == "I" || temp.size() >= 2)) break;
        else std::cout << "Erreur : vous devez rentrer I ou un nom." << std::endl;
    }

    if (temp == "I") {
        for (;;) {
            clearBuffer();

            std::cout << "Identifiant client : ";
            std::getline(std::cin, temp);

            if (temp.find_first_not_of("0123456789") != std::string::npos) {
                std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
                clearBuffer();
            }

            else {
                if (!errorCin()) {
                    if (temp.length() != 0) break;
                    else std::cout << "Erreur : vous devez rentrer un nombre." << std::endl;
                }

                else std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
            }
        }

        std::map<int, Client> ::iterator it = clients.find(stoi(temp));
        if (it != clients.end()) it->second.Affiche();
        else std::cout << "Aucun résultat !" << std::endl;
        return;
    }

    else {
        std::map<int, Client> ::iterator it;
        int count = 0;
        for (it = clients.begin(); it != clients.end(); it++) {
            if (temp == it->second.getNom()) {
                it->second.Affiche();
                count++;
            }
        }

        if (count == 0) {
            std::cout << "Aucun résultat !" << std::endl;
        }

        return;
    }
}

void Agence::rechercherBien() {
    std::string temp;

    std::cout << "Vous souhaitez filtrer par : " << std::endl;
    std::cout << "  - Surface : tapez S" << std::endl;
    std::cout << "  - Prix : tapez P" << std::endl;

    for (;;) {
        clearBuffer();

        std::cout << "Entrez votre choix : ";
        std::getline(std::cin, temp);

        if (!errorCin() && (temp == "P" || temp == "S")) break;
        else std::cout << "Erreur : vous devez rentrer S ou P." << std::endl;
    }

    if (temp == "S") {
        std::cout << "Nous vous proposerons des surfaces allant jusqu'à +/- 20% de la surface recherchée" << std::endl;
        for (;;) {
            clearBuffer();

            std::cout << "Surface : ";
            std::getline(std::cin, temp);

            if (temp.find_first_not_of("0123456789.") != std::string::npos) {
                std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
                clearBuffer();
            }

            else {
                if (!errorCin()) {
                    if (temp.length() != 0 && temp != ".") break;
                    else std::cout << "Erreur : vous devez rentrer un nombre." << std::endl;
                }

                else std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
            }
        }

        std::map<int, Bien> ::iterator it;
        float tempSurface = stof(temp);
        float tempSurfaceMin = tempSurface - 0.2*tempSurface;
        float tempSurfaceMax = tempSurface + 0.2*tempSurface;
        int count = 0;
        for (it = biens.begin(); it != biens.end(); it++) {
            if (tempSurfaceMin <= it->second.getSurface() && tempSurfaceMax >= it->second.getSurface()) {
                it->second.Affiche();
                count++;
            }
        }
        if (count == 0) std::cout << "Aucun résultat !" << std::endl;
        return;
    }

    else if (temp == "P") {
        std::cout << "Nous vous proposerons des prix allant jusqu'à +/- 20% du prix recherché" << std::endl;
        for (;;) {
            clearBuffer();

            std::cout << "Prix : ";
            std::getline(std::cin, temp);

            if (temp.find_first_not_of("0123456789") != std::string::npos) {
                std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
                clearBuffer();
            }

            else {
                if (!errorCin()) {
                    if (temp.length() != 0) break;
                    else std::cout << "Erreur : vous devez rentrer un nombre." << std::endl;
                }

                else std::cout << "Erreur : vous devez rentrer un nombre positif." << std::endl;
            }
        }

        std::map<int, Bien> ::iterator it;
        float tempPrix = stof(temp);
        float tempPrixMin = tempPrix - 0.2*tempPrix;
        float tempPrixMax = tempPrix + 0.2*tempPrix;
        int count = 0;
        for (it = biens.begin(); it != biens.end(); it++) {
            if (tempPrixMin <= it->second.getPrix() && tempPrixMax >= it->second.getPrix()) {
                it->second.Affiche();
                count++;
            }
        }
        if (count == 0) std::cout << "Aucun résultat !" << std::endl;
        return;
    }
    
    else std::cout << "Une erreur est survenue, veuillez réessayer." << std::endl;
}

int Agence::getLastIdBien() {
    std::map<int, Bien> ::iterator it = biens.end();
    return it->first;
}

int Agence::getLastIdClient() {
    std::map<int, Client> ::iterator it = clients.end();
    return it->first;
}

std::map<int, Client> Agence::findClient(std::string nom) {
    std::map<int, Client> ::iterator it;
    std::map<int, Client> listeClientsTrouves;

    for (it = clients.begin(); it != clients.end(); it++) {
        if (it->second.isVendeur() && it->second.getNom() == nom) listeClientsTrouves[it->first] = it->second;
    }

    return listeClientsTrouves;
}