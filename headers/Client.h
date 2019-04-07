#ifndef Client_h
#define Client_h

#include <iostream>
#include <map>
#include <vector>
#include <fstream>

class Client {
    protected:
        std::string nom;
        std::string adresse;
    public:
        Client();
        Client(std::string, std::string);
        Client(const Client&);

        std::string getNom();
        virtual void Affiche() const;
};

#endif