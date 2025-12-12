#include "bonbon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void afficherListeBonbons(ListeBonbons *liste)
{
    if (liste->tete==NULL)
    {
        printf("Liste vide!\n");
        return;
    }

    NoeudBonbon *courant=liste->tete;
    int i = 1;
    while (courant!=NULL)
    {
        printf("%d. ",i++);
        afficheBonbon(courant->bonbon);
        courant=courant->suivant;
    }
}

void creeBonbon(ListeBonbons *liste)
{
    NoeudBonbon *nouveau=(NoeudBonbon*)malloc(sizeof(NoeudBonbon));
    printf("Donner la COULEUR du bonbon: ");
    scanf("%s",nouveau->bonbon.couleur);
    printf("Donner la VALEUR du bonbon: ");
    scanf("%d",&nouveau->bonbon.valeur);
    nouveau->suivant=liste->tete;
    liste->tete=nouveau;
    liste->taille++;

    printf("Bonbon ajoute avec succes!\n");
}

void afficheBonbon(Bonbon b)
{
    printf("Couleur:%s,Valeur:%d\n",b.couleur,b.valeur);
}

void modifierBonbon(Bonbon *b)
{
    printf("Nouvelle couleur: ");
    scanf("%s",b->couleur);//lehne famech & kodem b->couleur khaterha string deja
    printf("Nouvelle valeur: ");
    scanf("%d",&b->valeur);
    printf("Bonbon modifie avec succes!\n");
}

void supprimerBonbon(ListeBonbons *liste, char couleur[])
{
    NoeudBonbon *courant=liste->tete;
    NoeudBonbon *precedent=NULL;
    while (courant!=NULL)
    {
        if (strcmp(courant->bonbon.couleur,couleur)==0)
        {

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
            printf("Bonbon supprime avec succes!\n");
            return;
        }
        precedent=courant;
        courant=courant->suivant;
    }

    printf("Bonbon non trouve!\n");
}
