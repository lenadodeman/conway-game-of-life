#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Règles : 
	- Pour les espaces où cellules vivantes :
		- Si 1 ou 0 voisins elle meurt
		- Si 4 ou plus voisins elle meurt
		- Si 2 ou 3 voisins elle survit
	
	- Pour les espaces vides :
		- Si 3 voisins elle est peuplée 
*/


/* Fonction qui print les cases du tableau, lorsque la cellule est vivante (1) elle print un 'X' et lorsque la cellule est morte (0) elle print un '.' */

void afficheTab(int taille, int tab[][taille]) /* On prend en argument notre tableau qui sera celui du jeu et sa taille */
{
	int i, j;
	for(i = 0 ; i < taille ; i++)
	{
		for(j = 0 ; j < taille ; j++)
		{
			if(tab[i][j] == 0)
			{
				printf( ". " );
			}
			else
			{
				printf( "X " );
			}
		}
		printf( "\n" );
	}
	printf( "\n" );
}

void jeuSansTorus(int taille, int grille[][taille]) /* Fonction du jeu sans l'univers Torus, elle prend en argument la taille du tableau, et le tableau initialisé dans le main */
{
	int i, j;
	/* Initialisation d'un tableau t+1 qui va se remplir pour avoir l'étape suivante, on l'initialise à 0 */
	int grillePlus1[taille][taille];
	
	for(i = 0 ; i < taille ; i++)
	{
		for(j = 0 ; j < taille ; j++)
		{
			grillePlus1[i][j] = 0;
		}
	}

	
	int compteurDeVies = 0; /* On initialise un compteur de vie à 0, il prend en compte le nombre de voisin et est réinitialisé à chaque début d'itérations pour recommencer pour chaque case */
	
	/* Ici le test des voisins selon l'emplacement de la case courante, on compte le nombre de voisin de la case, on regarde le i et le j pour savoir où est située la case courante et si elle fait partie des cas particuliers des extrémités de notre grille sans torus */
	
	for(i = 0 ; i < taille ; i++)
	{
		for(j = 0 ; j < taille ; j++)
		{
			
			/* Compteur des cases en extremité de la grille, les cas particuliers */
			
			if (i == 0 && j == 0) /* Si la case est celle en haut à gauche */
			{
				compteurDeVies = grille[i][j+1] + grille[i+1][j] + grille[i+1][j+1];
			}
			
			else if (i == taille-1 && j == 0) /* Si la case est celle en bas à gauche */
			{
				compteurDeVies = grille[i-1][j] + grille[i-1][j+1] + grille[i][j+1];
			}
			
			else if (i == 0 && j == taille-1) /* Si la case est celle en haut à droite */
			{
				compteurDeVies = grille[i][j-1] + grille[i+1][j-1] + grille[i+1][j];
			}	
			
			else if (i == taille-1 && j == taille-1) /* Si la case est celle en bas à droite */
			{
				compteurDeVies = grille[i-1][j] + grille[i][j-1] + grille[i-1][j-1];
			}		
			
			else if (i == 0 && j != 0 && j != taille-1) /* Si la case n'est pas un coin mais est sur la première ligne */
			{
				compteurDeVies = grille[i][j-1] + grille [i+1][j-1] + grille[i+1][j] + grille [i+1][j+1] + grille[i][j+1];
			}
			
			else if (j == 0 && i != 0 && i != taille-1) /* Si la case n'est pas un coin et est sur la première colonne */
			{
				compteurDeVies = grille[i-1][j] + grille[i-1][j+1] + grille [i][j+1] + grille[i+1][j+1] + grille [i+1][j];
			}
			
			else if (i == taille-1 && j != 0 && j != taille-1) /* Si la case n'est pas un coin et est sur la dernière ligne */
			{
				compteurDeVies = grille[i][j-1] + grille[i-1][j-1] + grille [i-1][j] + grille[i-1][j+1] + grille [i][j+1];
			}
			
			else if (j == taille-1 && i != 0 && i != taille-1) /* Si la case n'est pas un coin et est sur la dernière colonne */
			{
				compteurDeVies = grille[i-1][j] + grille[i-1][j-1] + grille [i][j-1] + grille[i+1][j-1] + grille [i+1][j];
			}
			else /* Si la case est dans la grille et n'est pas aux bords */
			{
				compteurDeVies = grille[i-1][j-1] + grille[i-1][j] + grille[i-1][j+1] + grille[i][j-1] + grille[i][j+1] + grille[i+1][j-1] + grille[i+1][j] + grille[i+1][j+1];
			}
			
			/* Remplissage tableau t+1, On remplie les cases du tableau de l'étape suivante en fonction du nombre de voisins comptés précédemment et en fonction de la valeur de la case au temps t */
			
			if(grille[i][j] == 1) /* Si la case courante est une cellule vivante, on lui applique les règles de ce cas */
			{
				if(compteurDeVies == 1 || compteurDeVies == 0 || compteurDeVies >= 4) /* Correspond aux règles écrites au début de ce fichier */
				{
					grillePlus1[i][j] = 0; /* Dans ce cas la case suivante sera morte en raison d'un voiinnage sous peuplé ou surpeuplé */
				}
				else if(compteurDeVies == 2 || compteurDeVies == 3)
				{
					grillePlus1[i][j] = 1; /* Dans ce cas la case suivante sera en vie étant donnée un voisinnage adéquat à la survie de la cellule */
				}
			}
	
			if(grille[i][j] == 0) /* Si la case courante est une cellule vide / morte, on lui applique la règle de ce cas aussi */
			{
				if(compteurDeVies == 3)
				{
					grillePlus1[i][j] = 1; /* Dans ce cas, le nouveau tableau aura donc une cellule vivante à cet endroit */
				}
			}
	
		}
	}

	/* Ici on passe les valeurs de la nouvelle grille initialisée au dessus, dans l'ancienne grille qui ne nous est plus utile maintenant. Cela nous permet de refaire le compte pour l'étape suivante */
	
	for (i = 0 ; i < taille ; i++)
        {
            for (j = 0 ; j < taille ; j++)
            {
                grille[i][j] = grillePlus1[i][j];
            }
        }
	
	afficheTab(taille, grille); /* On affiche le tableau obtenu à la fin */
}


