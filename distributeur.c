#include "distributeur.h"
#include "bonbon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Distributeur* rechercherDistributeur(ListeDistributeurs *liste, int id)
{
    NoeudDistributeur *courant=liste->tete;
    while (courant!=NULL)
    {
        if (courant->distributeur.id==id)
        {
            return &(courant->distributeur);
        }
        courant=courant->suivant;
    }
    return NULL;
}

void creerDistributeur(ListeDistributeurs *liste)
{

    NoeudDistributeur *nouveau = (NoeudDistributeur*)malloc(sizeof(NoeudDistributeur));
    printf("Saisir l'identifiant du distributeur: ");
    scanf("%d", &nouveau->distributeur.id);
    nouveau->distributeur.reserve.tete=NULL;
    nouveau->distributeur.reserve.taille=0;
    nouveau->distributeur.nb_bonbons_actuel=0;
    nouveau->suivant=liste->tete;
    liste->tete=nouveau;
    liste->taille++;

    printf("Distributeur cree avec succes!\n");
}

void ajouterBonbon(Distributeur *d)
{
    if(d->nb_bonbons_actuel>=100)
    {
        printf("Reserve pleine!\n");
        return;
    }
    NoeudBonbon *nouveau=(NoeudBonbon*)malloc(sizeof(NoeudBonbon));
    printf("Couleur du bonbon: ");
    scanf("%s",nouveau->bonbon.couleur);
    printf("Valeur du bonbon: ");
    scanf("%d",&nouveau->bonbon.valeur);
    nouveau->suivant=d->reserve.tete;
    d->reserve.tete=nouveau;
    d->reserve.taille++;
    d->nb_bonbons_actuel=d->reserve.taille;

    printf("Bonbon ajoutee au distributeur!\n");
}

void retirerBonbon(Distributeur *d)
{
    if(d->nb_bonbons_actuel==0)
    {
        printf("Distributeur vide!\n");
        return;
    }

    char couleur[30];
    printf("Couleur du bonbon a retirer: ");
    scanf("%s", couleur);

    NoeudBonbon *courant=d->reserve.tete;
    NoeudBonbon *precedent=NULL;

    while (courant!=NULL)
    {
        if (strcmp(courant->bonbon.couleur,couleur)==0)
        {

            if (precedent==NULL)
            {
                d->reserve.tete=courant->suivant;
            }
            else
            {
                precedent->suivant=courant->suivant;
            }
            free(courant);
            d->reserve.taille--;
            d->nb_bonbons_actuel=d->reserve.taille;
            printf("Bonbon retire!\n");
            return;
        }
        precedent=courant;
        courant=courant->suivant;
    }

    printf("Bonbon non trouve!\n");
}

void afficherDistributeur(Distributeur d)
{
    printf("\n--- Distributeur %d ---\n",d.id);
    printf("Bonbons actuels: %d\n",d.nb_bonbons_actuel);

    if(d.nb_bonbons_actuel>0)
    {
        printf("les bonbons:\n");
        NoeudBonbon *courant=d.reserve.tete;
        while (courant!=NULL)
        {
            printf("\n");
            afficheBonbon(courant->bonbon);
            courant=courant->suivant;
        }
    }
}

void supprimerDistributeur(ListeDistributeurs *liste)
{
    int id;
    printf(" du distributeur a supprimer: ");
    scanf("%d",&id);

    NoeudDistributeur *courant=liste->tete;
    NoeudDistributeur *precedent=NULL;
    while (courant!=NULL) {
        if (courant->distributeur.id==id)
            {
            // Effacer tous les bonbons du distributeur
            NoeudBonbon *bonbon=courant->distributeur.reserve.tete;
            while (bonbon!=NULL)
            {
                NoeudBonbon *auxBonbon=bonbon;
                bonbon=bonbon->suivant;
                free(auxBonbon);
            }

            // Supprimer le distributeur
            if (precedent==NULL)
            {
                liste->tete=courant->suivant;
            }
            else
            {
                precedent->suivant=courant->suivant;
            }
            free(courant);
            liste->taille--;
            printf("Distributeur supprime!\n");
            return;
        }
        precedent=courant;
        courant=courant->suivant;
    }

    printf("Distributeur non trouve!\n");
}
