#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Taquin
{
	int tab[3][3]; // tableau du taquin
	int nbposs; // nombre de cases vers lequels un deplacement est possible
	char coupposs[4]; // liste de ces coups possible
	char precedent; // dernier coup effectué
	int coup; // compte le nombre de coup auquel on est
	char coups[1000]; // repertorie tous les coups effectués
};
typedef struct Taquin taquin;


int test_taquin(int tab[3][3]) // Test si une grille est valabe
{
	int test = 0;
	int i,j,k;
	for(k = 0; k < 9; k++)
	{
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if(tab[i][j] == k)
				{
					if(test == 0)
						test = 1;
					else
						return 0;
				}
			}
		}
		test = 0;
	}
	return 1;
}


void initaliser_taquin(int tab[3][3],int deb) // Creer les grilles
{
	if(deb == 0)
		printf("Remplissage de la grille initiale : \n");
	else
		printf("Remplissage de la grille but \n");
	int k = 1;
	int i,j;
	int num;
	int test;
	int compt = 0;
	for(i = 0; i < 3;i++)
	{
		for(j = 0; j < 3; j++)
		{
			num = 10;
			while((num < 0) || (num > 8))
			{
				if(compt == 1)
					printf("Erreur nombre non valide \n");
				compt = 1;
				printf("Numéro dans la case %d :",k);
				scanf("%d",&num);
			}
			tab[i][j] = num;
			k++;
		}
		test = test_taquin(tab);
		if(test == 0)
		{
			printf("Erreur grille invalide \n");
			initaliser_taquin(tab, deb);
		}
	}
}

void deter_voisin(taquin debut, int ligne, int colonne) // determine les deplacement possible
{
	if(ligne == 0)
	{
		if(colonne == 0)
		{
			debut.nbposs = 2;
			debut.coupposs[0] = 'd';
			debut.coupposs[1] = 'b';
		}
		else
		{
			if(colonne == 1)
			{
				debut.nbposs = 3;
				debut.coupposs[0] = 'g';
				debut.coupposs[1] = 'd';
				debut.coupposs[2] = 'b';
			}
			else
			{
				debut.nbposs = 2;
				debut.coupposs[0] = 'g';
				debut.coupposs[1] = 'b';
			}
		}
	}
	else
	{
		if(ligne == 1)
		{
			if(colonne == 0)
			{
				debut.nbposs = 3;
				debut.coupposs[0] = 'h';
				debut.coupposs[1] = 'd';
				debut.coupposs[2] = 'b'; 
			}
			else
			{
				if(colonne == 1)
				{
					debut.nbposs = 4;
					debut.coupposs[0] = 'h';
					debut.coupposs[1] = 'd';
					debut.coupposs[2] = 'b';
					debut.coupposs[3] = 'g';
				}
				else
				{
					debut.nbposs = 3;
					debut.coupposs[0] = 'h';
					debut.coupposs[1] = 'g';
					debut.coupposs[2] = 'b';
				}
			}
		}
		else
		{
			if(colonne == 0)
			{
				debut.nbposs = 2;
				debut.coupposs[0] = 'h';
				debut.coupposs[1] = 'd';
			}
			else
			{
				if(colonne == 1)
				{
					debut.nbposs = 3;
					debut.coupposs[0] = 'g';
					debut.coupposs[1] = 'h';
					debut.coupposs[2] = 'd';
				}
				else
				{
					debut.nbposs = 2;
					debut.coupposs[0] = 'g';
					debut.coupposs[1] = 'h';
				}
			}
		}
	}
}


int compar(int test[3][3], int final[3][3]) // compare si deux grilles sont egales
{
	int i,j;
	int eg = 1;
	for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++)
				if(test[i][j] != final[i][j])
					eg = 0;
	return eg;
}


