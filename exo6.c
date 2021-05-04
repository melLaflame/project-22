#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ArbreQuat.h"
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"

int main(int argc,char**argv){
    srand(time(NULL));


    FILE *fic; //fichier pour stocker les donnees
    FILE *fic2; //fichier pour stocker les donnees

    Chaines* new_chaine; //Chaine aléatoire
    Reseau *R; //Resau de la Chaine aléatoire 
    clock_t temps_initial1;
    clock_t temps_final1;
    clock_t temps_initial2;
    clock_t temps_final2;
    clock_t temps_initial3;
    clock_t temps_final3;
    clock_t temps_initial4;
    clock_t temps_final4;
    clock_t temps_initial5;
    clock_t temps_final5;
    double temps_cpu1;
    double temps_cpu2;
    double temps_cpu3;
    double temps_cpu4;
    double temps_cpu5;

    int nbPointsChaine = 100;
    int xmax = 5000;
    int ymax = 5000;

    fic = fopen("graphe_liste_chainee","w");
    if(fic ==NULL){
        printf("le fichier est null\n");
        return 0;
    }

    fic2 = fopen("grahe_liste_hachage_arbre_quat","w");
    if(fic2 ==NULL){
        printf("le fichier est null\n");
        return 0;
    }

    int i = 500;
    int k = 1;

    FILE* fic3 = fopen("test_alea.txt","w");
    new_chaine = generationAleatoire(i,nbPointsChaine,xmax,ymax);
    afficheChaines(new_chaine);
    R = reconstitueReseauListe(new_chaine);
    ecrireReseau(R,fic3);

    while(i<=5000){
        new_chaine = generationAleatoire(i,nbPointsChaine,xmax,ymax);

        temps_initial1 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauListe(new_chaine);
        temps_final1 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu1 = (((double)( temps_final1 - temps_initial1 )) / CLOCKS_PER_SEC);

        temps_initial2 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauHachage(new_chaine,k);
        temps_final2 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu2 = (((double)( temps_final2 - temps_initial2 )) / CLOCKS_PER_SEC);

        temps_initial3 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauArbre(new_chaine);
        temps_final3 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu3 = (((double)( temps_final3 - temps_initial3 )) / CLOCKS_PER_SEC);

        fprintf(fic,"%d %f\n",i*100,temps_cpu1);
        fprintf(fic2,"%d %f %f\n",i*100,temps_cpu2,temps_cpu3);

        i=i+500;
    }


    fic = fopen("algo_hachage_taille.txt","w");
    while(i<=5000){
        new_chaine = generationAleatoire(i,nbPointsChaine,xmax,ymax);

        temps_initial1 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauHachage(new_chaine,2);
        temps_final1 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu1 = (((double)( temps_final1 - temps_initial1 )) / CLOCKS_PER_SEC);
        
        temps_initial2 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauHachage(new_chaine,500);
        temps_final2 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu2 = (((double)( temps_final2 - temps_initial2 )) / CLOCKS_PER_SEC);

        temps_initial3 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauHachage(new_chaine,10000);
        temps_final3 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu3 = (((double)( temps_final3 - temps_initial3 )) / CLOCKS_PER_SEC);

        temps_initial4 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauHachage(new_chaine,25000);
        temps_final4 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu4 = (((double)( temps_final4 - temps_initial4 )) / CLOCKS_PER_SEC);

        temps_initial5 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauHachage(new_chaine,100000);
        temps_final5 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu5 = (((double)( temps_final5 - temps_initial5 )) / CLOCKS_PER_SEC);

        i=i+500;

        detruire_Chaines(new_chaine);
        fprintf(fic,"%d %f %f %f %f %f\n",i*100,temps_cpu1,temps_cpu2,temps_cpu3,temps_cpu4,temps_cpu5);
        detruire_Chaines(new_chaine);
    }

    fclose(fic2);
    fclose(fic);
    return 0;
}