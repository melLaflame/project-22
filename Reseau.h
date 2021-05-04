#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
void ecrireReseau(Reseau *R, FILE *f);
int nbLiaisons(Reseau *R);
int nbCommodites(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);
Noeud* creer_noeud(double x, double y, int num);
CellNoeud* creer_cell_noeud(Noeud* noeud);
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
void ajout_NoeudReseau(Reseau *R, CellNoeud *cellNoeud);
CellCommodite* creer_commodite(Noeud* A, Noeud* B);
Reseau* creer_reseau(int gamma);
void ajouter_voisin(Noeud* A, Noeud* B);
void ajouter_commodite(Reseau *R,CellCommodite *commodite);
Reseau* reconstitueReseauListe(Chaines *C);
int nbCommodites(Reseau *R);
int nbLiaison(Reseau *R);
void ecrireReseau(Reseau *R, FILE *f);
void detruire_CellCommodite(CellCommodite *cellcomm);
void detruire_Noeud(Noeud *n);
void detruire_cellNoeud(CellNoeud *cellnoeud);
void detruire_reseau(Reseau *r);























#endif

