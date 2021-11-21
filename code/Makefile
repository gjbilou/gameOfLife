CC = gcc
CFLAGS = -Wall -Werror -Wextra
ODIR = obj
SDIR = src
IDIR = include
BDIR = bin
OBJS = $(ODIR)/main.o $(ODIR)/jeu.o $(ODIR)/io.o $(ODIR)/grille.o
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11


final : $(OBJS)
	$(CC) -o $(BDIR)/final $(OBJS) $(CPPFLAGS) $(LDFLAGS)

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c $(IDIR)
	$(CC) -c $< $(CPPFLAGS) -o $@ $(LDFLAGS)

#avec un Doxyfile deja existant afin de generer que la documentation 
docs:
	doxygen Doxyfile

dist: 
	tar -Jcvf JBILOU-GHAIT-GoL-v2.6.tar.xz Doxyfile Makefile main.c jeu.c jeu.h io.c io.h grille.c grille.h grilles

clean:
	rm $(BDIR)/final $(ODIR)/*.o