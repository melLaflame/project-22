#include <stdlib.h>
#include <string.h>
#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include "Hachage.h"


int main(int argc,char**argv){

    if(argc!=3){
        printf("Erreur format: %s <NomFichier.cha> <Numero_methode>\n", argv[0]);
        return 0;
    }


    FILE *fic; 
    FILE *fic2;
    FILE *fic3;
    char *nom_fichier;
    int choix;
    Chaines *instance;
    Reseau *R;
    Reseau *R1;

    if (argc!=3){
        printf("Erreur de format: %s <Fichier.cha> <Numero_methode>\n", argv[0]);
    return 0;
    }

    choix=atoi(argv[2]);
    nom_fichier=strdup(argv[1]);
    fic = fopen(nom_fichier,"r");
    fic3 = fopen("test_ecriture_chaine.txt","w");
    if(!fic){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return 1;
    }
    
    instance=lectureChaine(fic);
    //ecrireChaine(instance,fic3);
    //afficheChaines(instance);
    switch(choix){
        case 1:
            printf("Reconstitution avec liste chainee\n");
            R = reconstitueReseauListe(instance);
            fic2=fopen("reconstitue_reseau_liste_chainee.txt","w");
            if(!fic2){
                printf("Erreur\n");
                return 1;
            }
            ecrireReseau(R,fic2);
            printf("Reseau de l'instance %s reconstitue avec succes\n", nom_fichier); 
            break;
        case 2:
            printf("Reconstitution avec table de Hachage\n");
            R = reconstitueReseauHachage(instance,100);
            fic2=fopen("Reconstitue_reseau_tableHachage.txt","w");
            if(!fic2){
                printf("Erreur\n");
                return 1;
            }
            ecrireReseau(R,fic2);
            printf("Reseau de l'instance %s reconstitue avec succes\n", nom_fichier);
            break;
        case 3:
            printf("Reconstitution avec Arbre Quaternaire\n");
            R = reconstitueReseauArbre(instance);
            //printf("HEYYYYY5555");
            fic2=fopen("Reconstitue_reseau_ArbreQuaternaire.txt","w");
            if(!fic2){
                printf("Erreur\n");
                return 1;
            }
            ecrireReseau(R,fic2);
            printf("Reseau de l'instance %s reconstitue avec succes\n", nom_fichier);
            break;
    }

    detruire_Chaines(instance);
    detruire_reseau(R);
    free(nom_fichier);
    fclose(fic2);
    fclose(fic);

    return 0;
}
