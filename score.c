#include "score.h"
#include <stdio.h>
#include <string.h>

void ajouterScore(Score tab_score[], int *taille_tab_score) {
    Score sr;
    printf("Pseudo: ");
    scanf("%s", sr.pseudo);
    printf("Valeur: ");
    scanf("%d", &sr.valeur);
    printf("Date YYYY-MM-DD: ");
    scanf("%s", sr.date);

    tab_score[*taille_tab_score] = sr;
    (*taille_tab_score)++;
    printf("Score ajoute!\n");
}

void afficherscore(Score tabscore[], int taille_tab_score) {
    for (int i=0;i<taille_tab_score;i++) {
        printf("%d. %s - %d points - %s\n",i+1, tabscore[i].pseudo, tabscore[i].valeur, tabscore[i].date);
    }

}

void trierScore(Score tabscore[], int taille_tab_score) {
    for (int i=0;i<taille_tab_score-1;i++) {
        for (int j=0;j< taille_tab_score-i-1;j++) {
            if (tabscore[j].valeur<tabscore[j+1].valeur) {
                Score aux=tabscore[j];
                tabscore[j]=tabscore[j+1];
                tabscore[j+1]=aux;
            }
        }
    }
    printf("Scores tries par ordre decroissant!\n");
}

void supprimerScore(Score tabscore[], int *taille_tab_score, char pseudo[]) {
    int index = -1;
    for (int i=0;i<*taille_tab_score;i++) {
        if (strcmp(tabscore[i].pseudo, pseudo) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Score non trouve!\n");
        return;
    }

    for (int i=index;i<*taille_tab_score-1;i++) {
        tabscore[i] = tabscore[i + 1];
    }
    (*taille_tab_score)--;
    printf("Score supprime!\n");
}
