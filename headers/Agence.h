#ifndef Agence_h
#define Agence_h

#include <iostream>
#include <string>
#include <map>
#include <vector>

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
        std::map<std::string, Client> clients;
        std::map<int, Appartement> apparts;
        std::map<int, Maison> maisons;
        std::map<int, Terrain> terrains;
        std::map<int, LocalPro> locaux;
    public:
        Agence();
        Agence(std::string);
        Agence(const Agence&);

        void AjoutClient(Client);
        void AjoutAppartement(Appartement);
        void AjoutMaison(Maison);
        void AjoutTerrain(Terrain);
        void AjoutLocal(LocalPro);
};

#endif