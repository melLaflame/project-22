#include "Hachage.h"
#include "Reseau.h"
#include "Chaine.h"
#include <math.h>
#include <stdlib.h>

#define A ((sqrt(5) - 1) / 2)

int fonctionClef(int x , int y){
	return y + (x + y) * (x + y + 1) / 2;
}

/*
Pour x = 1 et y = 1 => clé = 4
Pour x = 1 et y = 2 => clé = 8
Pour x = 1 et y = 3 => clé = 13
Pour x = 1 et y = 4 => clé = 19
Pour x = 1 et y = 5 => clé = 26
Pour x = 1 et y = 6 => clé = 34
Pour x = 1 et y = 7 => clé = 43
Pour x = 1 et y = 8 => clé = 53
Pour x = 1 et y = 9 => clé = 64
Pour x = 1 et y = 10 => clé = 76
Pour x = 2 et y = 1 => clé = 7
Pour x = 2 et y = 2 => clé = 12
Pour x = 2 et y = 3 => clé = 18
Pour x = 2 et y = 4 => clé = 25
Pour x = 2 et y = 5 => clé = 33
Pour x = 2 et y = 6 => clé = 42
Pour x = 2 et y = 7 => clé = 52
Pour x = 2 et y = 8 => clé = 63
Pour x = 2 et y = 9 => clé = 75
Pour x = 2 et y = 10 => clé = 88
Pour x = 3 et y = 1 => clé = 11
Pour x = 3 et y = 2 => clé = 17
Pour x = 3 et y = 3 => clé = 24
Pour x = 3 et y = 4 => clé = 32
Pour x = 3 et y = 5 => clé = 41
Pour x = 3 et y = 6 => clé = 51
Pour x = 3 et y = 7 => clé = 62
Pour x = 3 et y = 8 => clé = 74
Pour x = 3 et y = 9 => clé = 87
Pour x = 3 et y = 10 => clé = 101
Pour x = 4 et y = 1 => clé = 16
Pour x = 4 et y = 2 => clé = 23
Pour x = 4 et y = 3 => clé = 31
Pour x = 4 et y = 4 => clé = 40
Pour x = 4 et y = 5 => clé = 50
Pour x = 4 et y = 6 => clé = 61
Pour x = 4 et y = 7 => clé = 73
Pour x = 4 et y = 8 => clé = 86
Pour x = 4 et y = 9 => clé = 100
Pour x = 4 et y = 10 => clé = 115
Pour x = 5 et y = 1 => clé = 22
Pour x = 5 et y = 2 => clé = 30
Pour x = 5 et y = 3 => clé = 39
Pour x = 5 et y = 4 => clé = 49
Pour x = 5 et y = 5 => clé = 60
Pour x = 5 et y = 6 => clé = 72
Pour x = 5 et y = 7 => clé = 85
Pour x = 5 et y = 8 => clé = 99
Pour x = 5 et y = 9 => clé = 114
Pour x = 5 et y = 10 => clé = 130
Pour x = 6 et y = 1 => clé = 29
Pour x = 6 et y = 2 => clé = 38
Pour x = 6 et y = 3 => clé = 48
Pour x = 6 et y = 4 => clé = 59
Pour x = 6 et y = 5 => clé = 71
Pour x = 6 et y = 6 => clé = 84
Pour x = 6 et y = 7 => clé = 98
Pour x = 6 et y = 8 => clé = 113
Pour x = 6 et y = 9 => clé = 129
Pour x = 6 et y = 10 => clé = 146
Pour x = 7 et y = 1 => clé = 37
Pour x = 7 et y = 2 => clé = 47
Pour x = 7 et y = 3 => clé = 58
Pour x = 7 et y = 4 => clé = 70
Pour x = 7 et y = 5 => clé = 83
Pour x = 7 et y = 6 => clé = 97
Pour x = 7 et y = 7 => clé = 112
Pour x = 7 et y = 8 => clé = 128
Pour x = 7 et y = 9 => clé = 145
Pour x = 7 et y = 10 => clé = 163
Pour x = 8 et y = 1 => clé = 46
Pour x = 8 et y = 2 => clé = 57
Pour x = 8 et y = 3 => clé = 69
Pour x = 8 et y = 4 => clé = 82
Pour x = 8 et y = 5 => clé = 96
Pour x = 8 et y = 6 => clé = 111
Pour x = 8 et y = 7 => clé = 127
Pour x = 8 et y = 8 => clé = 144
Pour x = 8 et y = 9 => clé = 162
Pour x = 8 et y = 10 => clé = 181
Pour x = 9 et y = 1 => clé = 56
Pour x = 9 et y = 2 => clé = 68
Pour x = 9 et y = 3 => clé = 81
Pour x = 9 et y = 4 => clé = 95
Pour x = 9 et y = 5 => clé = 110
Pour x = 9 et y = 6 => clé = 126
Pour x = 9 et y = 7 => clé = 143
Pour x = 9 et y = 8 => clé = 161
Pour x = 9 et y = 9 => clé = 180
Pour x = 9 et y = 10 => clé = 200
Pour x = 10 et y = 1 => clé = 67
Pour x = 10 et y = 2 => clé = 80
Pour x = 10 et y = 3 => clé = 94
Pour x = 10 et y = 4 => clé = 109
Pour x = 10 et y = 5 => clé = 125
Pour x = 10 et y = 6 => clé = 142
Pour x = 10 et y = 7 => clé = 160
Pour x = 10 et y = 8 => clé = 179
Pour x = 10 et y = 9 => clé = 199
Pour x = 10 et y = 10 => clé = 220
*/

