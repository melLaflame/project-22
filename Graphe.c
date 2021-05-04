#include "Reseau.h"
#include "Chaine.h"
#include "Graphe.h"
#include "Struct_File.h"
#include "Struct_Liste.h"
#include "SVGwriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Arete* creer_arrete(int u, int v){
    Arete* arete = (Arete*)malloc(sizeof(Arete));
    arete -> u = u;
    arete -> v = v;
    return arete;
}

Cellule_arete* creer_cellule_arete(Arete* arete){
    Cellule_arete* cell_arete = (Cellule_arete*)malloc(sizeof(Cellule_arete));
    cell_arete -> a = arete;
    cell_arete -> suiv = NULL;
    return cell_arete;
}

Sommet* creer_sommet(int num, double x, double y){
    Sommet* sommet = (Sommet*)malloc(sizeof(Sommet));
    sommet->num = num;
    sommet->x = x;
    sommet -> y = y;
    sommet -> L_voisin = NULL;
    return sommet;
}

Commod* creer_commod(int e1, int e2){
    Commod* commodite = (Commod*)malloc(sizeof(Commod));
    commodite-> e1 = e1;
    commodite -> e2 = e2;
    return commodite;
}

Graphe* creer_graphe(int nbsom, int gamma, int nbcommod){
    Graphe* graphe = (Graphe*)malloc(sizeof(Graphe));
    graphe -> nbsom = nbsom;
    graphe -> gamma = gamma;
    graphe -> nbcommod = nbcommod;
    (graphe -> T_som) = (Sommet**)malloc(sizeof(Sommet*) * nbsom ); //on alloue la mémoire pour le tableau de pointeur sur sommet
    for(int i=0;i<nbsom;i++){ //chaque case est NULL (pour que l'on puisse y accéder)
        (graphe -> T_som)[i] = NULL;
    }

    (graphe -> T_commod) = (Commod*)malloc(sizeof(Commod) * nbcommod); //on alloue la mémoire pour le tableau de pointeur sur sommet
    /**for(int i=0;i<nbcommod;i++){ //chaque case est NULL (pour que l'on puisse y accéder)
        (graphe -> T_commod)[i] == NULL;
    }**/
    return graphe;
}

void ajouter_arrete_sommet(Arete* arete, Sommet* sommet){
    Cellule_arete* cell_arete = creer_cellule_arete(arete);
    (cell_arete->suiv) = sommet->L_voisin;
    (sommet->L_voisin) = cell_arete;
}   

void ajouter_commodite_graphe(Commod* commodite,Graphe* graphe,int position){
    (graphe -> T_commod)[position] = *commodite;
}

Sommet* recherche_noeud_graphe(Noeud* noeud, Graphe* graphe){
    //verifier si le noeud/sommet est déja dans le graphe si il est présent on le retourne
    for(int i = 0;i<graphe->nbsom;i++){
        if((graphe->T_som)[i] != NULL && ((graphe->T_som)[i])->num == noeud->num){
            return (graphe->T_som)[i];
        }
    }
    //sinon on crée un sommet et on l'ajoute au graphe
    Sommet* sommet = creer_sommet(noeud->num,noeud->x,noeud->y);
    (graphe->T_som)[noeud->num] = sommet ;
    return sommet;
}

Graphe* creerGraphe(Reseau* r){

    Noeud* noeud; // noeud à ajouter au graphe
    Noeud* noeud_voisin; //noeud voisin du noeud a ajouter au grpahe
    Sommet* sommet; //sommet correspondant à ajouter au graphe
    Sommet* sommet_voisin; //sommet voisin du sommet

    Arete* arete; //arrete incidente au sommet a ajouter au graphe
    Graphe* graphe = creer_graphe(r->nbNoeuds,r->gamma,nbCommodites(r)); // graphe a retoruner
    CellNoeud* cell_noeud = r->noeuds; //liste des noeuds du reseau
    CellNoeud* cell_noeud_voisin; //liste des voisins du noeud

    CellCommodite* cell_commodite = r->commodites;
    Commod* commodite;

    while(cell_noeud){
        noeud = cell_noeud ->nd;
        cell_noeud_voisin = noeud -> voisins;
        //on creer le sommet associe au noeud
        sommet = recherche_noeud_graphe(noeud,graphe);

        //on créer les arretes du sommets en regardant la liste de ses voisins
        while(cell_noeud_voisin){
            noeud_voisin = cell_noeud_voisin->nd;

            if(noeud->num > noeud_voisin->num){
                sommet_voisin = recherche_noeud_graphe(noeud_voisin,graphe); 
                arete = creer_arrete(noeud->num,noeud_voisin->num);
                ajouter_arrete_sommet(arete,sommet);
                ajouter_arrete_sommet(arete,sommet_voisin);
            }

            cell_noeud_voisin = cell_noeud_voisin -> suiv;
        }
        cell_noeud = cell_noeud->suiv;
    }

    int nb_commodites = 0 ;
    while(cell_commodite){
        commodite = creer_commod(cell_commodite->extrA->num,cell_commodite->extrB->num);
        ajouter_commodite_graphe(commodite,graphe,nb_commodites);
        cell_commodite = cell_commodite -> suiv;
        nb_commodites = nb_commodites+1;
    }
    return graphe;
}

