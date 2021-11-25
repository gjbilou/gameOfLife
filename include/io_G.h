#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"

void affiche_ligne_G (grille g, int i, int j, cairo_t *cr);


void affiche_grille_G(cairo_surface_t *surface,grille g);


void window_g (grille * g, grille * gc);

#endif
