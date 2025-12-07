#include "combinaison.h"
#include <stdio.h>

Combinaison creeCombinaison(int *nb) {
    Combinaison c;
    printf("ID: ");
    scanf("%d", &c.id);
    for (int i=0;i<3;i++) {
        printf("Couleur %d: ", i + 1);
        scanf("%s", c.couleurs[i]);
    }
    printf("Points: ");
    scanf("%d", &c.points);
    (*nb)++;
    printf("Combinaison creee avec succes!\n");
    return c;
}

void afficherCombinaison(Combinaison c) {
    printf("Combinaison %d: %s - %s - %s \nPoints: %d\n",
           c.id, c.couleurs[0], c.couleurs[1], c.couleurs[2], c.points);
}

void modifierCombinaison(Combinaison *c) {
    printf("Modification de la combinaison %d\n", c->id);
    for (int i=0;i<3;i++) {
        printf("Nouvelle couleur %d: ", i + 1);
        scanf("%s", c->couleurs[i]);
    }
    printf("Nouveaux points: ");
    scanf("%d", &c->points);
}

void supprimerCombinaison(Combinaison tab[],int *nb,int id) {
    int found=0;
    for (int i=0;i<*nb;i++) {
        if (tab[i].id==id) {
            // Remplacer par le dernier élément
            tab[i]=tab[*nb-1];
            (*nb)--;
            found=1;
            printf("Combinaison supprimee!\n");
            break;
        }
    }

    if (!found) {
        printf("Combinaison non trouvee!\n");
    }
}
