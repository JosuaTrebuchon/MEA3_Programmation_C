#ifndef __MAIN_H__
#define __MAIN_H__

/**
 * Fills the array with random values in the range [min;max]
 * (limits are included in the range).
 * Random values are generated using the rand() function.
 *
 * @param array - the array to fill with random values
 * @param array_size - size of the array to fill
 * @param min - minimum random value
 * @param max - maximum random value
 */
void random_array(int array[], int array_size, int min, int max);

/**
 * Affiche le min et le max d'un tableau passé en paramètre
 * @param array - Tableau à évaluer
 * @param array_size - Taille du tableau
 */
void minMax(int array[], int array_size);

/**
 * Affiche si  le tableau est croissant ou non
 * @param array - Tableau à évaluer
 * @param array_size - Taille du tableau
 *
 * @return 0 si croissant -1 sinon
 */
int croissant(int array[], int array_size);

void affiche(int array[], int array_size);

/**
 * Tri le tableau mis en paramètre
 *
 * @param array - Tableau à trier
 * @param array_size - Taille du tableau
 */
void triTab(int array[], int array_size);

/**
 * Affiche le nombre de valeur différentes dans le tableau
 *
 * @param array - Tableau à traiter
 * @param array_size - Taille du tableau
 * @return Renvoi le nombre de valeurs différentes
 */
int doublons(int array[], int array_size);

/**
 * Enlève les doublons de source en recopiant le tableau dans destination
 *
 * @param source - Tableau trié
 * @param ns - Taille du tableau source
 * @param destination - Tableau filtrer
 * @param nd - Taille tableau destination
 * @return Taille du nouveau tableau
 */
int filtreTab(int* source, int ns, int* destination, int nd);


/**
 * Pour deux tableaux triés donnés on les fusionne dans un troisième tableau de façon
 * que le dernier tableau soit trié
 *
 * @param t1 Premier tableau à traité
 * @param t2 Second tableau à traiter
 * @param dest Tableau destination
 * @param n1 Taille de t1
 * @param n2 Taille de t2
 */
void triFusion(int* t1, int* t2, int* dest, int n1, int n2);


#endif // __MAIN_H__
