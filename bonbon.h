#ifndef BONBON_H_INCLUDED
#define BONBON_H_INCLUDED

struct Bonbon {
    char couleur[20];
    int valeur;
};
typedef struct Bonbon Bonbon;

// Noeud pour la liste chainee de bonbons
struct NoeudBonbon {
    Bonbon bonbon;
    struct NoeudBonbon *suivant;
};
typedef struct NoeudBonbon NoeudBonbon;

// Liste chainee de bonbons (remplace le tableau)
typedef struct {
    NoeudBonbon *tete;
    int taille;
} ListeBonbons;

void creeBonbon(ListeBonbons *liste);
void afficheBonbon(Bonbon b);
void afficherListeBonbons(ListeBonbons *liste);
void modifierBonbon(Bonbon *b);
void supprimerBonbon(ListeBonbons *liste, char couleur[]);

#endif // BONBON_H_INCLUDED
