#ifndef Appartement_h
#define Appartement_h

#include "Bien.h"

class Appartement: public Bien {
    protected:
        int nbPieces, etage, totalApparts;
        bool garage, cave, balcon;
    public:
        Appartement();
        Appartement(int, int, std::string, std::string, float, int, int, int, bool, bool, bool);
};

#endif