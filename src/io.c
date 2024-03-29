/**
 * @file io.c
 * @author JBILOU Ghait (ghait.jbilou@etu.unistra.fr)
 * @brief programme contenant les fonction permettant d'organiser les entres et les sorties du programmes.
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "io.h"
#define NBR 100
#define SIZEX 1000
#define SIZEY 1000
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
 * @brief fonction permettant de comparer entre deux grilles et renvoie 1 si elle sont similaire et 0 sinon 
 * 
 * @param g la grille d'origine (a laquelle va se faire la comparaison)
 * @param g1 la grille changeante (qui va nous servir par la suite pour l'oscillation) qui va etre compare a la grille g
 * @return int permet de retourner 1 si les deux grilles sont similaires et les 0 si les deux grilles ne le sont pas 
 */

int grille_egale (grille g, grille g1)
{
	for(int i = 0; i < g.nbl; i++)
	{
		for(int j = 0; j < g.nbc; j++)
		{
			if(g.cellules[i][j] != g1.cellules[i][j])
			{
				return 0;
			}
		} 	
	}
	return 1;
}


/**
 * @brief fonction permettant de determiner si un motif (une grille) peut osciller ou pas
 * 
 * @param g grille par rapport a laquelle l'oscillation va etre determine
 * @param gc copie de la grille g (essentiel pour la fonction evolution)
 * @param vieillissement l'etat du vieillissement (essentiel pour la fonction evolution)
 * @return int l'oscillation (nbrs d'evolutions) avant que le motif de la grille g ne se repete
 */

int est_oscillante(grille *g, grille *gc, int vieillissement)
{
	grille g1, gc1;
	alloue_grille(g->nbl, g->nbc, &g1);
	alloue_grille(gc->nbl, gc->nbc, &gc1);
	copie_grille(*g, g1);
	copie_grille(*gc, gc1);
	int i;
	for(i = 1; i<101; i++)
	{
		evolue(&g1, &gc1, vieillissement);
		if (grille_egale(*g, g1) == 1)
		{
			return i;
		}
	}
	
	i = 0;
	return i;
	
	
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
	int oslt = 0;
	int oslt_etat = 0;
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
				if (oslt_etat == 0)
				{
					printf("\tOSCILLATION : OFF.");
				}
				else if (oslt_etat == 1)
				{
					printf("\tOSCILLATION : %d  ", oslt);
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
			
			case 'o' :
			{
				if(oslt_etat == 0)
				{
					oslt_etat = 1;
					oslt = est_oscillante(g, gc, v_etat);
					
				}
				else if(oslt_etat == 1)
				{
					oslt_etat = 0;
					oslt = 0;
				}


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
