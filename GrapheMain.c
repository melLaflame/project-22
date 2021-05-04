#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Reseau.h"
#include "Chaine.h"
#include "Graphe.h"
#include "Struct_Liste.h"
#include "Struct_File.h"

int main(int argc,char**argv){
    Graphe* graphe;
    Sommet** tab;;
    Arete* arete;
    Cellule_arete* cel_arete;

    FILE* fic = fopen("05000_USA-road-d-NY.cha","r");
    if(fic == NULL){
        printf("le fichier est null");
        return 0;
    }

    Chaines* instance = lectureChaine(fic);
    Reseau* r = reconstitueReseauListe(instance);
    graphe = creerGraphe(r);
    tab = graphe->T_som;

    /**for(int i=1;i<=graphe->nbsom;i++){                       //Pour afficher le graphe
        printf("x= %f\n",tab[i]->x);
        cel_arete = (tab[i])->L_voisin;
        while(cel_arete){
            arete = cel_arete -> a;
            printf("u = %d v = %d\n",arete ->u,arete->v);
            cel_arete = cel_arete ->suiv;
        }
    }**/

    printf("HEY");
    printf("%d\n",reorganiseReseau(r));
    freeGraphe(graphe);
    detruire_reseau(r);
    detruire_Chaines(instance);
    printf("HEY");
    return 0;
}

