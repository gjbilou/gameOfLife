/**
 * @file main.c
 * @author JBILOU Ghait (ghait.jbilou@etu.unistra.fr)
 * @brief programme principale de notre projet qui va faire appel a l'ensemble des fonctions cree auparavant pour faire fonction le jeu correctement sous mode textuelle
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 * @brief fonction main : il s'agit du point d'entree principale de notre programme et permet 
 * 
 * @param argc le nombre d'arguments passes au programme principale
 * @param argv les arguments passes au programme pricipale
 * @return int 
 */
int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	system("clear");
	
	printf("NBR EVOLUTIONS : 0.");
	printf("\tVIEILLISSEMENT : OFF.");
	affiche_grille(g);
	
	debut_jeu(&g, &gc);
	

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
