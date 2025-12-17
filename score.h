#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

struct Score {
    char pseudo[30];
    int valeur;
    char date[20];
};
typedef struct Score Score;


struct NoeudScore {
    Score score;
    struct NoeudScore *suivant;
};
typedef struct NoeudScore NoeudScore;


typedef struct {
    NoeudScore *tete;
    int taille;
} ListeScores;

void ajouterScore(ListeScores *liste);
void afficherscore(ListeScores *liste);
void trierScore(ListeScores *liste);
void supprimerScore(ListeScores *liste, char pseudo[]);
void trierScore(ListeScores *liste);
void trierScoreDecroissant(ListeScores *liste);
void trierScoreCroissant(ListeScores *liste);
void trierScoreChronologique(ListeScores *liste);
void trierScoreParJoueur(ListeScores *liste);
void afficherStatistiquesJoueur(ListeScores *liste);

#endif // SCORE_H_INCLUDED
