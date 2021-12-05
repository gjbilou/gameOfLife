/**
 * @file io_G.c
 * @author JBILOU Ghait (ghait.jbilou@etu.unistra.fr)
 * @brief programme prennant en charge l'organisation des entrees et sorties du programme en mode Graphique (avec la librairie Cairo)
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "io_G.h"
#define NBR 100
#define SIZEX 1000
#define SIZEY 1000
extern int (*pf)(int, int, grille);

/**
 * @brief fonction permettant d'afficher le contenu de chaque case d'une grille donnee
 * 
 * @param g la grille dont le contenu (les cellules) vont etre affichees
 * @param i l'abscisse de la cellule en question 
 * @param j l'ordonnee de la cellule a afficher
 * @param cr un pointeur cairo_t qui va nous permettre d'afficher une chaine de caractere sur la surface qu'on a cree
 */
void affiche_ligne_G (grille g, int i, int j, cairo_t *cr)
{
	cairo_select_font_face(cr, "Purisa",
      		CAIRO_FONT_SLANT_NORMAL,
      		CAIRO_FONT_WEIGHT_NORMAL);
  	cairo_set_font_size(cr, 40);
	char v [2];
	//if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ",ligne[i]-1);
	if (g.cellules[i][j]==0)
	{
		cairo_show_text(cr," ");
	}
	else if (g.cellules[i][j]==-1)
	{
		cairo_show_text(cr,"X");
	}
	else
	{
		sprintf(v, "%d", g.cellules[i][j]-1);		
		cairo_show_text(cr,v);
	}
	return;
}

/**
 * @brief fonction permettant d'afficher la grille en mode graphique
 * 
 * @param surface un pointeur de type cairo_surface_t permettant de faire bouger le point d'origine des rectangles (qui constituent la base de la grille a concevoir)
 * @param g la grille qu'on va afficher
 */
void affiche_grille_G(cairo_surface_t *surface,grille g)
{

	cairo_t *cr;
	cr=cairo_create(surface);
	
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	for(int i = 0; i<g.nbl; i++)
	{
		for (int j = 0; j<g.nbc; j++)
		{
			/*
			cairo_rectangle(cr , j*((int)(SIZEX*2/3)/g.nbl), i * ((int)(SIZEY*2/3)/g.nbc) ,((SIZEX*2/3)/g.nbl), ((SIZEY*2/3)/g.nbc)  );
			*/
			cairo_rectangle(cr , j*((SIZEX)/g.nbc), i*((SIZEY*2/3)/g.nbl), ((SIZEX)/g.nbc), ((SIZEY*2/3)/g.nbl));
			cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
			cairo_stroke(cr);
			
			//cairo_move_to(cr, j*res+res1/3, i*res2+res2*3/4);
			cairo_move_to(cr, j * ((SIZEX)/g.nbc)+((SIZEX)/g.nbc)*1/3, i * ((SIZEY*2/3)/g.nbl) + ((SIZEY*2/3)/g.nbl)*2.5/3);
			affiche_ligne_G(g,i,j,cr);
			
		}
	}
	return ;
}


/**
 * @brief fonction permettant d'afficher un tableau de controle des differentes options du jeu
 * 
 * @param surface un pointeur de type cairo_surface_t permettant d'afficher les differents elements du tableau de bord 
 * @param hmt_e un iterateur gardant en compte le nombre de generations/evolutions qui sont passee
 * @param v_etat une variable indiquant l'etat du vieillissement
 * @param c_etat une variable indiquant l'etat de la grille 
 * @param oslt une variable qui indique l'oscillation d'un motif de grille donee
 * @param oslt_etat une variable indiquant l'etat de l'oscillation 
 */
