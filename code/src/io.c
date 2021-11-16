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
#define NBR 100
extern int (*pf)(int,int,grille);

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
		//if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ",ligne[i]-1);
		if (ligne[i]==0)
		{
			printf("|   ");
		}
		else if (ligne[i]==-1)
		{
			printf("| X ");
		}
		else
		{
			printf ("| %d ",ligne[i]-1);
		}
	printf("|\n");
	return;
}

/**
 * @brief fonction permettant d'afficher la grille dans son entierete en faisant appel aux fonction affiche_trait et affiche_ligne
 * 
 * @param g la grille qu'on va afficher a l'ecran 
 */
void affiche_grille (grille g){
	if(pf == &compte_voisins_vivants)
	{
		printf("\tGRILLE CYCLIQUE : ON.");
	}
	else
	{
		printf("\tGRILLE CYCLIQUE : OFF.");
	}
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
	char tmp = c;
	int hmt_e = 0;
	pf = &compte_voisins_vivants;
	int v_etat = 0;
	int v_etait_etat = v_etat;
	while (c != 'q') // touche 'q' pour quitter
	{ 

		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				if (v_etat == 1 && v_etat == v_etait_etat && tmp == c)
				{
					for(int i = 0; i < g->nbl; i++)
					{
						for(int j = 0; j< g->nbc; j++)
						{
							if (est_vivante(i, j, *g))
							{
								g->cellules[i][j]++;
							}
						}
					}
				}
				else
				{
					v_etait_etat = v_etat;
				}
				if (tmp == c)
				{
					evolue(g,gc,v_etat);
					hmt_e ++;
				}
				efface_grille(*g);
				printf("NBR EVOLUTIONS : %d.",hmt_e);
				if (v_etat == 1)
				{
					printf("\tVIEILLISSEMENT : ON.");
				}
				else
				{
					printf("\tVIEILLISSEMENT : OFF.");
				}
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{ //touche "n" pour donner le nom d'une nouvelle 
			  //grille a afficher
			  	efface_grille(*g);
				printf("CHEMIN DE LA NOUVELLE GRILLE A AFFICHER : ");
			  	char * in = (char *) malloc(NBR*sizeof(char));
				scanf(" %s",in);
				libere_grille(g);
				libere_grille(gc);
				init_grille_from_file(in,g);
				alloue_grille(g->nbl,g->nbc,gc);
				affiche_grille(*g);
				free(in);
				hmt_e = 0;
				break;
			}
			case 'c' :
			{
				pf = (pf == &compte_voisins_vivants) ? &compte_voisins_vivants_ncy : &compte_voisins_vivants;
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'v' :
			{
				if (v_etat == 0) 
				{
					v_etat = 1;
				}
				else if (v_etat == 1)
				{
					v_etat = 0;
					v_etait_etat = 0;
					for(int i = 0; i < g->nbl; i++)
					{
						for(int j = 0; j< g->nbc; j++)
						{
							if (est_vivante(i, j, *g))
							{
								g->cellules[i][j]=1;
							}
						}
					}					
				}
				efface_grille(*g);
				affiche_grille(*g);
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
