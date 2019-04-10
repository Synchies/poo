#ifndef Vendeur_h
#define Vendeur_h

#include "Client.h"

// classe fille de client
class Vendeur: public Client {
    protected:
        std::map<int, Bien> biens;
    public:
        Vendeur();
        Vendeur(int, std::string, std::string, std::string, bool = 1);
        void AjoutBien(int, Bien);

        virtual void Affiche(bool = 1) const;

        // accesseurs
        std::map<int, Bien> getBiens();
};

#endif