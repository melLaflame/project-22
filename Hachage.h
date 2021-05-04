#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"
#define A ((sqrt(5) - 1) / 2)

typedef struct table{
  int nE; /*nombre d’elements contenus dans la table de hachage */
  int m; /*taille de la table de hachage */
  CellNoeud ** T; /*table de hachage avec resolution des collisions par chainage */
}tHachage;

int fonctionClef(int x , int y);
int fonctionHachage(int clef,int M);
Noeud* rechercheCreeNoeudHachage(Reseau *R, tHachage* H, double x, double y);
tHachage *initTableHachage(int m);
Reseau* reconstitueReseauHachage(Chaines *C, int M);
void detruire_cellNoeud_TH(CellNoeud *cellnoeud);
void detruire_tH(tHachage* H);


#endif
