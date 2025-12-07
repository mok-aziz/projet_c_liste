#include "bonbon.h"
#include <stdio.h>
#include <string.h>

void creeBonbon(Bonbon tab_bon[],int* taille_tab_bon) {
    Bonbon b;
    printf("Donner la COULEUR du bonbon: ");
    scanf("%s",b.couleur);
    printf("Donner la VALEUR du bonbon: ");
    scanf("%d",&b.valeur);

    tab_bon[*taille_tab_bon]=b;
    (*taille_tab_bon)++;
    printf("Bonbon ajoute avec succes!\n");
}

void afficheBonbon(Bonbon b) {
    printf("Couleur: %s, Valeur: %d\n", b.couleur, b.valeur);
}

void modifierBonbon(Bonbon *b) {
    printf("Nouvelle couleur: ");
    scanf("%s",b->couleur);
    printf("Nouvelle valeur: ");
    scanf("%d",&b->valeur);
    printf("Bonbon modifie avec succes!\n");
}

void supprimerBonbon(Bonbon tab_bonbon[],int *taille_tab_bon,char couleur[]) {
    int index=-1;
    for (int i=0;i<*taille_tab_bon;i++) {
        if (strcmp(tab_bonbon[i].couleur,couleur)==0) {
            index=i;
            break;
        }
    }

    if (index==-1) {
        printf("Bonbon non trouve!\n");
        return;
    }

    for (int i=index;i<*taille_tab_bon-1;i++) {
        tab_bonbon[i]=tab_bonbon[i+1];
    }
    (*taille_tab_bon)--;
    printf("Bonbon supprime avec succes!\n");
}
