CC = gcc
CFLAGS = -Wall -Werror -Wextra
ODIR = obj
SDIR = src
IDIR = include
BDIR = bin
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
MODE = GRAPHIQUE
ifeq ($(MODE), GRAPHIQUE)

OBJS = $(ODIR)/main_G.o $(ODIR)/jeu.o $(ODIR)/io_G.o $(ODIR)/grille.o

final : $(OBJS)
	$(CC) -g -o $(BDIR)/final $(OBJS) -I$(IDIR) $(CPPFLAGS) $(LDFLAGS) 

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c $(IDIR)
	$(CC) -g -c $< -I$(IDIR) $(CPPFLAGS) -o $@ $(LDFLAGS) 

endif 


ifeq ($(MODE), TEXTE)

OBJS = $(ODIR)/main.o $(ODIR)/jeu.o $(ODIR)/io.o $(ODIR)/grille.o
final : $(OBJS)
	$(CC) -o $(BDIR)/final $(OBJS) -I$(IDIR)

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c $(IDIR)
	$(CC) -c $< -I$(IDIR) -o $@ 

endif


#avec un Doxyfile deja existant afin de generer que la documentation 
docs:
	doxygen Doxyfile

dist: 
	tar -Jcvf JBILOU-GHAIT-GoL-v2.6.tar.xz Doxyfile Makefile main.c jeu.c jeu.h io.c io.h grille.c grille.h grilles

clean:
	rm $(BDIR)/final $(ODIR)/*.o
