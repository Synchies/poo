#ifndef Client_h
#define Client_h

#include <iostream>
#include <map>
#include <vector>
#include <fstream>

class Client {
    protected:
        int id;
        std::string nom, adresse;
    public:
        Client();
        Client(int, std::string, std::string);
        Client(const Client&);

        std::string getNom();
        virtual void Affiche() const;
};

#endif