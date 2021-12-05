/**
 * @file grille.c
 * @author JBILOU Ghait (ghait.jbilou@etu.unistra.fr)
 * @brief programme permettant la creation de grille, qui est la structure principale de notre projet, grace a la fonction alloue grille et la liberation de cette derniere apres l'avoir utilise.
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "grille.h"

/**
 * @brief fonction permettant de allouer dynamiquement l'espace necessaire pour notre structre grille 
 * 
 * @param l le nombre de lignes (de tableaux) du tableau 2D cellules de notre structure grille
 * @param c le nombre de colonnes (d'elements) des tableaux 1D qui constituent le tableau 2D cellules de notre structure grille
 * @param g Pointeur sur la grille qu'on veut allouer dynamiquement et initialiser a 0, et qui a ete declare auparavant
 */
void alloue_grille (int l, int c, grille* g)
{
	g -> nbl = l;
	g -> nbc = c;
	g -> cellules = (int **) calloc(g -> nbl , sizeof(int *));
	for (int i = 0; i < g -> nbl; i ++)
	{
		g -> cellules [i] = (int *) calloc(g -> nbc, sizeof(int));
	}
}


/**
 * @brief permet de liberer l'espace utilise pour cree le tableau 2D cellules de notre structure grille 
 * 
 * @param g Pointeur vers la grille pour laquelle on doit liberer l'espace alloue en memoire auparavant
 */
void libere_grille (grille* g)
{
	for (int i = g -> nbl; i != 0; i--)
	{
		free(g -> cellules [i]);
	}
	free(g -> cellules);
}

/**
 * @brief permet d'initialise une grille declare auparavant a partir d'un fichier passe en argument au programme principale lors de son execution
 * 
 * @param filename le chemin du fichier permettant d'initialiser les valeurs de notre strucutre grille
 * @param g Pointeur vers la grille, qui a ete declare au paravant, et qu'on va initialiser
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0,n_viables=0,m;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	fscanf(pfile, "%d", & n_viables);
	for(m=0; m<n_viables; ++m)
	{
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}
	
	fclose (pfile);
	return;
}


/**
 * @brief permet de copier le contenu du tableau 2D cellules de la grille gs et le mettre dans le tableau 2D cellules de la grille gd 
 * 
 * @param gs la grille a partie de laquelle on va copier 
 * @param gd la grille qui va recevoir la copie
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
