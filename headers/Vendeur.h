#ifndef Vendeur_h
#define Vendeur_h

#include "Client.h"

class Vendeur: public Client {
    protected:
        std::vector<int> biens;
    public:
        Vendeur();
        Vendeur(std::string, std::string);
        void AjoutBien(int);
};

#endif