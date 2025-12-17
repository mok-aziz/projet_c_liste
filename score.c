#include "score.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ajouterScore(ListeScores *liste) {

    NoeudScore *nouveau=(NoeudScore*)malloc(sizeof(NoeudScore));
    if (nouveau==NULL) {
        printf("Erreur d'allocation memoire!\n");
        return;
    }
    printf("Pseudo: ");
    scanf("%s", nouveau->score.pseudo);
    printf("Valeur: ");
    scanf("%d", &nouveau->score.valeur);
    printf("Date YYYY-MM-DD: ");
    scanf("%s", nouveau->score.date);
    nouveau->suivant=liste->tete;
    liste->tete=nouveau;
    liste->taille++;
    printf("Score ajoute!\n");
}

void afficherscore(ListeScores *liste) {
    if (liste->tete==NULL) {
        printf("Aucun score!\n");
        return;
    }

    NoeudScore *courant=liste->tete;
    int i=1;

    printf("\n%-5s %-20s %-10s %-12s\n", "No.", "Pseudo", "Score", "Date");
    printf("---------------------------------------------------\n");


    while (courant!=NULL) {
        printf("%-5d %-20s %-10d %-12s\n", i++,
               courant->score.pseudo,
               courant->score.valeur,
               courant->score.date);
        courant=courant->suivant;
    }
    printf("---------------------------------------------------\n");
}

void trierScoreDecroissant(ListeScores *liste) {
    if (liste->tete==NULL || liste->tete->suivant == NULL) {
        return;
    }

    NoeudScore *courant=liste->tete;

    while (courant!=NULL) {
        NoeudScore *max =courant;
        NoeudScore *ptr =courant->suivant;
        while (ptr!=NULL) {
            if (ptr->score.valeur>max->score.valeur) {
                max=ptr;
            }
            ptr=ptr->suivant;
        }
        if (max!=courant) {
            Score temp =courant->score;
            courant->score=max->score;
            max->score=temp;
        }
        courant=courant->suivant;
    }
    printf("\nScores triés par ordre décroissant!\n");
}

void trierScoreCroissant(ListeScores *liste) {
    if (liste->tete==NULL || liste->tete->suivant==NULL) {
        return;
    }

    NoeudScore *courant=liste->tete;

    while (courant!=NULL) {
        NoeudScore *min =courant;
        NoeudScore *ptr =courant->suivant;

        while (ptr!=NULL) {
            if (ptr->score.valeur < min->score.valeur) {
                min = ptr;
            }
            ptr=ptr->suivant;
        }
        if (min!=courant) {
            Score temp=courant->score;
            courant->score=min->score;
            min->score=temp;
        }

        courant=courant->suivant;
    }

    printf("\nScores tries par ordre croissant!\n");
}

void trierScoreChronologique(ListeScores *liste) {
    if (liste->tete==NULL || liste->tete->suivant==NULL) {
        return;
    }

    NoeudScore *courant=liste->tete;

    while (courant != NULL) {
        NoeudScore *min=courant;
        NoeudScore *ptr=courant->suivant;
        while (ptr!=NULL) {
            if (strcmp(ptr->score.date,min->score.date)<0) {
                min=ptr;
            }
            ptr=ptr->suivant;
        }

        if (min!=courant) {
            Score temp=courant->score;
            courant->score=min->score;
            min->score=temp;
        }

        courant=courant->suivant;
    }

    printf("\nScores tries par ordre chronologique !\n");
}

void trierScoreParJoueur(ListeScores *liste) {
    if (liste->tete==NULL || liste->tete->suivant == NULL) {
        return;
    }

    NoeudScore *courant=liste->tete;

    while (courant!=NULL) {
        NoeudScore *min=courant;
        NoeudScore *ptr=courant->suivant;

        while (ptr != NULL) {
            if (strcmp(ptr->score.pseudo, min->score.pseudo) < 0) {
                min=ptr;
            }
            ptr=ptr->suivant;
        }

        if (min!=courant) {
            Score temp=courant->score;
            courant->score=min->score;
            min->score=temp;
        }

        courant=courant->suivant;
    }
    printf("\nScores tries par joueur !\n");
}

void afficherStatistiquesJoueur(ListeScores *liste) {
    if (liste->tete == NULL) {
        printf("Aucun score!\n");
        return;
    }

    char pseudo[50];
    printf("\nEntrez le pseudo du joueur: ");
    scanf("%s", pseudo);

    int nb_parties = 0;
    int total_points = 0;
    int meilleur_score = 0;

    NoeudScore *courant = liste->tete;

    while (courant != NULL) {
        if (strcmp(courant->score.pseudo, pseudo) == 0) {
            nb_parties++;
            total_points += courant->score.valeur;

            if (courant->score.valeur > meilleur_score) {
                meilleur_score = courant->score.valeur;
            }

        }
        courant = courant->suivant;
    }

    if (nb_parties == 0) {
        printf("\nAucune partie trouvee pour le joueur '%s'\n", pseudo);
        return;
    }

    printf("\n========================================\n");
    printf("  STATISTIQUES DE %s\n", pseudo);
    printf("========================================\n");
    printf("Nombre de parties jouees: %d\n", nb_parties);
    printf("Score total cumule: %d points\n", total_points);
    printf("Moyenne par partie: %.2f points\n", (float)total_points / nb_parties);
    printf("Meilleur score: %d points\n", meilleur_score);
    printf("========================================\n");
}

void trierScore(ListeScores *liste) {
    if (liste->tete == NULL || liste->tete->suivant == NULL) {
        printf("Pas assez de scores pour trier!\n");
        return;
    }

    int choix;

    printf("\n==== OPTIONS DE TRI ====\n");
    printf("1. Decroissant (meilleurs scores en premier)\n");
    printf("2. Croissant (moins bons scores en premier)\n");
    printf("3. Chronologique (du plus ancien au plus recent)\n");
    printf("4. Par joueur (ordre alphabetique)\n");
    printf("5. Statistiques d'un joueur\n");
    printf("========================\n");
    printf("Votre choix: ");
    scanf("%d", &choix);

    switch(choix) {
        case 1:
            trierScoreDecroissant(liste);
            afficherscore(liste);
            break;
        case 2:
            trierScoreCroissant(liste);
            afficherscore(liste);
            break;
        case 3:
            trierScoreChronologique(liste);
            afficherscore(liste);
            break;
        case 4:
            trierScoreParJoueur(liste);
            afficherscore(liste);
            break;
        case 5:
            afficherStatistiquesJoueur(liste);
            break;
        default:
            printf("Choix invalide!\n");
    }
}

void supprimerScore(ListeScores *liste, char pseudo[]) {
    NoeudScore *courant = liste->tete;
    NoeudScore *precedent = NULL;

    while (courant != NULL) {
        if (strcmp(courant->score.pseudo, pseudo) == 0) {
            if (precedent == NULL) {
                liste->tete = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }
            free(courant);
            liste->taille--;
            printf("Score supprime!\n");
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    }

    printf("Score non trouve!\n");
}