void jeuAvecTorus(int taille, int grille[][taille]) /* Fonction du jeu avec Torus, elle prend la taille du tableau et le tableau initialisé dans initTabAvectorus */
{

	int i, j;
	/* Initialisation d'un tableau t+1 qui va se remplir pour avoir l'étape suivante, on l'initialise à 0 */
	int grillePlus1[taille][taille];
	
	for(i = 0 ; i < taille ; i++)
	{
		for( j = 0 ; j < taille ; j++)
		{
			grillePlus1[i][j] = 0;
		}
	}
	
	int compteurDeVies = 0; /* On initialise un compteur de vie à 0, il prend en compte le nombre de voisin et est réinitialisé à chaque début d'itérations pour recommencer pour chaque case */
	
	for(i = 0 ; i < taille ; i++) /* Ici on fait les mêmes tests que pour l'univers sans torus, seulement le nombre de voisin à regarder sera supérieur */
	{
		for(j = 0 ; j < taille ; j++)
		{
			
			/* Compteur des cases en extremité de la grille, les cas particuliers */
			
			if (i == 0 && j == 0) /* Si la case est celle en haut à gauche */
			{
				compteurDeVies = grille[i][j+1] + grille[i+1][j] + grille[i+1][j+1] + grille[taille-1][j] + grille[taille-1][j+1] + grille[i][taille-1] + grille[i+1][taille-1] + grille[taille-1][taille-1];
			}
			
			else if (i == taille-1 && j == 0) /* Si la case est celle en bas à gauche */
			{
				compteurDeVies = grille[i-1][j] + grille[i-1][j+1] + grille[i][j+1] + grille[0][0] + grille[0][j+1] + grille[taille-1][taille-1] + grille[taille-2][taille-1] + grille[0][taille-1];
			}
			
			else if (i == 0 && j == taille-1) /* Si la case est celle en haut à droite */
			{
				compteurDeVies = grille[i][j-1] + grille[i+1][j-1] + grille[i+1][j] + grille[taille-1][taille-1] + grille[taille-1][taille-2] + grille[i][0] + grille[i+1][0] + grille[taille-1][0];
			}	
			
			else if (i == taille-1 && j == taille-1) /* Si la case est celle en bas à droite */
			{
				compteurDeVies = grille[i-1][j] + grille[i][j-1] + grille[i-1][j-1] + grille[taille-1][0] + grille[taille-2][0] + grille[0][taille-1] + grille[0][taille-2] + grille[0][0];
			}		
			
			else if (i == 0 && j != 0 && j != taille-1) /* Si la case n'est pas un coin mais est sur la première ligne */
			{
				compteurDeVies = grille[i][j-1] + grille [i+1][j-1] + grille[i+1][j] + grille [i+1][j+1] + grille[i][j+1] + grille[taille-1][j] + grille[taille-1][j-1] + grille[taille-1][j+1];
			}
			
			else if (j == 0 && i != 0 && i != taille-1) /* Si la case n'est pas un coin et est sur la première colonne */
			{
				compteurDeVies = grille[i-1][j] + grille[i-1][j+1] + grille [i][j+1] + grille[i+1][j+1] + grille [i+1][j] + grille[i][taille-1] + grille[i+1][taille-1] + grille[i-1][taille-1];
			}
			
			else if (i == taille-1 && j != 0 && j != taille-1) /* Si la case n'est pas un coin et est sur la dernière ligne */
			{
				compteurDeVies = grille[i][j-1] + grille[i-1][j-1] + grille [i-1][j] + grille[i-1][j+1] + grille [i][j+1] + grille[0][j] + grille[0][j-1] + grille[0][j+1];
			}
			
			else if (j == taille-1 && i != 0 && i != taille-1) /* Si la case n'est pas un coin et est sur la dernière colonne */
			{
				compteurDeVies = grille[i-1][j] + grille[i-1][j-1] + grille [i][j-1] + grille[i+1][j-1] + grille [i+1][j] + grille[i][0] + grille[i+1][0] + grille[i-1][0];
			}
			else /* Si la case est dans la grille est pas aux bords */
			{
				compteurDeVies = grille[i-1][j-1] + grille[i-1][j] + grille[i-1][j+1] + grille[i][j-1] + grille[i][j+1] + grille[i+1][j-1] + grille[i+1][j] + grille[i+1][j+1];
			}
			
			/* Remplissage tableau t+1 comme pour le jeu sans torus */
			
			if(grille[i][j] == 1)
			{
				if(compteurDeVies == 1 || compteurDeVies == 0 || compteurDeVies >= 4)
				{
					grillePlus1[i][j] = 0;
				}
				else if(compteurDeVies == 2 || compteurDeVies == 3)
				{
					grillePlus1[i][j] = 1;
				}
			}
	
			if(grille[i][j] == 0)
			{
				if(compteurDeVies == 3)
				{
					grillePlus1[i][j] = 1;
				}
			}
		}
	}
	
	/* On échange les tableaux comme pour le jeu sans torus */
	
	for (i = 0 ; i < taille ; i++)
        {
            for (j = 0 ; j < taille ; j++)
            {
                grille[i][j] = grillePlus1[i][j];
            }
        }
	
	afficheTab(taille, grille); /* On affiche le tableau à la fin de l'étape */

}



