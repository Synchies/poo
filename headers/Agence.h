#ifndef Agence_h
#define Agence_h

#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <limits>
#include <algorithm>

#include "Client.h"
#include "Acheteur.h"
#include "Vendeur.h"
#include "Bien.h"
#include "Appartement.h"
#include "Maison.h"
#include "Terrain.h"
#include "LocalPro.h"

class Agence {
    protected:
        std::string nom;
        std::map<int, Client> clients;
        std::map<int, Bien> biens; // répertoire de biens, sans les informations propres aux biens particuliers
        std::map<int, Appartement> apparts;
        std::map<int, Maison> maisons;
        std::map<int, Terrain> terrains;
        std::map<int, LocalPro> locaux;
    public:
        // constructeurs
        Agence();
        Agence(std::string);
        Agence(const Agence&);

        // méthodes
        void AjoutClient(std::string);
        void AjoutBien(std::string, int = 0);
        void AjoutAppartement(Appartement);
        void AjoutMaison(Maison);
        void AjoutTerrain(Terrain);
        void AjoutLocal(LocalPro);

        // accesseur
        int getLastIdBien();
        int getLastIdClient();
};

#endif