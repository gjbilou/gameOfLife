final: main.o jeu.o io.o grille.o
	gcc -o final main.o jeu.o io.o grille.o

main.o: main.c grille.h io.h jeu.h
	gcc -c main.c

jeu.o: jeu.c jeu.h
	gcc -c jeu.c

io.o: io.c grille.h
	gcc -c io.c
	
grille.o: grille.c grille.h
	gcc -c grille.c

clean:
	rm final *.o