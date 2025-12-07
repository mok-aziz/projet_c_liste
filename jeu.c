#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void initialiserJeu(Jeu *jeu) {
    jeu->nbTours=10;
    jeu->toursEffectues=0;
    jeu->mode=1;
    jeu->nbJoueurs=0;
    jeu->nbCombinaisons=0;
    jeu->nbScores=0;
}
void tirerBonbons(Distributeur *d, Bonbon tirage[3], int *nb_tires) {
    *nb_tires=0;

    if(d->nb_bonbons_actuel<3) {
        printf("Pas assez de bonbons dans le distributeur!\n");
        return;
    }
    for(int i=0;i<3;i++) {
        int index=rand()%d->nb_bonbons_actuel;
        tirage[i]=d->reserve[index];

        for(int j=index;j<d->nb_bonbons_actuel-1;j++) {
            d->reserve[j]=d->reserve[j+1];
        }
        d->nb_bonbons_actuel--;
        (*nb_tires)++;
    }
}
int verifierCombinaison(Bonbon tirage[3], Combinaison comb) {
    int trouve[3]={0,0,0};
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(trouve[j]==0 && strcmp(tirage[j].couleur,comb.couleurs[i])==0) {
                trouve[j]=1;
                break;
            }
        }
    }
    return (trouve[0]&&trouve[1]&&trouve[2]);
}

int calculerPoints(Bonbon tirage[3], Combinaison combinaisons[], int nbCombinaisons) {
    int points = 0;

    for (int i = 0; i < nbCombinaisons; i++) {
        if (verifierCombinaison(tirage, combinaisons[i])) {
            printf("*** COMBINAISON GAGNANTE ***: ");
            afficherCombinaison(combinaisons[i]);
            return combinaisons[i].points;
        }
    }

    for (int i = 0; i < 3; i++) {
        points += tirage[i].valeur;
    }

    return points;
}

void lancerPartie(Jeu *jeu) {
    if (jeu->nbJoueurs == 0) {
        printf("Aucun joueur! Veuillez d'abord creer un joueur.\n");
        return;
    }

    printf("\n=== DEBUT DE LA PARTIE ===\n");
    printf("Joueur: %s\n", jeu->joueurs[jeu->nbJoueurs-1].pseudo);
    printf("Nombre de tours: %d\n", jeu->nbTours);
    int scorePartie = 0;
    for (int tour = 1; tour <= jeu->nbTours; tour++) {
        printf("\n--- Tour %d/%d ---\n", tour, jeu->nbTours);


        if (jeu->nbCombinaisons == 0) {
            printf("Aucune combinaison definie! Impossible de jouer.\n");
            return;
        }
        // on va choisir le premier dist(pour simplification)
        int dist_index = 0;
        if (jeu->distributeurs[dist_index].nb_bonbons_actuel < 3) {
            printf("Le distributeur n'a plus assez de bonbons!\n");
            break;
        }
        printf("Tirage des bonbons...\n");
        Bonbon tirage[3];
        int nb_tires = 0;
        tirerBonbons(&jeu->distributeurs[dist_index], tirage, &nb_tires);

        if (nb_tires == 3) {
            printf("vous avez tire:\n");
            for (int i = 0; i < 3; i++) {
                printf("  %d. ", i + 1);
                afficheBonbon(tirage[i]);
            }

            int points = calculerPoints(tirage, jeu->combinaisons, jeu->nbCombinaisons);
            printf("Points de ce tour: %d\n", points);
            scorePartie += points;
            printf("Score total: %d\n", scorePartie);
        } else {
            printf("Erreur lors du tirage!\n");
            break;
        }

        jeu->toursEffectues++;
    }

    printf("\n=== FIN DE LA PARTIE ===\n");
    printf("Score final: %d points\n", scorePartie);


    jeu->joueurs[jeu->nbJoueurs - 1].scoreTotal = scorePartie;


    if (jeu->nbScores < 50) {
        strcpy(jeu->scores[jeu->nbScores].pseudo, jeu->joueurs[jeu->nbJoueurs - 1].pseudo);
        jeu->scores[jeu->nbScores].valeur = scorePartie;


        jeu->nbScores++;
    }
}

void afficherScore(Jeu jeu) {
    printf("\n=== SCORES ACTUELS ===\n");
    if (jeu.nbJoueurs==0) {
        printf("Aucun joueur!\n");
        return;
    }
    for (int i=0;i<jeu.nbJoueurs;i++) {
        aficherJoueur(jeu.joueurs[i]);
    }

}

void afficherResultats(Jeu jeu) {
    printf("=== RESULTATS ===\n");
    afficherScore(jeu);
    if (jeu.nbScores > 0) {
        printf("\n=== HISTORIQUE DES SCORES ===\n");
        afficherscore(jeu.scores, jeu.nbScores);
    }
}

void sauvegarderScores(Jeu jeu) {
    printf("Scores sauvegardes )!\n");//pas terminee
}

void chargerScores(Jeu *jeu) {
    printf("Scores charges !\n");//pas terminee
}
