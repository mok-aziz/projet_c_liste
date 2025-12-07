#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"
#include "jeu.c"
#include "joueur.h"
#include "joueur.c"
#include "distributeur.h"
#include "distributeur.c"
#include "combinaison.h"
#include "combinaison.c"
#include "score.h"
#include "score.c"
#include "bonbon.h"
#include "bonbon.c"






int choix_valide(int choix, int n) {
    return (choix>0&&choix<=n);
}

void parametrerMachine(int *nb_dis, int *max_bonbon) {
    printf("\n==== PARAMETRER MACHINE ===== \n");
    printf("Donnez nombre de distributeurs initial: ");
    scanf("%d",nb_dis);
    printf("Donnez la capacite d'un distributeur: ");
    scanf("%d",max_bonbon);
}

void parametrerDistributeur(Distributeur tab_dis[], int *nb_dis, Bonbon tab_bon[], int *taille_tab_bon, int max_bonbon) {
    int choix2;

    while(1) {
        printf("\n==== PARAMETRER DISTRIBUTEUR ===== \n");
        printf("1. Ajouter distributeur\n");
        printf("2. Supprimer distributeur\n");
        printf("3. Ajouter bonbon a un distributeur\n");
        printf("4. Retirer bonbon d'un distributeur\n");
        printf("5. Afficher distributeurs\n");
        printf("6. Retour\n");
        printf("================================== \n");

        scanf("%d",&choix2);

        if(!choix_valide(choix2,6)) {
            printf("Choix invalide!\n");
            continue;
        }

        switch(choix2) {
            case 1:
                creerDistributeur(tab_dis,nb_dis);
                break;
            case 2:
                supprimerDistributeur(tab_dis,nb_dis);
                break;
            case 3:
                printf("Donnez l'id du distributeur: ");
                int idd,pos=-1;
                scanf("%d",&idd);
                for(int i=0;i<*nb_dis;i++) {
                    if(tab_dis[i].id==idd) {
                        pos=i;
                        break;
                    }
                }
                if(pos!=-1) {
                    ajouterBonbon(&tab_dis[pos]);
                } else {
                    printf("Distributeur non trouve!\n");
                }
                break;
            case 4:
                printf("Donnez l'id du distributeur: ");
                int idd2,pos2=-1;
                scanf("%d",&idd2);
                for(int i=0;i<*nb_dis;i++) {
                    if(tab_dis[i].id==idd2) {
                        pos2=i;
                        break;
                    }
                }
                if(pos2!=-1) {
                    retirerBonbon(&tab_dis[pos2]);
                } else {
                    printf("Distributeur non trouve!\n");
                }
                break;
            case 5:
                if(*nb_dis==0) {
                    printf("Aucun distributeur!\n");
                } else {
                    for(int i=0;i<*nb_dis;i++) {
                        afficherDistributeur(tab_dis[i]);
                    }
                }
                break;
            case 6:
                return;
        }
    }
}

void parametrerCombinaison(Combinaison tab_comb[], int *taille_tab_comb) {
    int choix3;

    while(1) {
        printf("\n==== PARAMETRER COMBINAISON ===== \n");
        printf("1. Ajouter combinaison\n");
        printf("2. Supprimer combinaison\n");
        printf("3. Modifier combinaison\n");
        printf("4. Afficher combinaisons\n");
        printf("5. Retour\n");
        printf("================================== \n");

        scanf("%d",&choix3);

        if(!choix_valide(choix3,5)) {
            printf("Choix invalide!\n");
            continue;
        }

        switch(choix3) {
            case 1:
                if(*taille_tab_comb<25) {
                    tab_comb[*taille_tab_comb]=creeCombinaison(taille_tab_comb);
                } else {
                    printf("Nombre maximum de combinaisons atteint!\n");
                }
                break;
            case 2:
                printf("Donnez l'id de la combinaison a supprimer: ");
                int id;
                scanf("%d",&id);
                supprimerCombinaison(tab_comb,taille_tab_comb,id);
                break;
            case 3:
                printf("Donnez l'id de la combinaison a modifier: ");
                int id_mod;
                scanf("%d",&id_mod);
                int trouve=0;
                for(int i=0;i<*taille_tab_comb;i++) {
                    if(tab_comb[i].id==id_mod) {
                        modifierCombinaison(&tab_comb[i]);
                        trouve=1;
                        break;
                    }
                }
                if(!trouve) {
                    printf("Combinaison non trouvee!\n");
                }
                break;
            case 4:
                if(*taille_tab_comb==0) {
                    printf("Aucune combinaison!\n");
                } else {
                    for(int i=0;i<*taille_tab_comb;i++) {
                        afficherCombinaison(tab_comb[i]);
                    }
                }
                break;
            case 5:
                return;
        }
    }
}

