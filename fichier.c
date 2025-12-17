#include "fichier.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void sauvegarderJoueurs(ListeJoueurs *liste) {
    FILE *f = fopen(FICHIER_JOUEURS, "w");
    if (f == NULL) {
        printf("Erreur: impossible d'ouvrir %s en ecriture\n", FICHIER_JOUEURS);
        return;
    }
    NoeudJoueur *courant = liste->tete;
    while (courant != NULL) {
        fprintf(f, "%s %d\n",
                courant->joueur.pseudo,
                courant->joueur.scoreTotal);
        courant = courant->suivant;
    }
    fclose(f);
    printf("Joueurs sauvegardes dans %s\n", FICHIER_JOUEURS);
}

void sauvegarderDistributeurs(ListeDistributeurs *liste) {
    FILE *f = fopen(FICHIER_DISTRIBUTEURS, "w");
    if (f == NULL) {
        printf("Erreur: impossible d'ouvrir %s en ecriture\n", FICHIER_DISTRIBUTEURS);
        return;
    }

    NoeudDistributeur *courant = liste->tete;
    while (courant != NULL) {
        fprintf(f, "DISTRIBUTEUR %d %d\n",
                courant->distributeur.id,
                courant->distributeur.nb_bonbons_actuel);

        // Sauvegarder les bonbons de ce distributeur
        NoeudBonbon *bonbon = courant->distributeur.reserve.tete;
        while (bonbon != NULL) {
            fprintf(f, "BONBON %s %d\n",
                    bonbon->bonbon.couleur,
                    bonbon->bonbon.valeur);
            bonbon = bonbon->suivant;
        }

        fprintf(f, "FIN_DISTRIBUTEUR\n");
        courant = courant->suivant;
    }

    fclose(f);
    printf("Distributeurs sauvegardes dans %s\n", FICHIER_DISTRIBUTEURS);
}

void sauvegarderCombinaisons(ListeCombinaisons *liste) {
    FILE *f = fopen(FICHIER_COMBINAISONS, "w");
    if (f == NULL) {
        printf("Erreur: impossible d'ouvrir %s en ecriture\n", FICHIER_COMBINAISONS);
        return;
    }

    NoeudCombinaison *courant = liste->tete;
    while (courant != NULL) {
        fprintf(f, "%d %s %s %s %d\n",
                courant->combinaison.id,
                courant->combinaison.couleurs[0],
                courant->combinaison.couleurs[1],
                courant->combinaison.couleurs[2],
                courant->combinaison.points);
        courant = courant->suivant;
    }

    fclose(f);
    printf("Combinaisons sauvegardees dans %s\n", FICHIER_COMBINAISONS);
}

void sauvegarderScoresFichier(ListeScores *liste) {
    FILE *f = fopen(FICHIER_SCORES, "w");
    if (f == NULL) {
        printf("Erreur: impossible d'ouvrir %s en ecriture\n", FICHIER_SCORES);
        return;
    }

    NoeudScore *courant = liste->tete;
    while (courant != NULL) {
        fprintf(f, "%s %d %s\n",
                courant->score.pseudo,
                courant->score.valeur,
                courant->score.date);
        courant = courant->suivant;
    }

    fclose(f);
    printf("Scores sauvegardes dans %s\n", FICHIER_SCORES);
}

void sauvegarderBonbons(ListeBonbons *liste) {
    FILE *f = fopen(FICHIER_BONBONS, "w");
    if (f == NULL) {
        printf("Erreur: impossible d'ouvrir %s en ecriture\n", FICHIER_BONBONS);
        return;
    }

    NoeudBonbon *courant = liste->tete;
    while (courant != NULL) {
        fprintf(f, "%s %d\n",
                courant->bonbon.couleur,
                courant->bonbon.valeur);
        courant = courant->suivant;
    }

    fclose(f);
    printf("Bonbons sauvegardes dans %s\n", FICHIER_BONBONS);
}

void sauvegarderTout(Jeu *jeu, ListeBonbons *liste_bonbons) {
    printf("\n=== SAUVEGARDE EN COURS ===\n");
    sauvegarderJoueurs(&jeu->joueurs);
    sauvegarderDistributeurs(&jeu->distributeurs);
    sauvegarderCombinaisons(&jeu->combinaisons);
    sauvegarderScoresFichier(&jeu->scores);
    sauvegarderBonbons(liste_bonbons);
    printf("=== SAUVEGARDE TERMINEE ===\n");
}


void chargerJoueurs(ListeJoueurs *liste, int *nbJoueurs) {
    FILE *f = fopen(FICHIER_JOUEURS, "r");
    if (f == NULL) {
        printf("Aucun fichier %s trouve (premiere execution)\n", FICHIER_JOUEURS);
        return;
    }

    char pseudo[50];
    int score;

    while (fscanf(f, "%s %d", pseudo, &score) == 2) {
        NoeudJoueur *nouveau = (NoeudJoueur*)malloc(sizeof(NoeudJoueur));
        if (nouveau == NULL) {
            printf("Erreur d'allocation memoire!\n");
            break;
        }

        strcpy(nouveau->joueur.pseudo, pseudo);
        nouveau->joueur.scoreTotal = score;
        nouveau->suivant = liste->tete;
        liste->tete = nouveau;
        liste->taille++;
    }

    *nbJoueurs = liste->taille;
    fclose(f);
    printf("%d joueur(s) charge(s)\n", liste->taille);
}

