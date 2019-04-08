#ifndef Vendeur_h
#define Vendeur_h

#include "Client.h"

// classe fille de client
class Vendeur: public Client {
    protected:
        std::vector<int> biens;
    public:
        Vendeur();
        Vendeur(int, std::string, std::string);
        void AjoutBien(int);
};

#endif