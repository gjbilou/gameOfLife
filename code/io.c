/**
 * @file io.c
 * @author JBILOU Ghait (ghait.jbilou@etu.unistra.fr)
 * @brief programme contenant les fonction permettant d'organiser les entres et les sorties du programmes.
 * @version 0.1
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "io.h"
#include "grille.h"
#define NBR 100


/**
 * @brief fonction permettant d'afficher un trait repete selon le nombre de colonne existant
 * 
 * @param c le nombre de colonne (de fois) qu'on va afficher une partie du trait totale
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * @brief fonction permettant d'afficher une ligne, et les cellules vivantes de cette derniere 
 * 
 * @param c le nombre de colonne (de fois) qu'une partie de la ligne va etre repete 
 * @param ligne le tableau qui contient la valeur des cellules de la ligne concerne
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| 0 ");
	printf("|\n");
	return;
}

/**
 * @brief fonction permettant d'afficher la grille dans son entierete en faisant appel aux fonction affiche_trait et affiche_ligne
 * 
 * @param g la grille qu'on va afficher a l'ecran 
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/**
 * @brief fonction permettant d'effacer de l'ecran la grille qu'on vient d'afficher 
 * 
 * @param g la grille a effacer de l'ecran (non modifiable fondamentalement)
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
	system("clear");
}

/**
 * @brief fonction permettant de derouler le jeu et de le faire avancer selon les inputs de l'utilisateur
 * 
 * @param g Pointeur vers la grille principale a afficher et a faire avancer/evoluer
 * @param gc Pointeur vers la grilles secondaire qui sers de copie de la grille g
 */
void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	char tmp;
	while (c != 'q') // touche 'q' pour quitter
	{ 

		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				if (tmp == c)
				{
					evolue(g,gc);
				}
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{ //touche "n" pour donner le nom d'une nouvelle 
			  //grille a afficher
			  	efface_grille(*g);
			  	char * in = (char *) malloc(NBR*sizeof(char));
				scanf(" %s",in);
				libere_grille(g);
				libere_grille(gc);
				init_grille_from_file(in,g);
				alloue_grille(g->nbl,g->nbc,gc);
				affiche_grille(*g);
				free(in);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		tmp = c;
		c = getchar();
		
	}
	return;	
}