void chargerDistributeurs(ListeDistributeurs *liste) {
    FILE *f = fopen(FICHIER_DISTRIBUTEURS, "r");
    if (f == NULL) {
        printf("Aucun fichier %s trouve (premiere execution)\n", FICHIER_DISTRIBUTEURS);
        return;
    }

    char ligne[100];
    NoeudDistributeur *dist_courant = NULL;

    while (fgets(ligne, sizeof(ligne), f)) {
        if (strncmp(ligne, "DISTRIBUTEUR", 12) == 0) {
            // Nouveau distributeur
            NoeudDistributeur *nouveau = (NoeudDistributeur*)malloc(sizeof(NoeudDistributeur));
            if (nouveau == NULL) {
                printf("Erreur d'allocation memoire!\n");
                break;
            }

            sscanf(ligne, "DISTRIBUTEUR %d %d",
                   &nouveau->distributeur.id,
                   &nouveau->distributeur.nb_bonbons_actuel);

            nouveau->distributeur.reserve.tete = NULL;
            nouveau->distributeur.reserve.taille = 0;
            nouveau->suivant = liste->tete;
            liste->tete = nouveau;
            liste->taille++;

            dist_courant = nouveau;
        }
        else if (strncmp(ligne, "BONBON", 6) == 0 && dist_courant != NULL) {
            // Ajouter un bonbon au distributeur courant
            NoeudBonbon *nouveau_bonbon = (NoeudBonbon*)malloc(sizeof(NoeudBonbon));
            if (nouveau_bonbon == NULL) {
                printf("Erreur d'allocation memoire!\n");
                break;
            }

            sscanf(ligne, "BONBON %s %d",
                   nouveau_bonbon->bonbon.couleur,
                   &nouveau_bonbon->bonbon.valeur);

            nouveau_bonbon->suivant = dist_courant->distributeur.reserve.tete;
            dist_courant->distributeur.reserve.tete = nouveau_bonbon;
            dist_courant->distributeur.reserve.taille++;
        }
        else if (strncmp(ligne, "FIN_DISTRIBUTEUR", 16) == 0) {
            dist_courant = NULL;
        }
    }

    fclose(f);
    printf("%d distributeur(s) charge(s)\n", liste->taille);
}

void chargerCombinaisons(ListeCombinaisons *liste, int *nbCombinaisons) {
    FILE *f = fopen(FICHIER_COMBINAISONS, "r");
    if (f == NULL) {
        printf("Aucun fichier %s trouve (premiere execution)\n", FICHIER_COMBINAISONS);
        return;
    }

    int id, points;
    char couleur1[30], couleur2[30], couleur3[30];

    while (fscanf(f, "%d %s %s %s %d", &id, couleur1, couleur2, couleur3, &points) == 5) {
        NoeudCombinaison *nouveau = (NoeudCombinaison*)malloc(sizeof(NoeudCombinaison));
        if (nouveau == NULL) {
            printf("Erreur d'allocation memoire!\n");
            break;
        }

        nouveau->combinaison.id = id;
        strcpy(nouveau->combinaison.couleurs[0], couleur1);
        strcpy(nouveau->combinaison.couleurs[1], couleur2);
        strcpy(nouveau->combinaison.couleurs[2], couleur3);
        nouveau->combinaison.points = points;

        nouveau->suivant = liste->tete;
        liste->tete = nouveau;
        liste->taille++;
    }

    *nbCombinaisons = liste->taille;
    fclose(f);
    printf("%d combinaison(s) chargee(s)\n", liste->taille);
}

void chargerScoresFichier(ListeScores *liste, int *nbScores) {
    FILE *f = fopen(FICHIER_SCORES, "r");
    if (f == NULL) {
        printf("Aucun fichier %s trouve (premiere execution)\n", FICHIER_SCORES);
        return;
    }

    char pseudo[50], date[20];
    int valeur;

    while (fscanf(f, "%s %d %s", pseudo, &valeur, date) == 3) {
        NoeudScore *nouveau = (NoeudScore*)malloc(sizeof(NoeudScore));
        if (nouveau == NULL) {
            printf("Erreur d'allocation memoire!\n");
            break;
        }

        strcpy(nouveau->score.pseudo, pseudo);
        nouveau->score.valeur = valeur;
        strcpy(nouveau->score.date, date);

        nouveau->suivant = liste->tete;
        liste->tete = nouveau;
        liste->taille++;
    }

    *nbScores = liste->taille;
    fclose(f);
    printf("%d score(s) charge(s)\n", liste->taille);
}

void chargerBonbons(ListeBonbons *liste) {
    FILE *f = fopen(FICHIER_BONBONS, "r");
    if (f == NULL) {
        printf("Aucun fichier %s trouve (premiere execution)\n", FICHIER_BONBONS);
        return;
    }

    char couleur[30];
    int valeur;

    while (fscanf(f, "%s %d", couleur, &valeur) == 2) {
        NoeudBonbon *nouveau = (NoeudBonbon*)malloc(sizeof(NoeudBonbon));
        if (nouveau == NULL) {
            printf("Erreur d'allocation memoire!\n");
            break;
        }

        strcpy(nouveau->bonbon.couleur, couleur);
        nouveau->bonbon.valeur = valeur;

        nouveau->suivant = liste->tete;
        liste->tete = nouveau;
        liste->taille++;
    }

    fclose(f);
    printf("%d bonbon(s) charge(s)\n", liste->taille);
}

void chargerTout(Jeu *jeu, ListeBonbons *liste_bonbons) {
    printf("\n=== CHARGEMENT DES DONNEES ===\n");
    chargerJoueurs(&jeu->joueurs, &jeu->nbJoueurs);
    chargerDistributeurs(&jeu->distributeurs);
    chargerCombinaisons(&jeu->combinaisons, &jeu->nbCombinaisons);
    chargerScoresFichier(&jeu->scores, &jeu->nbScores);
    chargerBonbons(liste_bonbons);
    printf("=== CHARGEMENT TERMINE ===\n\n");
}