void freeGraphe(Graphe* G){
  for(int i=1;i<G->nbsom;i++){
    while(G->T_som[i]->L_voisin){
      Cellule_arete* tmp=G->T_som[i]->L_voisin->suiv;
      //Pour eviter de desallouer 2 fois la meme arete, on desalloue seulement
      //quand le numero du sommet actuel est superieur au numero du sommet voisin
      if((G->T_som[i]->L_voisin->a->v < i) || (G->T_som[i]->L_voisin->a->u < i)){
        free(G->T_som[i]->L_voisin->a);
      }
      free(G->T_som[i]->L_voisin);
      G->T_som[i]->L_voisin=tmp;
    }
    free(G->T_som[i]);
  }
  printf("OOOO");
  /**free(G->T_som);
  free(G->T_commod);
  free(G);**/
}

//7.2
//le plus petit nombre d’aretes d’une chaine entre deux sommets r et s d’un graphe G
int plus_petit_nbArete(Graphe* G, int r, int s){
  //tableau des distances de r vers les autres sommets
  int* D=(int*)malloc(G->nbsom*sizeof(int));

  int* visit=(int*)malloc(G->nbsom*sizeof(int));
  for(int i=0;i<G->nbsom;i++){
    visit[i]=0;
    D[i]=0;
  }
  visit[r]=1;
  S_file* S=(S_file*)malloc(sizeof(S_file));
  Init_file(S);
  enfile(S,r);

  int nb;
  while (!(estFileVide(S))){
    int u=defile(S);
    Cellule_arete* cour=G->T_som[u]->L_voisin;
    while(cour!=NULL){
      int v;
      if(cour->a->u==u){
        v=cour->a->v;
      }
      else{
        v=cour->a->u;
      }

      if(visit[v]==0){
        visit[v]=1;
        D[v]=D[u]+1;
        enfile(S,v);
      }
      cour=cour->suiv;
    }
  }
  nb=D[s];
  free(visit);
  free(S);
  free(D);
  return nb;
}

//7.3
// retourne un tableau d’entiers contenant à l'indice i le numero du pere du sommet de numero i
int* pere(Graphe* G, int r, int s){
  //tableau des distances de r vers les autres sommets
  int* D=(int*)malloc(G->nbsom*sizeof(int));

  //tableau des peres des sommets
  int* P=(int*)malloc(G->nbsom*sizeof(int));

  int* visit=(int*)malloc(G->nbsom*sizeof(int));
  for(int i=0;i<G->nbsom;i++){
    visit[i]=0;
    D[i]=0;
    P[i]=-1;
  }

  P[r]=0;
  visit[r]=1;
  S_file* S=(S_file*)malloc(sizeof(S_file));
  Init_file(S);
  enfile(S,r);

  int v=-1;
  while ((!(estFileVide(S))) && (v!=s)){
    int u=defile(S);
    Cellule_arete* cour=G->T_som[u]->L_voisin;
    while((cour!=NULL) && (v!=s)){
      if(cour->a->u==u){
        v=cour->a->v;
      }
      else{
        v=cour->a->u;
      }

      if(visit[v]==0){
        visit[v]=1;
        D[v]=D[u]+1;
        P[v]=u;
        enfile(S,v);
      }
      cour=cour->suiv;
    }
  }
  free(visit);
  free(S);
  free(D);
  return P;
}

ListeEntier chemin(Graphe* G, int r, int s){
    int* P = pere(G, r, s);
    ListeEntier L;
	Init_Liste(&L);
	ajoute_en_tete(&L, s);
    int a=s;
	while(a!=r){
		ajoute_en_tete(&L, P[a]);
		a=P[a];
	}
	return L;
}

int reorganiseReseau(Reseau* r){
  //cree le graphe correspondant au reseau
  Graphe* G=creerGraphe(r);

  int nbsom=G->nbsom;
  int nbcommod=G->nbcommod;
  ListeEntier* L=(ListeEntier*)malloc(nbcommod*sizeof(ListeEntier));
  Commod c;
  int i;
  int j;
  //calcule la plus courte chaine pour chaque commodite
  
  for(i=0;i<nbcommod;i++){
    c=G->T_commod[i];
    L[i]=chemin(G, c.e1, c.e2);
  }


  //Initialisation et declaration de la matrice
  int** mat=(int**)malloc(nbsom*sizeof(int*));
  for(i=0;i<nbsom;i++){
    mat[i]=(int*)malloc(nbsom*sizeof(int));
  }
  for(i=0;i<nbsom;i++){
    for(j=0;j<nbsom;j++){
      mat[i][j]=0;
    }
  }

  ListeEntier l;
  int u = L[0]->u;
  int v;

  for(i=1;i<nbcommod;i++){
    l=L[i];
    while(l!=NULL){
      v=l->u;
      mat[u][v]++;
      mat[v][u]++;
      u=v;
      l=l->suiv;
    }
  }

  int bool=1;
  for(i=0;i<nbsom;i++){
    for(j=0;j<nbsom;j++){
      if(mat[i][j]>=G->gamma){
        bool=0;
        break;
      }
    }
  }

  //desallocation
  for(i=0;i<nbcommod;i++){
    free(L[i]);
  }

  free(L);
  for(i=0;i<nbsom;i++){
    free(mat[i]);
  }
  free(mat);
  printf("HEYY555\n");
  freeGraphe(G);
  printf("HEYY6666\n");
  return bool;
}
