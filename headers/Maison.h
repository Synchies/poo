#ifndef Maison_h
#define Maison_h

#include "Bien.h"

class Maison: public Bien {
    protected:
        int nbPieces;
        bool garage, jardin, piscine;
    public:
        Maison();
        Maison(int, int, std::string, int, float, int, bool, bool, bool, bool = 1);

        // accesseurs
        int getNbPieces();
        bool hasGarage();
        bool hasJardin();
        bool hasPiscine();
        void Affiche();
};

#endif