int deter_gagnant(taquin debut,char direc,int final[3][3],int ligne, int colonne) // determine si l un des coups est gagnant
{
	int i,j;
	int test[3][3];
	for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++)
				test[i][j] = debut.tab[i][j];
	int trouve;
	if(direc == 'h')
	{
		test[ligne][colonne] = test[ligne - 1][colonne];
		test[ligne - 1][colonne] = 0;
		trouve = compar(test,final);
	}
	if(direc == 'b')
	{
		test[ligne][colonne] = test[ligne + 1][colonne];
		test[ligne + 1][colonne] = 0;
		trouve = compar(test,final);
	}
	if(direc == 'g')
	{
		test[ligne][colonne] = test[ligne][colonne - 1];
		test[ligne][colonne - 1] = 0;
		trouve = compar(test,final);
	}
	if(direc == 'd')
	{
		test[ligne][colonne] = test[ligne][colonne + 1];
		test[ligne][colonne + 1] = 0;
		trouve = compar(test,final);
	}
	return trouve;
}




char deter_coup(taquin debut,int trouve, int j, int ligne, int colonne,int bloc) // determine le coup que la machine va effectuer
{

	if(trouve == 1)
	{
		return debut.coupposs[j];
	}
	if(bloc == 1)
	{
		int i;
		char bloca;
		if(debut.precedent == 'g')
			bloca = 'd';
		if(debut.precedent == 'd')
			bloca = 'g';
		if(debut.precedent == 'h')
			bloca = 'b';
		if(debut.precedent == 'b')
			bloca = 'h';
		for(i = 0; i < debut.nbposs; i++)
		{
			if(debut.coupposs[i] == bloca)
			{
				if(i == 0)
					debut.coupposs[i] = debut.coupposs[i + 1];
				else
					debut.coupposs[i] = debut.coupposs[i - 1];
			}
		}
	}
	int x = rand() % debut.nbposs;
	return debut.coupposs[x];
}

int coup(taquin debut, int final[3][3],int bloc) // action a effectuer pour faire un coup
{
	int ligne,colonne;
	int i,j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			if(debut.tab[i][j] == 0)
			{
				ligne = i;
				colonne = j;
			}
	deter_voisin(debut, ligne, colonne);
	int trouve;
	for(i = 0; i < debut.nbposs; i++)
	{
		trouve = deter_gagnant(debut, debut.coupposs[i], final, ligne, colonne);
		if(trouve == 1)
			j = i;
	}
	char coup;
	coup = deter_coup(debut, trouve, j, ligne, colonne, bloc);
	debut.precedent = coup;
	debut.coups[debut.coup] = coup;
	if(coup == 'h')
	{
		debut.tab[ligne][colonne] = debut.tab[ligne - 1][colonne];
		debut.tab[ligne - 1][colonne] = 0;
	}
	if(coup == 'b')
	{
		debut.tab[ligne][colonne] = debut.tab[ligne + 1][colonne];
		debut.tab[ligne + 1][colonne] = 0;
	}
	if(coup == 'g')
	{
		debut.tab[ligne][colonne] = debut.tab[ligne][colonne - 1];
		debut.tab[ligne][colonne - 1] = 0;
	}
	if(coup == 'd')
	{
		debut.tab[ligne][colonne] = debut.tab[ligne][colonne + 1];
		debut.tab[ligne][colonne + 1] = 0;
	}
	return trouve;
}



int main() 
{
	srand(time(NULL));
  taquin debut;
	int utilise[3][3];
	char chemin[1000]; 
	debut.coup = 1000;
	int final[3][3];
	printf("Les grilles sont remplis de la gauche vers la droite, du haut vers la droite.");
	int deb = 0;
	initaliser_taquin(debut.tab, deb);
	deb = 1;
	initaliser_taquin(final, deb);
	int i,j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			utilise[i][j] = debut.tab[i][j];
	printf("Combien de tests voulez vous faire :");
	int test;
	scanf("%d",&test);
	int bloc;
	int limite = 1000;
	int trouve = 0;
	for(i = 0; i < test; i++)
	{
		for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++)
				debut.tab[i][j] = utilise[i][j];
		debut.coup = 0;
		bloc = 0;
		while((trouve == 0) || (debut.coup < limite))
		{
			trouve = coup(debut, final, bloc);
			debut.coup++;
			bloc = 1;
		}
		if(trouve == 1)
		{
			limite = debut.coup;
			int j;
			for(j = 0; j < limite; j++)
			{
				chemin[j] = debut.coups[j];
			}
		}
	}
}
  