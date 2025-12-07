#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

struct Joueur {
    char pseudo[30];
    int scoreTotal;
};
typedef struct Joueur Joueur;


struct NoeudJoueur {
    Joueur joueur;
    struct NoeudJoueur *suivant;
};
typedef struct NoeudJoueur NoeudJoueur;


typedef struct {
    NoeudJoueur *tete;
    int taille;
} ListeJoueurs;

void creeJoueur(ListeJoueurs *liste);
void aficherJoueur(Joueur j);
void modifierJoueur(Joueur *j);
void supprimerJoueur(ListeJoueurs *liste, char pseudo[]);
#endif // JOUEUR_H_INCLUDED
