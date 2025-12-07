#include "distributeur.h"
#include "bonbon.h"
#include <stdio.h>
#include <string.h>

void creerDistributeur(Distributeur tab_dis[],int* nb_dis) {
    Distributeur d;
    printf("Saisir l'identifiant du distributeur: ");
    scanf("%d", &d.id);
    d.nb_bonbons_actuel=0;
    tab_dis[*nb_dis]=d;
    (*nb_dis)++;
    printf("Distributeur cree avec succes!\n");
}

void ajouterBonbon(Distributeur *d) {
    if(d->nb_bonbons_actuel>=100) {
        printf("Reserve pleine!\n");
        return;
    }

    Bonbon b;
    printf("Couleur du bonbon: ");
    scanf("%s",b.couleur);
    printf("Valeur du bonbon: ");
    scanf("%d",&b.valeur);

    d->reserve[d->nb_bonbons_actuel]=b;
    d->nb_bonbons_actuel++;
    printf("Bonbon ajoute au distributeur!\n");
}

void retirerBonbon(Distributeur *d) {
    if(d->nb_bonbons_actuel==0) {
        printf("Distributeur vide!\n");
        return;
    }

    char couleur[30];
    printf("Couleur du bonbon a retirer: ");
    scanf("%s",couleur);

    int index=-1;
    for (int i=0;i<d->nb_bonbons_actuel;i++) {
        if (strcmp(d->reserve[i].couleur, couleur)==0) {
            index=i;
            break;
        }
    }

    if (index==-1) {
        printf("Bonbon non trouve!\n");
        return;
    }

    for (int i=index;i<d->nb_bonbons_actuel-1;i++) {
        d->reserve[i]=d->reserve[i+1];
    }
    d->nb_bonbons_actuel--;
    printf("Bonbon retire!\n");
}

void afficherDistributeur(Distributeur d) {
    printf("\n--- Distributeur %d ---\n",d.id);
    printf("Bonbons actuels: %d\n",d.nb_bonbons_actuel);
    if(d.nb_bonbons_actuel>0) {
        printf("Contenu:\n");
        for(int i=0;i<d.nb_bonbons_actuel;i++) {
            printf("  ");
            afficheBonbon(d.reserve[i]);
        }
    }
}

void supprimerDistributeur(Distributeur tab_dis[],int* nb_dis) {
    int id;
    printf("ID du distributeur a supprimer: ");
    scanf("%d", &id);

    int index=-1;
    for (int i=0;i<*nb_dis; i++) {
        if (tab_dis[i].id==id) {
            index=i;
            break;
        }
    }

    if (index==-1) {
        printf("Distributeur non trouve!\n");
        return;
    }

    for (int i=index;i<*nb_dis-1; i++) {
        tab_dis[i]=tab_dis[i+1];
    }
    (*nb_dis)--;
    printf("Distributeur supprime!\n");
}
