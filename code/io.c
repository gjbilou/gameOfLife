#include "io.h"
#include "grille.h"
#define NBR 100


void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| 1 ");
	printf("|\n");
	return;
}

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

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
	system("clear");
}

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
