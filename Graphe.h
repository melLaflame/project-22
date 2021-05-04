#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include<stdlib.h>
#include<stdio.h>
#include "Struct_Liste.h"

typedef struct{
  int u,v;        /* Numeros des sommets extremité */
} Arete;


typedef struct cellule_arete{
  Arete *a;     /* pointeur sur l'arete */
  struct cellule_arete *suiv;
} Cellule_arete;


typedef struct {
  int num;                 /* Numero du sommet (le meme que dans T_som) */
  double x, y;
  Cellule_arete* L_voisin;  /* Liste chainee des voisins */
} Sommet;


typedef struct{
  int e1,e2;    /* Les deux extremites de la commodite */
} Commod;


typedef struct{
  int nbsom;        /* Nombre de sommets */
  Sommet* *T_som;    /* Tableau de pointeurs sur sommets */
  int gamma;     
  int nbcommod;     /* Nombre de commodites */
  Commod *T_commod; /* Tableau des commodites */
} Graphe;

Arete* creer_arrete(int u, int v);
Cellule_arete* creer_cellule_arete(Arete* arete);
Sommet* creer_sommet(int num, double x, double y);
Commod* creer_commod(int e1, int e2);
Graphe* creer_graphe(int nbsom, int gamma, int nbcommod);
void ajouter_arrete_sommet(Arete* arete, Sommet* sommet);
void ajouter_commodite_graphe(Commod* commodite,Graphe* graphe,int postion);
Sommet* recherche_noeud_graphe(Noeud* noeud, Graphe* graphe);
Graphe* creerGraphe(Reseau* r);
int plus_petit_nbArete(Graphe* G, int r, int s);
void freeGraphe(Graphe* G);
int plus_petit_nbArete(Graphe* G, int r, int s);
int* pere(Graphe* G, int r, int s);
ListeEntier chemin(Graphe* G, int r, int s);
int reorganiseReseau(Reseau* r);

#endif
