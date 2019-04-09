#ifndef string2commande_h
#define string2commande_h

#include <iostream>
#include <string>
#include <map>

// enum répertoriant toutes les commandes
enum commandes {
    invalide,
    help,
    quit,
    nouveauClient,
    nouveauBien,
    listeBiens,
    listeClients,
    rechercheClient,
    rechercheBien
};

// conversion d'une commande entrée par l'utilisateur (string) en commande pour le programme (enum)
commandes string2commande(std::string commande);

#endif