#ifndef COMBINAISON_H_INCLUDED
#define COMBINAISON_H_INCLUDED

struct Combinaison {
    int id;
    char couleurs[3][20];
    int points;
};
typedef struct Combinaison Combinaison;


struct NoeudCombinaison {
    Combinaison combinaison;
    struct NoeudCombinaison *suivant;
};
typedef struct NoeudCombinaison NoeudCombinaison;


typedef struct {
    NoeudCombinaison *tete;
    int taille;
} ListeCombinaisons;

Combinaison creeCombinaison(ListeCombinaisons *liste);
void afficherCombinaison(Combinaison c);
void modifierCombinaison(Combinaison *c);
void supprimerCombinaison(ListeCombinaisons *liste, int id);

#endif // COMBINAISON_H_INCLUDED
