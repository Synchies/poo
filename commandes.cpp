/*#include "headers/commandes.h"

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

// crée un nouveau client à partir de la saisie utilisateur
void newClient() {

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
    
    if (typeClient == "A")
        Acheteur *c = new Acheteur(nomClient, adresseClient);
    else
        Vendeur *c = new Vendeur(nomClient, adresseClient);

}

// crée un nouveau bien à partir de la saisie utilisateur
void newBien() {
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
                        if (temp == "oui")
                            gcb[itgcb->first] = 1;
                        else if (temp == "non")
                            gcb[itgcb->first] = 0;
                        break;
                    }
                }
            }
        }

        balcon = gcb["Balcon"];
        cave = gcb["Cave"];
        garage = gcb["Garage"];
        
        Appartement* appart = new Appartement(, prix, adresse, vendeur, surface, nbPieces, etage, totalApparts, garage, cave, balcon);
    }

    else if (typeBien == "M") {

    }

    else if (typeBien == "T") {

    }

    else if (typeBien == "L") {

    }
}*/