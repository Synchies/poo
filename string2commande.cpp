#include "headers/string2commande.h"

commandes string2commande(std::string commande) {

    // stockage de toutes les commandes en string, + équivalent en enum
    static const std::map<std::string, commandes> stringCommandes {
        { "@help", help },
        { "@quit", quit },
        { "@nouveauClient", nouveauClient },
        { "@nouveauBien", nouveauBien },
        { "@listeBiens", listeBiens },
        { "@listeClients", listeClients }
    };

    // recherche et envoi de la commande (enum) d'après sa correspondance (string)
    auto it = stringCommandes.find(commande);
    if (it != stringCommandes.end()) {
        return it->second;
    }

    // la commande n'est pas dans la liste, message d'erreur
    return invalide;
}