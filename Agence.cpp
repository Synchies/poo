#include "headers/Agence.h"

Agence::Agence() {}

Agence::Agence(std::string _nom) :
    nom(_nom) {}

Agence::Agence(const Agence& a) :
    nom(a.nom) {}

void Agence::AjoutClient(Client C) {
    clients[C.getNom()] = C;
}

void Agence::AjoutAppartement(Appartement A) {
    apparts[A.getId()] = A;
}

void Agence::AjoutMaison(Maison M) {
    maisons[M.getId()] = M;
}

void Agence::AjoutTerrain(Terrain T) {
    terrains[T.getId()] = T;
}

void Agence::AjoutLocal(LocalPro L) {
    locaux[L.getId()] = L;
}