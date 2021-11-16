CC = gcc
CFLAGS = -Wall -Werror -Wextra
ODIR = obj
SDIR = src
IDIR = include
BDIR = bin
OBJS = $(ODIR)/main.o $(ODIR)/jeu.o $(ODIR)/io.o $(ODIR)/grille.o

final : $(OBJS)
	$(CC) -o $(BDIR)/final $(OBJS) -I$(IDIR)

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c $(IDIR)
	$(CC) -c $< -I$(IDIR) -o $@ 

#avec un Doxyfile deja existant afin de generer que la documentation 
docs:
	doxygen Doxyfile

dist: 
	tar -Jcvf JBILOU-GHAIT-GoL-v2.6.tar.xz Doxyfile Makefile main.c jeu.c jeu.h io.c io.h grille.c grille.h grilles

clean:
	rm $(BDIR)/final $(ODIR)/*.o