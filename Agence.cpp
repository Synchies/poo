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
void Agence::AjoutClient(std::string action) {

    if (action == "lire") {
        std::ifstream aFile("files/acheteurs.txt", std::ios::in);
        std::ifstream vFile("files/vendeurs.txt", std::ios::in);
        std::ifstream bFile("files/biens.txt", std::ios::in);

        // contenu de l'entrée utilisateur.
        std::string contenu;
        // permet de compter les lignes parcourues.
        int curseur;

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
                        Acheteur acheteur = Acheteur(id, nom, adresse);
                        clients[id] = acheteur;
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
                        Vendeur vendeur = Vendeur(id, nom, adresse);
                        clients[id] = vendeur;
                        break;
                }

                curseur++;
            }
        }
    }

    else {
        // informations du client
        std::string typeClient;
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

        // boucle pour la saisie du type de client (permet de sécuriser et de redonner sa chance à l'utilisateur)
        for (;;) {
            std::cout << "Acheteur/Vendeur ? (Tapez A ou V) : ";
            std::getline(std::cin, typeClient);

            if (typeClient != "A" && typeClient != "V" || typeClient.size() > 1)
                std::cerr << "Erreur : Vous devez saisir A ou V." << std::endl;

            else if (!errorCin())
                break;
        }

        std::map<int, Clients> ::iterator it = clients.end();

        if (typeClient == "A")
            Acheteur *c = new Acheteur(it->first, nomClient, adresseClient);
        else
            Vendeur *c = new Vendeur(it->first, nomClient, adresseClient);
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
void Agence::AjoutBien(string action, int idBien = 0) {
    if (action == "lire") {
        if (bFile) {
            // curseur pour savoir à quel paramètre on se situe, selon le type de bien recontré
            curseur = 0;
            std::string typeBien, adresse, vendeur;
            int id, nbPieces, etage, totalApparts;
            float prix, surface;
            bool garage, cave, balcon, vitrine, stockage, jardin, piscine, constructible;
            // modulo correspond au nombre de paramètres demandés par la classe.
            int modulo;

            while(std::getline(bFile, contenu)) {
                if (contenu == "a") modulo = 11;
                else if (contenu == "m") modulo = 10;
                else if (contenu == "t") modulo = 7;
                else if (contenu == "l") modulo = 8;
                else {
                    switch (modulo) {
                        case 11:
                            switch(curseur%11) {
                                case 1: id = stoi(contenu);
                                break;
                                case 2: prix = stof(contenu);
                                break;
                                case 3: adresse = contenu;
                                break;
                                case 4: vendeur = contenu;
                                break;
                                case 5: surface = stof(contenu);
                                break;
                                case 6: nbPieces = stoi(contenu);
                                break;
                                case 7: etage = contenu == "1";
                                break;
                                case 8: garage = contenu == "1";
                                break;
                                case 9: cave = contenu == "1";
                                break;
                                case 10:
                                    balcon = contenu == "1";
                                    Appartement appart = Appartement(id, prix, adresse, vendeur, surface, nbPieces, etage, garage, cave, balcon);
                                    biens[id] = appart;
                                    apparts[id] = appart;
                                    break;
                            }
                            break;
                        case 10:
                            switch(curseur%10) {
                                case 1: id = stoi(contenu);
                                break;
                                case 2: prix = stof(contenu);
                                break;
                                case 3: adresse = contenu;
                                break;
                                case 4: vendeur = contenu;
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
                                    Maison maison = Maison(id, prix, adresse, vendeur, surface, nbPieces, garage, jardin, piscine);
                                    biens[id] = maison;
                                    maisons[id] = maison;
                                    break;
                            }
                            break;
                        case 7:
                            switch(curseur%7) {
                                case 1: id = stoi(contenu);
                                break;
                                case 2: prix = stof(contenu);
                                break;
                                case 3: adresse = contenu;
                                break;
                                case 4: vendeur = contenu;
                                break;
                                case 5: surface = stof(contenu);
                                break;
                                case 6:
                                    constructible = contenu == "1";
                                    Terrain terrain = Terrain(id, prix, adresse, vendeur, surface, constructible);
                                    biens[id] = terrain;
                                    terrains[id] = terrain;
                                    break;
                            }
                            break;
                        case 8:
                            switch(curseur%8) {
                                case 1: id = stoi(contenu);
                                break;
                                case 2: prix = stof(contenu);
                                break;
                                case 3: adresse = contenu;
                                break;
                                case 4: vendeur = contenu;
                                break;
                                case 5: surface = stof(contenu);
                                break;
                                case 6: stockage = contenu == "1";
                                break;
                                case 7:
                                    vitrine = contenu == "1";
                                    LocalPro local = LocalPro(id, prix, adresse, vendeur, surface, stockage, vitrine);
                                    biens[id] = local;
                                    locaux[id] = local;
                                    break;
                            }
                            break;
                    }
                }
            }
        }
    }

    else {
        std::string temp;
        std::string typeBien;
        std::vector<std::string> types = {"A", "M", "T", "L"};
        int prix;
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

        for (;;) {
            clearBuffer();

            std::cout << "Nom du vendeur : ";
            std::getline(std::cin, vendeur);

            if (adresse.size() < 2)
                    std::cerr << "Erreur : Vous devez saisir une adresse valide." << std::endl;

            else if (!errorCin())
                break;
        }

        std::cout << "           --- Détails du bien ---" << std::endl;

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
                            gcb[itpgj->first] = temp == "oui";
                            break;
                        }
                    }
                }
            }

            balcon = gcb["Balcon"];
            cave = gcb["Cave"];
            garage = gcb["Garage"];

            Appartement* appart = new Appartement(idBien, prix, adresse, vendeur, surface, nbPieces, etage, totalApparts, garage, cave, balcon);
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

            Maison* maison = new Maison(idBien, prix, adresse, vendeur, surface, nbPieces, garage, jardin, piscine);
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

            Terrain* terrain = new Terrain(idBien, prix, adresse, vendeur, surface, constructible);
        }

        else if (typeBien == "L") {
            bool stockage, vitrine;

            std::map<std::string, bool> sv;
            std::map<std::string, bool> ::iterator itsv;
            sv["Stockage"] = false;
            sv["Vitrine"] = false;

            for (itsv = sv.begin(); itsv != pgj.end(); itsv++) {
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

            LocalPro* localpro = new LocalPro(idBien, prix, adresse, vendeur, surface, stockage, vitrine);
        }
    }
}

int Agence::getLastIdBien() {
    std::map<int, Bien> ::iterator it = biens.end();
    std::cout << it->first << std::endl;
    return it->first;
}