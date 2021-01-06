/*
 * main.h
 *
 *  Created on: 21 oct. 2020
 *      Author: mea
 */

#ifndef MAIN_H_
#define MAIN_H_

<<<<<<< HEAD
#define DIM1 15
#define DIM2 20
#define MIN_RAND 0
#define MAX_RAND 100
=======
>>>>>>> 528e4d1feb6a93beebd21175baf8d374d4b49b89

/**
 * Affiche l'état de la grille à un moment donné
 *
 * @param tab Tableau à deux dimensions
 * @param dim1 Dimension 1
 * @param dim2 Dimension 2
 */
<<<<<<< HEAD
void affiche(char mat[][DIM2], int dim1);
=======
void affiche(int* mat, int dim1, int dim2);
>>>>>>> 528e4d1feb6a93beebd21175baf8d374d4b49b89

int random_number(int min, int max);

/**
 * Remplis les bords de la matrice d'obstacles (-1) et le centre de 0
 *
 * @param tab Tableau à deux dimensions
 * @param dim1 Dimension 1
 * @param dim2 Dimension 2
 * @param p Nombre d'obstacles
 */
void initialise(char mat[][DIM2], int dim1, double p);

/**
 * Place les points de départ et d'arrivée
 * 
 * @param mat matrice où placer le départ et l'arrivée 
 */
void departArrivee(char mat[][DIM2], int dim1, int* xd, int* yd, int* xa, int* ya);

/**
 * Fais une étape de l'expansion
 * 
 * @param
 * @param
 * @param
 * @return 
 */
int etape(char mat[][DIM2], int dim1, int val);

/**
 * Réalise l'expansion de Lee
 * 
 * @param
 * @param
 * @param
 * @param
 * @param
 * @return
 */
int expansion(char mat[][DIM2], int dim1, int xd, int yd, int xa, int ya);

/**
 * Trace le chemin depuis l'arrivee jusqu'au départ en cherchant la case autour 
 * qui possède la plus petite valeur.
 * 
 * @param
 * @param
 * @param
 */
void chemin(char mat[][DIM2], int dim1, int xa, int ya);

#endif /* MAIN_H_ */
