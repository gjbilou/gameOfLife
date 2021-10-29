final: main.o jeu.o io.o grille.o
	gcc -o final main.o jeu.o io.o grille.o

main.o: main.c grille.h io.h jeu.h
	gcc -c main.c

jeu.o: jeu.c jeu.h grille.h
	gcc -c jeu.c

io.o: io.c grille.h jeu.h
	gcc -c io.c

grille.o: grille.c grille.h
	gcc -c grille.c


dist: Doxyfile Makefile main.c jeu.c io.c grille.c grilles
	tar -Jcvf JBILOU-GHAIT-GoL-v2.8.tar.xz Doxyfile Makefile main.c jeu.c jeu.h io.c io.h grille.c grille.h grilles
clean:
	rm final *.o