#ifndef Bien_h
#define Bien_h

#include <iostream>
#include <string>
#include <fstream>

class Bien {
    protected:
        int prix, id;
        std::string adresse, vendeur;
        float surface;
    public:
        Bien();
        Bien(int, int, std::string, std::string, float);
        int getId();
};

#endif