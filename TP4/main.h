/*
 * main.h
 *
 *  Created on: 21 oct. 2020
 *      Author: mea
 */

#ifndef MAIN_H_
#define MAIN_H_


/**
 * Affiche l'état de la grille à un moment donné
 *
 * @param tab Tableau à deux dimensions
 * @param dim1 Dimension 1
 * @param dim2 Dimension 2
 */
void affiche(int* mat, int dim1, int dim2);

int random_number(int min, int max);

/**
 * Remplis les bords de la matrice d'obstacles (-1) et le centre de 0
 *
 * @param tab Tableau à deux dimensions
 * @param dim1 Dimension 1
 * @param dim2 Dimension 2
 * @param p Nombre d'obstacles
 */
void initialise(int mat[][], int dim1, int dim2, int p);



#endif /* MAIN_H_ */