int main() {

    Jeu jeu;
    initialiserJeu(&jeu);

    // tableaux auxiliaires pour la gestion
    int taille_tab_bon=0;
    Bonbon tab_bon[30];
    int nb_dis=0;
    int max_bonbon=100;

    int choix;

    printf("\n========================================\n");
    printf("   BIENVENUE A LA MACHINE A BONBONS!\n");
    printf("========================================\n");

    while(1) {
        printf("\n==== MACHINE A BONBONS ==== \n");
        printf("1. Jouer une partie \n");
        printf("2. Parametrer le jeu \n");
        printf("3. Voir les scores \n");
        printf("4. Quitter \n");
        printf("============================ \n");
        printf("Votre choix: ");

        scanf("%d",&choix);

        if(choix==4) {
            printf("\nMerci d'avoir joue! Au revoir!\n");
            break;
        }

        if(!choix_valide(choix,4)) {
            printf("Choix invalide!\n");
            continue;
        }

        switch(choix) {
            case 1: {
                // Vérifications avant de jouer
                if(jeu.nbCombinaisons==0) {
                    printf("\nVeuillez d'abord definir au moins une combinaison!\n");
                    break;
                }

                if(nb_dis==0||jeu.distributeurs[0].nb_bonbons_actuel<3) {
                    printf("\nVeuillez d'abord creer un distributeur avec au moins 3 bonbons!\n");
                    break;
                }

                // Demander le nombre de joueurs
                int nb_joueurs_partie;
                printf("\nCombien de joueurs pour cette partie? (1-10): ");
                scanf("%d",&nb_joueurs_partie);

                if(nb_joueurs_partie<1||nb_joueurs_partie>10) {
                    printf("Nombre de joueurs invalide! (Entre 1 et 10)\n");
                    break;
                }

                // Créer les joueurs pour cette partie
                printf("\n=== CREATION DES JOUEURS ===\n");
                for(int i=0;i<nb_joueurs_partie;i++) {
                    if(jeu.nbJoueurs<10) {
                        printf("\nJoueur %d:\n",i+1);
                        creeJoueur(jeu.joueurs,&jeu.nbJoueurs);
                    } else {
                        printf("Nombre maximum de joueurs atteint!\n");
                        break;
                    }
                }

                // Lancer la partie pour chaque joueur
                for(int i=jeu.nbJoueurs-nb_joueurs_partie;i<jeu.nbJoueurs;i++) {
                    printf("\n\n========================================\n");
                    printf("Au tour de: %s\n",jeu.joueurs[i].pseudo);
                    printf("========================================\n");

                    // Simuler la partie pour ce joueur
                    int joueur_actuel_index=jeu.nbJoueurs-1;
                    jeu.nbJoueurs=i+1;
                    lancerPartie(&jeu);
                    jeu.nbJoueurs=joueur_actuel_index+1;
                }

                printf("\n\n=== RESULTATS DE LA PARTIE ===\n");
                for(int i=jeu.nbJoueurs-nb_joueurs_partie;i<jeu.nbJoueurs;i++) {
                    aficherJoueur(jeu.joueurs[i]);
                }

                break;
            }

            case 2: {
                int choix1;
                while(1) {
                    printf("\n==== PARAMETRER LE JEU ===== \n");
                    printf("1. Parametrer machine \n");
                    printf("2. Parametrer distributeur \n");
                    printf("3. Parametrer combinaison \n");
                    printf("4. Gerer les bonbons \n");
                    printf("5. Retour au menu principal \n");
                    printf("============================ \n");
                    printf("Votre choix: ");

                    scanf("%d",&choix1);

                    if(choix1==5) break;

                    if(!choix_valide(choix1,5)) {
                        printf("Choix invalide!\n");
                        continue;
                    }

                    switch(choix1) {
                        case 1:
                            parametrerMachine(&nb_dis,&max_bonbon);
                            break;
                        case 2:
                            parametrerDistributeur(jeu.distributeurs,&nb_dis,tab_bon,&taille_tab_bon,max_bonbon);
                            break;
                        case 3:
                            parametrerCombinaison(jeu.combinaisons,&jeu.nbCombinaisons);
                            break;
                        case 4: {
                            int choix_bonbon;
                            printf("\n==== GESTION DES BONBONS ==== \n");
                            printf("1. Ajouter bonbon a la liste\n");
                            printf("2. Afficher bonbons de la liste\n");
                            printf("3. Retour\n");
                            printf("Votre choix: ");
                            scanf("%d",&choix_bonbon);

                            if(choix_bonbon==1) {
                                creeBonbon(tab_bon,&taille_tab_bon);
                            } else if(choix_bonbon==2) {
                                if(taille_tab_bon==0) {
                                    printf("Aucun bonbon dans la liste!\n");
                                } else {
                                    for(int i=0;i<taille_tab_bon;i++) {
                                        printf("%d. ",i+1);
                                        afficheBonbon(tab_bon[i]);
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                break;
            }

            case 3:
                if(jeu.nbScores==0) {
                    printf("\nAucun score enregistre!\n");
                } else {
                    printf("\n==== HISTORIQUE DES SCORES ====\n");
                    afficherscore(jeu.scores,jeu.nbScores);

                    // Proposer de trier
                    printf("\nVoulez-vous trier les scores? (1=Oui, 0=Non): ");
                    int trier;
                    scanf("%d",&trier);
                    if(trier==1) {
                        trierScore(jeu.scores,jeu.nbScores);
                        afficherscore(jeu.scores,jeu.nbScores);
                    }
                }
                break;
        }
    }

    return 0;
}
