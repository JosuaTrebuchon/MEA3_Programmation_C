#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "main.h"
#include <limits.h>

#define ARRAY_SIZE (5)
#define ARRAY_MIN (0)
#define ARRAY_MAX (100)

int main()
{
	int n = ARRAY_SIZE*2;
	int tab[n];
	int doublon[10] = {1, 6, 7, 99, 35, 24, 6, 84, 9, 35};
	int filtre[15] = {0};
	int array[ARRAY_SIZE]; ///< Array all the functions will work with
	unsigned int rand_seed; ///< seed to generate random values from
	int res[n + ARRAY_SIZE];

	rand_seed = time(0); // current time
	printf("random seed = %u\n", rand_seed);
	srand(rand_seed);



	random_array(array, ARRAY_SIZE, ARRAY_MIN, ARRAY_MAX);
	random_array(tab, n, ARRAY_MIN, ARRAY_MAX);

	//Test minMax
	printf("Test minMax :\n");
	affiche(array, ARRAY_SIZE);
	minMax(array, ARRAY_SIZE);
	printf("\n");

	// Test croissant et tri
	printf("Test croissant et tri :\n");
	affiche(array, ARRAY_SIZE);
	croissant(array, ARRAY_SIZE);
	triTab(array, ARRAY_SIZE);
	affiche(array, ARRAY_SIZE);
	croissant(array, ARRAY_SIZE);
	printf("\n");

	// Doublons
	printf("Test doublons :\n");
	triTab(doublon, 10);
	affiche(doublon, 10);
	printf("Il y a %d doublons dans ce tableau\n", doublons(doublon, 10));
	printf("\n");

	// Filtre tableau
	printf("Test filtre :\n");
	affiche(doublon, 10);
	affiche(filtre, 15);
	filtreTab(doublon, 10, filtre, 15);
	affiche(filtre, 15);
	printf("\nTest filtre sur place :\n");
	int f = filtreTab(doublon, 10, doublon, 10);
	affiche(doublon, 10);
	printf("Le tableau a maintenant une taille de %d entiers\n", f);
	printf("\n");

	// Fusion
	printf("Test de la fusion :\n");
	triTab(tab, n);
	affiche(array, ARRAY_SIZE);
	affiche(tab, n);
	triFusion(array,tab, res, ARRAY_SIZE, n);

	affiche(res, n + ARRAY_SIZE);
	croissant(res, n + ARRAY_SIZE);


	//...

//	croissant(array, ARRAY_SIZE);
//
//	triTab(array, ARRAY_SIZE);
//	affiche(array, ARRAY_SIZE);
//	filtreTab(array, ARRAY_SIZE, array, ARRAY_SIZE);
//	affiche(array, ARRAY_SIZE);



	return 0;
}

void random_array(int array[], int array_size, int min, int  max)
{
	int i;

	// limits are included in the range
	unsigned int rand_range = max + 1 - min;

	// assert() exits the program if the condition is not verified
	assert(rand_range > 0);

	for (i = 0; i < array_size; i++)
	{
		array[i] = (rand() % rand_range) + min;
	}
}

void minMax(int array[], int array_size){
	// On déclare les min et max
	int min = array[0];
	int max = array[0];
	// Pour i de 1 à taille(array)
	for(int i = 0; i < array_size; i++){

		// Si t[i] est le nouveau max
		if(array[i] > max){
			max = array[i];
		}
		// Si t[i] est le nouveau min
		if(array[i] < min){
			min = array[i];
		}
	}
	printf("Le min du tableau est : %d, et son max : %d\n", min, max);
}

int croissant(int array[], int array_size){
	int i = 0;
	// Tat que i < arraysize-1 (avant dernière case)
	while (i < array_size-1){
		// Si t[i] > t[i+1] alors pas croissant
		if(array[i]> array[i+1]){
			printf("Ce tableau n'est pas croissant\n");
			return -1;
		}
		i++;
	}
	// Sinon le tableau est croissant
	printf("Ce tableau est croissant\n");
	return 0;
}

void triTab(int array[], int array_size){
	// On déclare les bornes du sous tableau
	int fin = array_size-1;
	int deb = 0;
	int min, max, imin, imax, temp;

	// Tant qu'on n'a pas parcouru tout le tableau
	while(deb < fin){
		min = array[deb];max = array[deb];imin = deb;imax = deb;
		// On cherche le min et le max du sous tableau
		for(int i = deb; i <= fin; i++){
			// Si t[i] est le nouveau max
			if(array[i] > max){
				max = array[i];
				imax = i;
			}
			// Si t[i] est le nouveau min
			if(array[i] < min){
				min = array[i];
				imin = i;
			}
		}
		// On échange le min avec la première valeur du tableau
		temp = array[deb];
		array[deb] = array[imin];
		array[imin] = temp;

		// Si le max était au début alors il prend la valeur de imin (son nouvel indice)
		if(imax == deb){
			imax = imin;
		}

		// On échange le max avec le dernier du tableau
		temp = array[fin];
		array[fin] = array[imax];
		array[imax] = temp;

		// On décrémente Fin et on incrémente Deb
		deb++; fin--;
	}
}

int doublons(int array[], int array_size){
	int doublon = 0, i = 0;
	// On tri le tableau
	triTab(array, array_size);
	// Pour chaque valeur du tableau on la compare avec la suivante
	while(i < array_size-1){
		if(array[i] != array[i+1]){
			doublon++;
		}
		i++;
	}
	// On compare la dernière avec la première
	if(array[array_size-1] != array[0]){
		doublon ++;
	}

	//printf("Il y a %d valeurs différentes pour une taille de %d\n", doublon, array_size);
	return doublon;
}

int filtreTab(int* source, int ns, int* destination, int nd){
	int i = 1, k = 1, res;
	destination[0] = source[0];
	// Tant que l'on a pas parcouru tout le tableau
	while(i < ns){
		// Si les valeurs sont différents, on met dans destination
		if(source[i] != source[i-1]){
			destination[k] = source[i];
			k++;
		}
		i++;
	}
	res = k;
	// on remplis le reste de la destination
	for(int j = k; j < nd; j++){
		destination[j] = INT_MIN;
	}

	return res;
}


void triFusion(int* t1, int* t2, int* dest, int n1, int n2){
	// Initialisation des variables de parcours de tableau
	int iT1 = 0, iT2 = 0, idest = 0;

	// Tant que les indices respectent les tailles des tableaux
	while(iT1 < n1 && iT2 < n2 && idest < (n1 + n2)){
		// On met le min entre les deux valeurs dans Dest et on incrémente l'indice de tableau concerné
		if(t1[iT1] < t2[iT2]){
			dest[idest] = t1[iT1];
			iT1++;
		}else{
			dest[idest] = t2[iT2];
			iT2++;
		}
		// On incrémente l'indice du tableau destination
		idest++;
	}
	// Ici un tableau est fini mais peut-être pas l'autre donc on le parcours entièrement
	// Si t1 pas fini on le fini
	if(iT1 < n1){
		for(int i = iT1 ;i < n1; i++){
			dest[idest] = t1[i];
			idest++;
		}
	}
	// Si t2 pas fini on le fini
	if(iT2 < n2){
		for(int j = iT2 ;j < n2; j++){
			dest[idest] = t2[j];
			idest++;
		}
	}
}


void affiche(int array[], int array_size){
	printf("[ ");
	for(int i = 0; i < array_size-1; i++){
		printf("%d, ", array[i]);
	}
	printf("%d ", array[array_size-1]);
	printf("]\n");
}
