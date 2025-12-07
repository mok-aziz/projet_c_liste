#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "joueur.h"
#include "distributeur.h"
#include "combinaison.h"
#include "score.h"
#include "bonbon.h"

struct Jeu {
    int nbTours;
    int toursEffectues;
    int mode;
    ListeJoueurs joueurs;
    int nbJoueurs;
    ListeDistributeurs distributeurs;
    ListeCombinaisons combinaisons;
    int nbCombinaisons;
    ListeScores scores;
    int nbScores;
};
typedef struct Jeu Jeu;
void initialiserJeu(Jeu *jeu);
void lancerPartie(Jeu *jeu);
void afficherScore(Jeu jeu);
void afficherResultats(Jeu jeu);
void sauvegarderScores(Jeu jeu);
void chargerScores(Jeu *jeu);

#endif // JEU_H_INCLUDED