int fonctionHachage(int clef,int M){
	int res = floor(M * (clef * A - floor(clef * A)));
	return res;
}

Noeud* rechercheCreeNoeudHachage(Reseau *R, tHachage* H, double x, double y){
	int indice;
	Noeud *nouveauNoeud; /* nouveau noeud à inserer dans le réseau */
  	CellNoeud* cellnoeud; /* cellule qui contient le nouveau noeud */
	CellNoeud* tmp;
	CellNoeud* copie;

  	// indice de la table de hachage pour insérer le noeud
	indice = fonctionHachage(fonctionClef(x,y), H -> m);
	tmp = H -> T[indice];

	/* Parcours de la liste des noeuds de la table de hachage correspondant à l'indice pour savoir si le noeud à insérer existe
    déjà dans le réseau */
	while((tmp) && ((tmp -> nd -> x != x ) || (tmp->nd->y != y))){
		tmp = tmp->suiv;
	}

	// On a trouvé le noeud
	if (tmp){
		nouveauNoeud = tmp -> nd;
	}
	//On n'a pas trouvé le noeud
	else{
    	//On créé le noeud et l'ajoute dans le réseau
    	nouveauNoeud = creer_noeud(x, y,(R->nbNoeuds)+1);
    	cellnoeud = creer_cell_noeud(nouveauNoeud);
		//On doit faire une copie pour aussi l'ajouter dans la table de hachage
		copie = creer_cell_noeud(nouveauNoeud);
		ajout_NoeudReseau(R,cellnoeud);
		// ajout en tete de liste de H -> T[indice]
    	copie -> suiv = H->T[indice];
    	H -> T[indice]=copie;
		H->nE = (H->nE) +1;
	}
	return nouveauNoeud;
}

//Initialisation de la table de Hachage
tHachage *initTableHachage(int m){
	tHachage *tH = (tHachage*)malloc(sizeof(tHachage));
	if (!tH){
		fprintf(stderr, "Erreur lors de l'allocation de la table de hachage\n");
		exit(1);
	}
	tH -> nE = 0;
	tH  -> m = m;
	tH  -> T = (CellNoeud**)malloc(m*sizeof(CellNoeud*));
	for (int i = 0; i < m; i++){
		tH  -> T[i] = NULL;
	}
	return tH;
}

Reseau* reconstitueReseauHachage(Chaines *C, int M){
	CellChaine *chaine; /* chaine courante */
	CellPoint *point; /* point courant dans la chaine courante */
	Noeud *noeudCourant; /* noeudCourant correspondant au point courant */
	Noeud *extrA; /* extremite A d'une chaine */
	Noeud *extrB; /* extremite B d'une chaine */
	Noeud *prec; /* element precedent d'un noeud dans une chaine */
	tHachage *H; /* table de hachage */
	Reseau *R; /* le Reseau */

	//création du réseau
	R = creer_reseau(C->gamma);
	//Iniatialisation de la table de Hachage
	H = initTableHachage(M);

	chaine = C -> chaines;
	//On va parcourir chaque point de chaque chaîne de C et on l'ajoute à la liste des nœuds de R (s'il n'existe pas)
	while (chaine){
		point = chaine -> points;
		prec = NULL;

		// Extrémité A de la chaine qu'on garde pour les commodités
		if (point){
			extrA = rechercheCreeNoeudHachage(R, H, point -> x, point -> y);
		}

		while (point){
			/* on ajoute le noeud si on ne l'a pas deja rencontre grâce à la fonction rechercheCreeNoeudHachage,
			et on renvoie le noeud pour l'utiliser dans la fonction ajout_CellNoeudVoisin
			noeudCourant correspondant à un noeud contenant un point */
			noeudCourant  = rechercheCreeNoeudHachage(R, H, point -> x, point -> y);

			// on ajoute ses voisins
      		//le voisin précédent
			if (prec){
				ajouter_voisin(noeudCourant, prec);
			}

			//le voisin suivant
			if (point -> suiv){
				ajouter_voisin(noeudCourant, rechercheCreeNoeudHachage(R, H, point -> suiv -> x, point -> suiv -> y));
			}

			prec = noeudCourant;
			point = point -> suiv;
		}

		/* Si la chaine compte plus d'un point , cela veut dire qu'on peut avoir des commodités et qu'on peut ajouter l'extrémité B */
		if (comptePoints(chaine) > 1){
			extrB = prec;
			ajouter_commodite(R, creer_commodite(extrA, extrB));
		}
		chaine = chaine -> suiv;
	}
	detruire_tH(H);
	return R;
}


void detruire_cellNoeud_TH(CellNoeud *cellnoeud){
	CellNoeud *tmp;
	while (cellnoeud){
		tmp = cellnoeud;
		cellnoeud = cellnoeud->suiv;
		free(tmp);
	}
}

void detruire_tH(tHachage* H){
	for (int i=0; i<H->m; i++){
		detruire_cellNoeud_TH(H->T[i]);
	}
	free(H->T);
	free(H);
}
