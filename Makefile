CC = gcc
CFLAGS = -Wall -Werror -Wextra
ODIR = obj
SDIR = src
IDIR = include
BDIR = bin
LDIR = lib
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
MODE = GRAPHIQUE

	
ifeq ($(MODE), GRAPHIQUE)
	
OBJS = $(ODIR)/main_G.o $(ODIR)/io_G.o 

final : $(ODIR) $(BDIR) $(OBJS) libjeu.a
	$(CC) -g -o $(BDIR)/final $(OBJS) -I$(LDIR)/ -L$(LDIR)/ -ljeu  $(CPPFLAGS) $(LDFLAGS) 



$(ODIR)/%.o: $(SDIR)/%.c $(IDIR)
	$(CC) -g -c $< -I$(IDIR) $(CPPFLAGS) -o $@ $(LDFLAGS) 

$(ODIR) :
	mkdir $(ODIR)
$(BDIR) :
	mkdir $(BDIR)



endif 


ifeq ($(MODE), TEXTE)

OBJS = $(ODIR)/main.o $(ODIR)/io.o
final : $(ODIR) $(BDIR) $(OBJS) libjeu.a
	$(CC) -g -o $(BDIR)/final $(OBJS) -I$(IDIR) -Ilib/ -Llib/ -ljeu

$(ODIR)/%.o: $(SDIR)/%.c $(IDIR)
	$(CC) -g -c $< -I$(IDIR) -o $@ 

$(ODIR) :
	mkdir $(ODIR)
$(BDIR) :
	mkdir $(BDIR)



endif

libjeu.a : $(LDIR) $(ODIR)/jeu.o $(ODIR)/grille.o
	ar rcs lib/libjeu.a $(ODIR)/jeu.o $(ODIR)/grille.o



$(LDIR) :
	mkdir $(LDIR)

#avec un Doxyfile deja existant afin de generer que la documentation 
docs:
	doxygen Doxyfile

dist: 
	tar -Jcvf JBILOU-GHAIT-GoL-v2.6.tar.xz Doxyfile Makefile src include grilles

clean:
	rm -rf bin && rm -rf obj && rm -rf lib
