#include <stdlib.h>
#include "ArbreQuat.h"
#include "Reseau.h"
#include "Chaine.h"

void chaineCoordMinMax(Chaines *C, double *xmin, double *ymin, double *xmax, double *ymax){
	CellChaine *chaine_courante;
	CellPoint *point_courant;

	//On parcours les chaînes de la liste chaînée
	chaine_courante = C -> chaines;
	while (chaine_courante){
		//On parcours les points de la chaîne courante
		point_courant = chaine_courante -> points;
		while (point_courant){
			if(point_courant -> x > *xmax) *xmax = point_courant -> x;
      		if(point_courant -> y > *ymax) *ymax = point_courant -> y;
      		if(point_courant -> x < *xmin) *xmin = point_courant -> x;
      		if(point_courant -> y < *ymin) *ymin = point_courant -> y;
      	point_courant = point_courant -> suiv;
		}
    chaine_courante = chaine_courante -> suiv;
	}
}

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX,double coteY){
    ArbreQuat* new_ArbreQuat = (ArbreQuat*)malloc(sizeof(ArbreQuat));
    if(new_ArbreQuat == NULL){
		fprintf(stderr, "Erreur\n");
		exit(1);
    }
    new_ArbreQuat -> xc = xc;
    new_ArbreQuat -> yc = yc;
    new_ArbreQuat -> coteX = coteX;
    new_ArbreQuat -> coteY = coteY;
    new_ArbreQuat -> noeud = NULL;
    new_ArbreQuat -> so = NULL;
    new_ArbreQuat -> se = NULL;
    new_ArbreQuat -> no = NULL;
    new_ArbreQuat -> ne = NULL;
    return new_ArbreQuat;
}

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat*parent){
    double X1;
    double Y1;
    double X2;
    double Y2;
    ArbreQuat* new_ArbreQuat;
    Noeud* ancien_noeud;


	//Cas Arbre vide => il faut creer un arbre
    if(*a==NULL){
        X1 = n->x;
        Y1 = n->y;
        X2 = parent->xc;
        Y2 = parent->yc;
        new_ArbreQuat;
        *a = (ArbreQuat*)malloc(sizeof(ArbreQuat));

        if(X1<X2 && Y1<Y2){
            //PARTIE SUD OUEST
            new_ArbreQuat = creerArbreQuat( (parent->xc) - ((parent->coteX)/4) , (parent -> yc) - ((parent->coteY)/4) , (parent->coteX)/2 , (parent->coteY)/2);
            new_ArbreQuat -> noeud = n;
        }
        if(X1<X2 && Y1>Y2){
            //PARTIE NORD OUEST
            new_ArbreQuat = creerArbreQuat( (parent->xc) - ((parent->coteX)/4) , (parent -> yc) + ((parent->coteY)/4) , (parent->coteX)/2 , (parent->coteY)/2);
            new_ArbreQuat -> noeud = n;
        }

        if(X1>X2 && Y1<Y2){
            //PARTIE SUD EST
            new_ArbreQuat = creerArbreQuat( (parent->xc) + ((parent->coteX)/4) , (parent -> yc) - ((parent->coteY)/4) , (parent->coteX)/2 , (parent->coteY)/2);
            new_ArbreQuat -> noeud = n;
        }

        if(X1>X2 && Y1>Y2){
            //PARTIE NORD EST
            new_ArbreQuat = creerArbreQuat( (parent->xc) + ((parent->coteX)/4) , (parent -> yc) + ((parent->coteY)/4) , (parent->coteX)/2 , (parent->coteY)/2);
            new_ArbreQuat -> noeud = n;
        }

        (*a) = new_ArbreQuat;
    }

    else{
        //Cas Feuille
        if((*a)->noeud != NULL){
            //On recupère l'ancien noeud
            ancien_noeud = (*a)->noeud;
            (*a)->noeud = NULL;
            insererNoeudArbre(n, a, parent);
            insererNoeudArbre(ancien_noeud, a, parent);
        }

        //Cas Noeud interne
        else{
            X1 = n->x;
            Y1 = n->y;
            X2 = (*a)->xc;
            Y2 = (*a)->yc;

            if(X1<X2 && Y1<Y2){
                //PARTIE SUD OUEST
                insererNoeudArbre(n , &((*a)->so) , *a);
            }
            if(X1<X2 && Y1>Y2){
                //PARTIE NORD OUEST
                insererNoeudArbre(n , &((*a)->no) , *a);
            }

            if(X1>X2 && Y1<Y2){
                //PARTIE SUD EST
                insererNoeudArbre(n , &((*a)->se) , *a);
            }

            if(X1>X2 && Y1>Y2){
                //PARTIE NORD EST
                insererNoeudArbre(n , &((*a)->ne) , *a);
            }
        }
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat*parent, double x, double y){
    Noeud* noeud;
    CellNoeud *cel_noeud;

    //Cas Arbre vide
    if(*a == NULL){                                         //ATTENTION
        noeud = creer_noeud(x,y,(R->nbNoeuds)+1);                               
        cel_noeud=creer_cell_noeud(noeud);
        ajout_NoeudReseau(R,cel_noeud);
        insererNoeudArbre(noeud,a,parent);
        return noeud; 
    }

    else{
        //Cas Feuille
        if((*a)->noeud != NULL){
            if((*a)->noeud->x == x && (*a)->noeud->y==y){
                return (*a)->noeud;
            }

            else{
                noeud = creer_noeud(x,y,(R->nbNoeuds)+1);
                cel_noeud = creer_cell_noeud(noeud);
                ajout_NoeudReseau(R,cel_noeud);
                insererNoeudArbre(noeud,a,parent);
                return noeud;    
            }
        }  

        //Cas Noeud Interne
        else{
            double X = (*a)->xc;
            double Y = (*a)->yc;

            if(x<X && y<Y){
                //PARTIE SUD OUEST
                return rechercheCreeNoeudArbre(R,&((*a)->so),*a,x,y);
            }
            if(x<X && y>Y){
                //PARTIE NORD OUEST
                return rechercheCreeNoeudArbre(R,&((*a)->no),*a,x,y);
            }

            if(x>X && y<Y){
                //PARTIE SUD EST
                return rechercheCreeNoeudArbre(R,&((*a)->se),*a,x,y);
            }

            if(x>X && y>Y){
                //PARTIE NORD EST
                return rechercheCreeNoeudArbre(R,&((*a)->ne),*a,x,y);
            }
        }    
    }
}

Reseau* reconstitueReseauArbre(Chaines* C){
    double xmin = 0;
    double xmax = 0;
    double ymin = 0;
    double ymax = 0;

    chaineCoordMinMax(C,&xmin,&ymin,&xmax,&ymax);

    ArbreQuat* parent = creerArbreQuat(xmin + (xmax-xmin)/2,ymin+(ymax-ymin)/2,xmax-xmin,ymax-ymin) ; /* arbre parent */
    ArbreQuat* Arbre; /*arbre courant dans la recherche ou l'insertion */
    Arbre = parent;

    Reseau* R = creer_reseau(C->gamma); //création du réseau
    CellChaine* cell_chaines = C->chaines; /* chaine courante */
    CellPoint* points; /* point courant dans la chaine courante */

    Noeud* prec = NULL; /* element precedent d'un noeud dans une chaine */
    Noeud* extrA; /* extremite A d'une chaine */
    Noeud* extrB; /* extremite B d'une chaine et noeud courant  correspondant au point courant aussi*/
    
	/* on parcourt chaque point de chaque chaine de C et on l'ajoute a la liste de noeuds de R s'il n'est pas present */
    while(cell_chaines){
        points = cell_chaines->points;
        prec = NULL;

		// Extrémité A de la chaine qu'on garde pour les commodités
        if(points){
            extrA = rechercheCreeNoeudArbre(R,&Arbre,parent,points->x,points->y);
        }

        while(points){

            /* on ajoute le noeud si on ne l'a pas deja rencontre grâce à la fonction rechercheCreeNoeudArbre,
			et on renvoie le noeud pour l'utiliser dans la fonction ajout_CellNoeudVoisin
			noeudCourant correspondant à un noeud contenant un point */

            extrB = rechercheCreeNoeudArbre(R,&Arbre,parent,points->x,points->y);


            //on ajoute ses voisins

            if(prec){
                //le voisin précédent
                ajouter_voisin(extrB,prec);
            }

            if(points->suiv){
                //le voisin suivant
                ajouter_voisin(extrB,rechercheCreeNoeudArbre(R,&Arbre,parent,(points->suiv)->x,(points->suiv)->y));
            }

            prec = extrB;
            points = points -> suiv;
        }
		/* Si la chaine compte plus d'un point , cela veut dire qu'on peut avoir des commodités et qu'on peut ajouter l'extrémité B */
		if (comptePoints(cell_chaines) > 1){
			ajouter_commodite(R,creer_commodite(extrA, extrB));
		}
        cell_chaines = cell_chaines->suiv;
    }
	libere_arbre(parent);
    return R;
}

void libere_arbre(ArbreQuat *a){
	if (a != NULL){
		libere_arbre(a->so);
		libere_arbre(a->se);
		libere_arbre(a->no);
		libere_arbre(a->ne);
		free(a);
	}
}

