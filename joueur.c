#include "joueur.h"
#include <stdio.h>
#include <string.h>

void creeJoueur(Joueur tab_joueur[], int *nb) {
    Joueur j;
    printf("Pseudo: ");
    scanf("%s", j.pseudo);
    j.scoreTotal = 0;
    tab_joueur[*nb] = j;
    (*nb)++;
    printf("Joueur cree avec succes!\n");
}

void aficherJoueur(Joueur j) {
    printf("Pseudo: %s\nScore = %d\n", j.pseudo, j.scoreTotal);
}

void modifierJoueur(Joueur *j) {
    printf("Nouveau pseudo: ");
    scanf("%s", j->pseudo);
    printf("Nouveau score Total: ");
    scanf("%d", &j->scoreTotal);
    printf("Joueur modifie avec succes!\n");
}

void supprimerJoueur(Joueur tab[], int *nb, char pseudo[]) {
    int found = 0;
    for (int i=0;i<*nb;i++) {
        if (strcmp(tab[i].pseudo, pseudo) == 0) {
            for (int j = i; j < *nb - 1; j++) {
                tab[j] = tab[j + 1];
            }
            (*nb)--;
            found = 1;
            printf("Joueur supprime avec succes!\n");
            break;
        }
    }

    if (!found) {
        printf("Joueur non trouve!\n");
    }
}
