all:ChaineMain ReconstitueReseauMain exo6 GrapheMain exo6q1

ChaineMain: ChaineMain.o Chaine.o SVGwriter.o
	gcc ChaineMain.o Chaine.o SVGwriter.o -o ChaineMain -lm

ReconstitueReseauMain: ReconstitueReseauMain.o Reseau.o Chaine.o ArbreQuat.o Hachage.o SVGwriter.o
	gcc ReconstitueReseauMain.o Chaine.o Reseau.o ArbreQuat.o Hachage.o SVGwriter.o -o ReconstitueReseauMain -lm

ArbreQuatMain: ArbreQuatMain.o ArbreQuat.o Reseau.o Chaine.o  SVGwriter.o
	gcc ArbreQuatMain.o ArbreQuat.o Chaine.o Reseau.o  SVGwriter.o -o ArbreQuatMain -lm

GrapheMain: GrapheMain.o Graphe.o Reseau.o Chaine.o Struct_File.o Struct_Liste.o SVGwriter.h
	gcc GrapheMain.o Graphe.o Reseau.o Chaine.o Struct_File.o Struct_Liste.o SVGwriter.o -o GrapheMain -lm

exo6: exo6.o Reseau.o Chaine.o ArbreQuat.o Hachage.o SVGwriter.o
	gcc exo6.o Chaine.o Reseau.o ArbreQuat.o Hachage.o SVGwriter.o -o exo6 -lm

exo6q1: exo6q1.o Reseau.o Chaine.o ArbreQuat.o Hachage.o SVGwriter.o
	gcc exo6q1.o Chaine.o Reseau.o ArbreQuat.o Hachage.o  SVGwriter.o -o exo6q1 -lm

exo7: exo7.o Reseau.o Chaine.o ArbreQuat.o Hachage.o
	gcc exo7.o Chaine.o Reseau.o ArbreQuat.o Hachage.o -o exo7 -lm

Chaine.o: Chaine.c Chaine.h SVGwriter.h
	gcc -c Chaine.c -o Chaine.o -lm 

exo6.o: exo6.c ArbreQuat.h Reseau.h Chaine.h Hachage.h 
	gcc -c exo6.c -o exo6.o

exo6q1.o: exo6q1.c ArbreQuat.h Reseau.h Chaine.h Hachage.h 
	gcc -c exo6q1.c -o exo6q1.o

ArbreQuat.o: ArbreQuat.c ArbreQuat.h Reseau.h Chaine.h
	gcc -c ArbreQuat.c -o ArbreQuat.o

Hachage.o: Hachage.c Hachage.h Reseau.h Chaine.h
	gcc -lm -c Hachage.c -o Hachage.o -lm

ReconstitueReseauMain.o: ReconstitueReseauMain.c Chaine.h Reseau.h ArbreQuat.h Hachage.h SVGwriter.h
	gcc -c ReconstitueReseauMain.c -o ReconstitueReseauMain.o

Struct_File.o: Struct_File.c Struct_File.h
	gcc -c Struct_File.c -o Struct_File.o

Struct_Liste.o: Struct_Liste.c Struct_Liste.h
	gcc -c Struct_Liste.c -o Struct_Liste.o

Reseau.o: Reseau.c Reseau.h Chaine.h SVGwriter.h
	gcc -c Reseau.c -o Reseau.o

Graphe.o: Graphe.c Graphe.h Reseau.h Chaine.h 
	gcc -c Graphe.c -o Graphe.o

GrapheMain.o: GrapheMain.c Graphe.h Reseau.h Chaine.h
	gcc -c GrapheMain.c -o GrapheMain.o

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc -c SVGwriter.c -o SVGwriter.o

ChaineMain.o: ChaineMain.c Chaine.h SVGwriter.h 
	gcc -c ChaineMain.c -o ChaineMain.o -lm

