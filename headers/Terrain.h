#ifndef Terrain_h
#define Terrain_h

#include "Bien.h"

class Terrain: public Bien {
    protected:
        bool constructible;
    public:
        Terrain();
        Terrain(int, int, std::string, std::string, float, bool);
};

#endif