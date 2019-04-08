#ifndef LocalPro_h
#define LocalPro_h

#include "Bien.h"

class LocalPro : public Bien {
    protected:
        float vitrine;
        bool stockage;
    public:
        LocalPro();
        LocalPro(int, int, std::string, std::string, float, float, bool, bool = 1);

        // accesseurs
        float getVitrine();
        bool hasStockage();
};

#endif