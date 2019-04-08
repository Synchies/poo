#ifndef Maison_h
#define Maison_h

#include "Bien.h"

class Maison: public Bien {
    protected:
        int nbPieces;
        bool garage, jardin, piscine;
    public:
        Maison();
        Maison(int, int, std::string, std::string, float, int, bool, bool, bool, bool = 1);
};

#endif