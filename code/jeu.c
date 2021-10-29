/**
 * @file jeu.c
 * @author JBILOU Ghait (ghait.jbilou@etu.unistra.fr)
 * @brief programme permettant de faire evoluer l'etat des grilles a travers le temps
 * @version 0.1
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "jeu.h"

/**
 * @brief fonction permettant de calculer le nombre de cellules vivantes voisines a une cellules donnee/considere
 * 
 * @param i le numero de la ligne ou se trouve notre cellule par rapport a laquelle va se faire le calcule
 * @param j le numero de la colonne ou se trouve notre cellule par rapport a laquelle va se faire le calcule
 * @param g la grille qui contient la cellules donnee 
 * @return int le nombre des cellules voisines vivantes de notre cellules "principale"
 */
int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}
int compte_voisins_vivants_ncy (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc, y = i, z = j;
	//printf("%d g.nbl   --- %d g.nbc",l,c);
	if(i-1 == -1)
	{
		if(j-1 == -1)
		{
			v+=est_vivante(i, j+1, g);
			v+=est_vivante(i+1, j, g);
			v+=est_vivante(i+1, j+1, g);
		}
		else if (j+1 == c)
		{
			v+=est_vivante(i, j-1, g);
			v+=est_vivante(i+1, j-1, g);
			v+=est_vivante(i+1, j, g);
		}
		else
		{
			v+=est_vivante(i, j-1, g);
			v+=est_vivante(i, j+1, g);
			v+=est_vivante(i+1, j, g);
			v+=est_vivante(i+1, j+1, g);
			v+=est_vivante(i+1, j-1, g);	
		}
	}
	else if (i+1 == l)
	{
		if(j-1 == -1)
		{
			v+=est_vivante(i, j+1, g);
			v+=est_vivante(i-1, j, g);
			v+=est_vivante(i-1, j+1, g);
		}
		else if (j+1 == c)
		{
			v+=est_vivante(i, j-1, g);
			v+=est_vivante(i-1, j-1, g);
			v+=est_vivante(i-1, j, g);
		}
		else
		{
			v+=est_vivante(i, j-1, g);
			v+=est_vivante(i, j+1, g);
			v+=est_vivante(i-1, j, g);
			v+=est_vivante(i-1, j+1, g);
			v+=est_vivante(i-1, j-1, g);	
		}
	}
	else
	{
		if(j-1 == -1)
		{
			v+=est_vivante(i, j+1, g);
			v+=est_vivante(i-1, j, g);
			v+=est_vivante(i-1, j+1, g);
			v+=est_vivante(i+1, j, g);
			v+=est_vivante(i+1, j+1, g);
		}
		else if (j+1 == c)
		{
			v+=est_vivante(i, j-1, g);
			v+=est_vivante(i-1, j-1, g);
			v+=est_vivante(i-1, j, g);
			v+=est_vivante(i+1, j-1, g);
			v+=est_vivante(i+1, j, g);
		}
		else
		{
			v = compte_voisins_vivants(i, j, g);
			/*
			v+=est_vivante(i, j-1, g);
			v+=est_vivante(i, j+1, g);
			v+=est_vivante(i-1, j, g);
			v+=est_vivante(i-1, j+1, g);
			v+=est_vivante(i-1, j-1, g);
			v+=est_vivante(i+1, j, g);
			v+=est_vivante(i+1, j+1, g);
			v+=est_vivante(i+1, j-1, g);	
			*/
		}
	}
	return v;
}
int (*pf)(int, int, grille) = &compte_voisins_vivants;

/**
 * @brief fonction permettant de faire evoluer dans le temps les cellules de la grilles 
 * 
 * @param g la grilles principale qui va etre evolue 
 * @param gc la grille secondaire qui servira de copie de la grille g avant evolution
 */
void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			
			v = (*pf)(i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