/* Fonctions pour réaliser les jeux à un nombre d'étapes voulues */

void iterationsTorus(int taille, int grille[][taille], int iterations) /* Elle prend en arguments la taille du tableau, le tableau utilisé puis le nombre d'itérations voulues */
{
	int i;
	
	for(i = 0 ; i < iterations ; i++) 
	{
		jeuAvecTorus(taille, grille); /* La fonction qui réalise le jeu, et sera donc répétée un nombre i de fois */
	}
}

void iterationsSansTorus(int taille, int grille[][taille], int iterations) /* Elle prend en arguments la taille du tableau, le tableau utilisé puis le nombre d'itérations voulues */
{
	int i;
	
	for(i = 0 ; i < iterations ; i++) /* Pour le jeu sans torus il suffit de répéter directement notre jeu à un nombre i d'étapes car le glider est initalisé dans le main */
	{
		jeuSansTorus(taille, grille); 
	}
}


void initTabAvecTorus(int taille, int iterations) /* Cette fonction initialise un tableau aléatoire pour le jeu avec torus, elle lance ensuite le jeu */
{
	srand( time( NULL ) ); /* On initialise pour la fonction rand() */
	int i, j;
	int tab[taille][taille]; /* On initialise le tableau qui sera initialisé et utilisé pour le reste du jeu */
	
	for(i = 0 ; i < taille ; i++)
	{
		for(j = 0 ; j < taille ; j++)
		{
			tab[i][j] = rand() %2; /* Les cases du tableau auront ainsi soit la valeur 0, soit la valeur 1 */
		}
	}
	
	printf("Votre grille de départ :\n\n"); /* On print notre tableau pour voir avec quoi on commence notre jeu */
	afficheTab(taille, tab);
	
	printf("Réalisation du jeu de la vie :\n\n"); /* Ensuite avec la fonctions iterationsTorus, on fait le jeu au nombre d'étape voulu, et le print du tableau se fait dans la fonction jeuAvectorus */
	iterationsTorus(taille, tab, iterations); /* Ici le jeu sera réalise au nombre i de fois que la fonction iterationsTorus sera utilisée */
}



