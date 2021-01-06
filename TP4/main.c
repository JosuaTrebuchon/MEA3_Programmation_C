#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "main.h"
#include <limits.h>


#define DIM1 20
#define DIM2 30
#define MIN_RAND 0
#define MAX_RAND 100

int main(){

	int matrice[DIM1][DIM2];
	initialise(matrice, DIM1, DIM2,30);
	affiche(matrice, DIM1, DIM2);


	return 0;
}


void affiche(int* mat, int dim1, int dim2){
	int i, j;
	// On parcours le tableau et on affiche le bon caractère en fonction de ce qu'on trouve
	for(i = 0; i < dim1; i++){
		for(j = 0; j < dim2; j++){
			switch (tab[i][j]) {
			case 0 :
				printf(" ");
				break;
			case -1 :
				printf("#");
				break;
			}
		}
		printf("\n");
	}
}

int random_number(int min, int  max)
{
	// limits are included in the range
	unsigned int rand_range = max + 1 - min;

	// assert() exits the program if the condition is not verified
	assert(rand_range > 0);

	return (rand() % rand_range) + min;
}

void initialise(int mat[][dim2], int dim1, int dim2, int p){
	int i, j, random;
	// On fait la première et la dernière ligne de la matrice
	for(j = 0; j < dim2; j++){
		mat[0][j] = -1;
		mat[dim1-1][j] = -1;
	}
	// On remplis la première et la dernière colonne
	for(i = 1; i < dim1-1; i++){
		mat[i][0] = -1;
		mat[i][dim2-1] = -1;
	}
	// On remplit le centre de 0
	for(i = 1; i < dim1-1; i++){
		for(j = 1; j < dim2-1; j++){
			// On vérifie la probas
			random = random_number(MIN_RAND, MAX_RAND);
			if(random <= p){
				mat[i][j] = -1;
			}else{
				mat[i][j] = 0;
			}
		}
	}



}
