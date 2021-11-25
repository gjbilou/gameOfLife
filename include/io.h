#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);
void affiche_ligne_G (grille g, int i, int j, cairo_t *cr);

// affichage d'une grille
void affiche_grille (grille g);
void affiche_grille_G(cairo_surface_t *surface,grille g);


void window (grille * g, grille * gc);

// effacement d'une grille
void efface_grille (grille g);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
