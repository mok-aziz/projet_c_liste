#include "combinaison.h"
#include <stdio.h>
#include <stdlib.h>

Combinaison* rechercherCombinaison(ListeCombinaisons *liste,int id)
{
    NoeudCombinaison *courant=liste->tete;
    while (courant!=NULL)
    {
        if (courant->combinaison.id==id)
        {
            return &(courant->combinaison);
        }
        courant=courant->suivant;
    }
    return NULL;
}

Combinaison creeCombinaison(ListeCombinaisons *liste)
{

    NoeudCombinaison *nouveau=(NoeudCombinaison*)malloc(sizeof(NoeudCombinaison));

    printf("ID: ");
    scanf("%d",&nouveau->combinaison.id);
    for(int i=0;i<3;i++)
    {
        printf("Couleur %d: ",i + 1);
        scanf("%s", nouveau->combinaison.couleurs[i]);
    }
    printf("Points: ");
    scanf("%d",&nouveau->combinaison.points);
    nouveau->suivant=liste->tete;
    liste->tete=nouveau;
    liste->taille++;
    printf("Combinaison creee avec succes!\n");
    return nouveau->combinaison;
}

void afficherCombinaison(Combinaison c)
{
    printf("Combinaison %d: %s .... %s ... %s \nPoints: %d\n",
           c.id,c.couleurs[0],c.couleurs[1],c.couleurs[2],c.points);
}

void modifierCombinaison(Combinaison *c)
{
    printf("Modification de la combinaison %d\n", c->id);
    for(int i=0;i<3;i++)
    {
        printf("Nouvelle couleur %d: ",i + 1);
        scanf("%s",c->couleurs[i]);
    }
    printf("Nouveaux points: ");
    scanf("%d",&c->points);
}

void supprimerCombinaison(ListeCombinaisons *liste, int id)
{
    NoeudCombinaison *courant=liste->tete;
    NoeudCombinaison *precedent=NULL;

    while (courant!=NULL)
    {
        if (courant->combinaison.id==id)
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
            printf("Combinaison supprimee!\n");
            return;
        }
        precedent=courant;
        courant=courant->suivant;
    }

    printf("Combinaison non trouvee!\n");
}
