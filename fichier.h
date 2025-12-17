#ifndef FICHIER_H
#define FICHIER_H

#include "jeu.h"
#define FICHIER_JOUEURS "joueurs.txt"
#define FICHIER_DISTRIBUTEURS "distributeurs.txt"
#define FICHIER_COMBINAISONS "combinaisons.txt"
#define FICHIER_SCORES "scores.txt"
#define FICHIER_BONBONS "bonbons.txt"

void sauvegarderJoueurs(ListeJoueurs *liste);
void sauvegarderDistributeurs(ListeDistributeurs *liste);
void sauvegarderCombinaisons(ListeCombinaisons *liste);
void sauvegarderScoresFichier(ListeScores *liste);
void sauvegarderBonbons(ListeBonbons *liste);
void sauvegarderTout(Jeu *jeu, ListeBonbons *liste_bonbons);

void chargerJoueurs(ListeJoueurs *liste, int *nbJoueurs);
void chargerDistributeurs(ListeDistributeurs *liste);
void chargerCombinaisons(ListeCombinaisons *liste, int *nbCombinaisons);
void chargerScoresFichier(ListeScores *liste, int *nbScores);
void chargerBonbons(ListeBonbons *liste);
void chargerTout(Jeu *jeu, ListeBonbons *liste_bonbons);

#endif
