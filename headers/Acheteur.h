#ifndef Acheteur_h
#define Acheteur_h

#include "Client.h"

class Acheteur: public Client {
    protected:
        std::map<int, std::pair<bool, int> > visites; // (id du bien visité, proposition ?, prix de la proposition (-1 sinon))
    public:
        Acheteur();
        Acheteur(std::string, std::string);
        void AjoutVisite(int, bool, int);
        virtual void Affiche() const;
};

#endif