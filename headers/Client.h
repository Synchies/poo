#ifndef Client_h
#define Client_h

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "Bien.h"

class Client {
    protected:
        int id;
        std::string nom, adresse, typeClient;
    public:
        Client();
        Client(int, std::string, std::string, std::string);
        Client(const Client&);

        // accesseurs
        std::string getNom();
        virtual void Affiche() const;
        bool isVendeur();
        int getId();
        std::string getAdresse();
};

#endif