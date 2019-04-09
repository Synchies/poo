#ifndef Acheteur_h
#define Acheteur_h

#include "Client.h"

// classe fille de Client
class Acheteur: public Client {
    protected:
        std::map<int, std::pair<bool, int> > visites; // (id du bien visité, proposition ?, prix de la proposition (-1 sinon))
    public:
        // constructeurs
        Acheteur();
        Acheteur(int, std::string, std::string, std::string, bool = 1);

        // méthodes
        void AjoutVisite(int, bool, int);
        virtual void Affiche(bool = 1) const;
};

#endif