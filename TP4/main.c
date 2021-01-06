#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "main.h"
#include <string.h>
#include <assert.h>

int main(){

	char matrice[DIM1][DIM2];
	int xd, yd, xa, ya;
	unsigned int rand_seed;

	rand_seed = time(0);   // current time
	printf("random seed = %u", rand_seed);
	srand(rand_seed);

	initialise(matrice, DIM1,40);
	affiche(matrice, DIM1);

	departArrivee(matrice, DIM1, &xd, &yd, &xa, &ya);
	affiche(matrice, DIM1);

	//printf(" xd = %d, yd = %d, xa = %d, ya = %d\n", xd, yd, xa, ya);

	// etape(matrice, DIM1, 'D');
	// affiche(matrice, DIM1);
	int bool = expansion(matrice, DIM1, xd, yd, xa, ya);
	printf("\nIl y a un chemin ? %d\n", bool);

	if(bool == 1){
		chemin(matrice, DIM1, xa, ya);
	    affiche(matrice, DIM1);
	}

	return 0;
}


void affiche(char mat[][DIM2], int dim1){
	int i, j;
	// On parcours le tableau et on affiche le bon caractère en fonction de ce qu'on trouve
	for(i = 0; i < dim1; i++){
		for(j = 0; j < DIM2; j++){
			switch (mat[i][j]) {
			case 0 :
				printf("   ");
				break;
			case -1 :
				printf(" # ");
				break;
			case 'D':
				printf(" %c ", mat[i][j]);
				break;
			case 'A':
				printf(" %c ", mat[i][j]);
				break;
			case '*':
				printf(" %c ", mat[i][j]);
				break;
			default:
				if(mat[i][j] >= 10){
					printf("%d ", mat[i][j]);
				}
				else{
					printf(" %d ", mat[i][j]);
				}
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

int random_number(int min, int  max)
{
	// limits are included in the range
	unsigned int rand_range = max + 1 - min;

	// assert() exits the program if the condition is not verified
	assert(rand_range > 0);

	return (rand() % rand_range) + min;
}

void initialise(char mat[][DIM2], int dim1, double p){
	int i, j, random, compteur = 0;
	// On fait la première et la dernière ligne de la matrice
	for(j = 0; j < DIM2; j++){
		mat[0][j] = -1;
		mat[dim1-1][j] = -1;
	}
	// On remplis la première et la dernière colonne
	for(i = 1; i < dim1-1; i++){
		mat[i][0] = -1;
		mat[i][DIM2-1] = -1;
	}
	// On remplit le centre de 0
	for(i = 1; i < dim1-1; i++){
		for(j = 1; j < DIM2-1; j++){
			// On vérifie la probas
			random = random_number(MIN_RAND, MAX_RAND);
			// Si on tombe en dessous
			if(random <= p){
				// On place un obstacle et on incrémente le compteur d'obstacle
				mat[i][j] = -1;
				compteur++;
			}else{
				// Sinon rien
				mat[i][j] = 0;
			}
		}
	}
	// Test du nombre d'obstacle
	int marge_min = ((p-7.5) / 100) * (DIM1-1) * (DIM2-1);
	int marge_max = ((p+7.5) / 100) * (DIM1-1) * (DIM2-1);
	printf("nb obstacles min = %d, nb max = %d et nb obstacles reels = %d \n",marge_min, marge_max ,compteur);
	assert((marge_min <= compteur) && (compteur <= marge_max));
}

void departArrivee(char mat[][DIM2], int dim1, int* xd, int* yd, int* xa, int* ya){
	// Tirage de nombre aléatoire pour placer A et D
	int depart = random_number(1, DIM2-2);
	int arrivee = random_number(1, DIM2-2);

	mat[1][depart] = 'D';
	mat[dim1-2][arrivee] = 'A';
	*xd = depart;
	*yd = 1;
	*xa = arrivee;
	*ya = dim1-2;

}

int etape(char mat[][DIM2], int dim1, int val){
	// Marquage nous permet de savoir si au moins une case à été modifiée
	int i, j, valeur, marquage = 0;
	valeur = (val == 'D') ? 0 : val;
	for(i = 1; i < DIM1-1; i++){
		for(j = 1; j < DIM2-1; j++){
			// Si valeur de la case == val
			if(mat[i][j] == val){
				// On regarde si les cases sont libres autour
				// Et si il y a une modification on met marquage à 1
				if(mat[i-1][j] == 0){
					mat[i-1][j] = valeur+1;
					marquage = 1;
				}
				if(mat[i][j-1] == 0){
					mat[i][j-1] = valeur+1;
					marquage = 1;
				}
				if(mat[i+1][j] == 0){
					mat[i+1][j] = valeur+1;
					marquage = 1;
				}
				if(mat[i][j+1] == 0){
					mat[i][j+1] = valeur+1;
					marquage = 1;
				}
			}
		}
	}
	return marquage;
}

int expansion(char mat[][DIM2], int dim1, int xd, int yd, int xa, int ya){
	//
	int val = 1, marquage = 1;
	mat[yd][xd] = val;
	mat[ya][xa] = 0;

	while(mat[ya][xa] == 0 && marquage == 1){
		marquage = etape(mat, dim1, val);
		val++;
		//affiche(mat, dim1);
	}
	affiche(mat, dim1);
	if(mat[ya][xa] == 0){
		return 0;
	}
	return 1;
}

void chemin(char mat[][DIM2], int dim1, int xa, int ya){
	int val;
	int x = xa, y = ya;

	// Tant que l'on a pas atteint le départ
	while(mat[y][x] != 1){
		// On récupère la valeur de la case courante
		val = mat[y][x];
		// puis on met une étoile
		mat[y][x] = '*';

		// On recherche la case adjacente avec la plus petite valeur
		if(mat[y-1][x] == val-1){
			y--;
		}
		if(mat[y][x-1] == val-1){
			x--;
		}
		if(mat[y+1][x] == val-1){
			y++;
		}
		if(mat[y][x+1] == val-1){
			x++;
		}
		//affiche(mat, dim1);
	}
	// On rempli la case avec une étoile
	mat[y][x] = '*';
}