#ifndef DISTRIBUTEUR_H_INCLUDED
#define DISTRIBUTEUR_H_INCLUDED
#include "bonbon.h"

struct Distributeur {
    int id;
    ListeBonbons reserve;
    int nb_bonbons_actuel;
};
typedef struct Distributeur Distributeur;


struct NoeudDistributeur {
    Distributeur distributeur;
    struct NoeudDistributeur *suivant;
};
typedef struct NoeudDistributeur NoeudDistributeur;


typedef struct {
    NoeudDistributeur *tete;
    int taille;
} ListeDistributeurs;

void creerDistributeur(ListeDistributeurs *liste);
void ajouterBonbon(Distributeur *d);
void retirerBonbon(Distributeur *d);
void afficherDistributeur(Distributeur d);
void supprimerDistributeur(ListeDistributeurs *liste);
Distributeur* rechercherDistributeur(ListeDistributeurs *liste, int id);

#endif // DISTRIBUTEUR_H_INCLUDED

