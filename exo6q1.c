#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ArbreQuat.h"
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"

int main(int argc,char**argv){
    srand(time(NULL));
    
    FILE *fic; 
    char *nom_fichier;

    clock_t temps_initial1 ;
    clock_t temps_final1 ;
    double temps_cpu1 ;

    clock_t temps_initial2 ;
    clock_t temps_final2 ;
    double temps_cpu2 ;


    clock_t temps_initial3 ;
    clock_t temps_final3 ;
    double temps_cpu3 ;

    Chaines *instance;
    Reseau *R;

    if (argc!=2){
        printf("Erreur de format: %s <Fichier.cha>\n", argv[0]);
    return 0;
    }
    
    nom_fichier=strdup(argv[1]);
    fic = fopen(nom_fichier,"r");
    FILE* fic2 = fopen("test_reconstituion.txt","w");
    instance=lectureChaine(fic);
    
    temps_initial1 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
    R = reconstitueReseauListe(instance);
    temps_final1 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
    temps_cpu1 = (((double)( temps_final1 - temps_initial1 )) / CLOCKS_PER_SEC);
    fprintf(fic2,"tps execution liste: %f\n",temps_cpu1);


    for(int i = 1;i<=100;i++){
        temps_initial2 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        R = reconstitueReseauHachage(instance,i);
        temps_final2 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
        temps_cpu2 = ((( double ) ( temps_final2 - temps_initial2 ) ) / CLOCKS_PER_SEC);
        fprintf(fic2,"tps execution hachage i:%d :%f\n",i,temps_cpu2);
    }

    temps_initial3 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
    R = reconstitueReseauArbre(instance);
    temps_final3 = clock (); //Nombre de ‘‘ticks’’ consomm’es par le programme jusqu’ici
    temps_cpu3 = ((( double ) ( temps_final3 - temps_initial3 ) ) / CLOCKS_PER_SEC);
    fprintf(fic2,"tps d'execution arbre: %f",temps_cpu3);

    detruire_reseau(R);
    detruire_Chaines(instance);
    fclose(fic);
    fclose(fic2);
    return 0;
}