int main()
{

	int taille = 0; /* On initialise un entier taille à 0 qui nous servira pour savoir la taille de la grille voulue par l'utilisateur */
	int nbIterations = 0; /* De même pour le nombre d'itérations */
	int choix; /* Un entier choix qui nous servira pour notre menu */
	int i, j;
	
	printf("Pour voir le glider du sujet tapez 1.\nPour voir le jeu avec Torus tapez 2.\n"); /* Ici on demande à l'utilisateur ce qu'il veut voir selon les nécéssités du sujet de TP */
	scanf("%d", &choix); /* On scan le choix de l'utilisateur */
	
	if(choix == 1) /* Si l'utilisateur veut voir la grille initialisée avec le glider */
	{
		printf("Quelle taille voulez-vous pour la grille du jeu ? Il est conseillé de prendre une taille = 10 pour le glider du sujet.\n");
		scanf("%d", &taille); /* On scan la taille voulue par l'utilisateur */
		
		int grilleJeu[taille][taille]; /* On ititialise une grille du jeu à 0 afin de pouvoir ensuite y mettre le glider */
		
		for(i = 0 ; i < taille ; i++)
		{
			for(j = 0 ; j < taille ; j++)
			{
				grilleJeu[i][j] = 0;
			}
		}
		
		/* Initialisation glider du sujet dans la grille */
		
		grilleJeu[1][1] = 1;
		grilleJeu[2][2] = 1;
		grilleJeu[3][0] = 1;
		grilleJeu[3][1] = 1;
		grilleJeu[3][2] = 1;
		
		printf("Combien voulez-vous faire d'itérations ?\n");
		scanf("%d", &nbIterations); /* Ici on utilise l'entier nbIterations afin de réaliser le jeu autant de fois que voulu */
			
		/* Réalisation du jeu */
		
		printf("Votre grille de départ :\n\n");
		afficheTab(taille,grilleJeu);
		
		printf("L'évolution de la grille :\n\n");
		iterationsSansTorus(taille, grilleJeu, nbIterations); /* On utilise la fonction iterationsSansTorus pour montrer toutes les étapes voulues */
	}
		
	else if(choix == 2) /* Si l'utilisateur veut voir un comportement aléatoire dans un monde avec torus */
	{
		printf("Quelle taille voulez-vous pour la grille du jeu ?\n");
		scanf("%d", &taille);
		
		printf("Combien voulez-vous faire d'itérations ?\n");
		scanf("%d", &nbIterations);
		initTabAvecTorus(taille, nbIterations); /* On a seulement besoin de cette fonction ici sans tableau car l'initialisation se fait dans initTabAvecTorus */
	}

	else /* Dans le cas où l'utilisateur a entré un chiffre autre que 1 ou 2 */
	{
		printf("Vous n'avez pas entré un bon numéro pour votre choix.\n");
	}	
	
return 0;

}

