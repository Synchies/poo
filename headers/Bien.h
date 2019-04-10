#ifndef Bien_h
#define Bien_h

#include <iostream>
#include <string>
#include <fstream>

class Bien {
    protected:
        int prix, id, vendeur;
        std::string adresse, type;
        float surface;
    public:
        Bien();
        Bien(int, int, std::string, int, float);

        // accesseurs
        int getId();
        float getPrix();
        std::string getAdresse();
        int getVendeur();
        float getSurface();
        void Affiche() const;
        std::string getType();
};

#endif