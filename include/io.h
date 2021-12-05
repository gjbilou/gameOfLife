#ifndef __IO_H
#define __IO_H

#include <stdio.h>

#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);


// affichage d'une grille
void affiche_grille (grille g);



void window (grille * g, grille * gc);

// effacement d'une grille
void efface_grille (grille g);

int grille_egale (grille g, grille g1);

int est_oscillante(grille *g, grille *gc, int vieillissement);
// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