void affiche_etat_V_C(cairo_surface_t * surface,int hmt_e,  int v_etat, int c_etat, int oslt, int oslt_etat)
{
	cairo_t * cr; 
	cr = cairo_create(surface);
	char tab_hmt_e[50];
	sprintf(tab_hmt_e, "Nbr de Generations : %d", hmt_e);
	char tab_oslt [50];


	cairo_rectangle(cr, 0, SIZEY*2/3, SIZEX, SIZEY*1/3);
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	// a modifier les couleurs par la suite
	cairo_stroke(cr);

	cairo_select_font_face(cr, "Pursia", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 40);

	cairo_move_to(cr, SIZEX*2.25/6, SIZEY*6.375/9);
	cairo_set_source_rgb (cr, 0.0, 0.5, 1.0);
	cairo_show_text(cr, "Control Panel");
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_set_font_size(cr, 30);


	cairo_move_to(cr, SIZEX*0.2/6, SIZEY*7/9);
	cairo_show_text(cr, tab_hmt_e);

	cairo_move_to(cr, SIZEX*3.5/6, SIZEY*7/9);
	cairo_show_text(cr, "Charger une grille  (n)");

	cairo_move_to(cr, SIZEX*0.25/6, SIZEY*7.625/9);
	if (v_etat == 1)
	{	
		cairo_set_source_rgb (cr, 0.5, 1.0, 0.0);
		cairo_show_text(cr, "Vieillissement (v)    : ON");
	}
	else if (v_etat == 0)
	{
		cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
		cairo_show_text(cr, "Vieillissement (v)    : OFF");
	}
	
	cairo_move_to(cr, SIZEX*3.5/6, SIZEY*7.625/9);
	if (c_etat == 1)
	{
		cairo_set_source_rgb (cr, 0.5, 1.0, 0.0);
		cairo_show_text(cr, "Grille Cyclique (c) : ON" );
	}
	else if (c_etat == 0)
	{
		cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
		cairo_show_text(cr, "Grille Cyclique (c) : OFF" );
	}

	cairo_move_to(cr, SIZEX*1/3, SIZEY*8.375/9);
	if(oslt_etat == 0)
	{
		cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
		cairo_show_text(cr, "Oscillation (o) : OFF");
	}
	else if(oslt_etat == 1)
	{
		cairo_set_source_rgb (cr, 0.5, 1.0, 0.0);
		sprintf(tab_oslt, "Oscillation (o) : %d", oslt);
		cairo_show_text(cr, tab_oslt);
	}
	return ;
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
 * @brief fonction permettant de derouler le jeu (en mode graphique) et de le faire avancer selon les inputs de l'utilisateur
 * 
 * @param g Pointeur vers la grille principale a afficher et a faire avancer/evoluer
 * @param gc Pointeur vers la grilles secondaire qui sers de copie de la grille g
 */
void window_g (grille * g, grille * gc)
{
	// X11 display variables
	Display * disp;
	Window window;
	XEvent event;
	int indxScr;
	
	//cairo display decorations variables
	cairo_surface_t * cs;

	//evolution/grilles variables qui permettent de controler
	//le vieillissement , le  nbre d'evolutions et la grille cyclique
	int hmt_e = 0;
	int c_etat = 1;
	int v_etat = 0;
	int oslt = 0;
	int oslt_etat = 0;

	


	disp = XOpenDisplay(NULL);
	if (disp == NULL)
	{
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	indxScr = DefaultScreen(disp);


	window = XCreateSimpleWindow(disp, RootWindow(disp, indxScr), 1, 1, SIZEX, SIZEY, 0, BlackPixel(disp, indxScr), BlackPixel(disp, indxScr) );

	XStoreName(disp, window, "Jeu de la Vie");

	cs = cairo_xlib_surface_create(disp, window, DefaultVisual(disp, 0), SIZEX, SIZEY);

	XSelectInput(disp, window, KeyPressMask | ButtonPressMask | ExposureMask);

	XMapWindow(disp, window);

	while(1)
	{
		XNextEvent(disp, &event);

		if (event.type == Expose && event.xexpose.count<1)
		{
			affiche_grille_G(cs, *g);
			affiche_etat_V_C(cs, hmt_e, v_etat, c_etat, oslt, oslt_etat);
		}
		else if (event.type == ButtonPress)
		{
			if(event.xbutton.button == 1)
			{
				if (v_etat == 1)
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
				evolue(g, gc, v_etat);
				hmt_e++;
				affiche_grille_G(cs, *g);
				affiche_etat_V_C(cs, hmt_e, v_etat,c_etat, oslt, oslt_etat);
				//need to write affiche nb evolutions
				//need to write affiche etat de vieillissement 
			}
			else if (event.xbutton.button == 3)
			{
				break;
			}
		}
		else if (event.type == KeyPress)
		{
			if (event.xkey.keycode == 0x36) // la touche c
			{
				if (pf == &compte_voisins_vivants)
				{
					pf = &compte_voisins_vivants_ncy;
					c_etat = 0;
				}
				else if (pf == &compte_voisins_vivants_ncy)
				{
					pf = &compte_voisins_vivants;
					c_etat = 1;
				}
				affiche_grille_G(cs, *g);
				affiche_etat_V_C(cs, hmt_e, v_etat, c_etat, oslt, oslt_etat);
				//afficher l'etat cyclique ou pas 
			}
			else if (event.xkey.keycode == 0x37) // la touche v
			{
				if (v_etat == 0) 
				{
					v_etat = 1;
					affiche_grille_G(cs, *g);
					affiche_etat_V_C(cs, hmt_e, v_etat, c_etat, oslt, oslt_etat);
				}
				else if (v_etat == 1)
				{
					v_etat = 0;
					for(int i = 0; i < g->nbl; i++)
					{
						for(int j = 0; j< g->nbc; j++)
						{
							if (est_vivante(i, j, *g))
							{
								g->cellules[i][j] = 1;
							}
						}
					}
					affiche_grille_G(cs, *g);	
					affiche_etat_V_C(cs, hmt_e, v_etat, c_etat, oslt, oslt_etat);				
				}
			}
			else if (event.xkey.keycode == 0x39) // la touche n
			{
				printf("CHEMIN DE LA NOUVELLE GRILLE A AFFICHER : ");
			  	char * in = (char *) malloc(NBR*sizeof(char));
				scanf(" %s",in);
				libere_grille(g);
				libere_grille(gc);
				init_grille_from_file(in,g);
				alloue_grille(g->nbl,g->nbc,gc);
				hmt_e = 0;
				affiche_grille_G(cs, *g);	
				affiche_etat_V_C(cs, hmt_e, v_etat, c_etat, oslt, oslt_etat);
				free(in);

			}
			else if (event.xkey.keycode == 0x20) // la touche o
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
				affiche_grille_G(cs, *g);
				affiche_etat_V_C(cs, hmt_e, v_etat, c_etat, oslt, oslt_etat);

			}
		}
	}

	cairo_surface_destroy(cs);
	XCloseDisplay(disp);
}


 