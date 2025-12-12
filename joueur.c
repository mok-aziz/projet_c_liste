#include "joueur.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void creeJoueur(ListeJoueurs *liste)
{
    NoeudJoueur *nouveau=(NoeudJoueur*)malloc(sizeof(NoeudJoueur));
    printf("Pseudo: ");
    scanf("%s",nouveau->joueur.pseudo);
    nouveau->joueur.scoreTotal=0;
    nouveau->suivant=liste->tete;
    liste->tete=nouveau;
    liste->taille++;
    printf("Joueur cree avec succes!\n");
}

void aficherJoueur(Joueur j) {
    printf("Pseudo: %s\nScore = %d\n",j.pseudo,j.scoreTotal);
}

void modifierJoueur(Joueur *j)
{
    printf("Nouveau pseudo: ");
    scanf("%s",j->pseudo);
    printf("Nouveau score Total: ");
    scanf("%d",&j->scoreTotal);
    printf("Joueur modifie avec succes!\n");
}

void supprimerJoueur(ListeJoueurs *liste, char pseudo[])
{
    NoeudJoueur *courant=liste->tete;
    NoeudJoueur *precedent=NULL;
    while (courant!=NULL)
    {
        if (strcmp(courant->joueur.pseudo,pseudo)==0)
            {
            if (precedent==NULL) {
                liste->tete=courant->suivant;
            }
            else
            {
                precedent->suivant=courant->suivant;
            }
            free(courant);
            liste->taille--;
            printf("Joueur supprime avec succes!\n");
            return;
        }
        precedent=courant;
        courant=courant->suivant;
    }

    printf("Joueur non trouve!\n");
}
