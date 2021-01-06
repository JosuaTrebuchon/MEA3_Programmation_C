/*
 * main.c
 *
 *  Created on: 13 nov. 2020
 *      Author: mea
 */
#include "exploitation.h"
#include <string.h>
#include <errno.h>

//#include <stdlib.h>
/*
 * La fonction main()est donc chargée de :
 * 	•Déclarer une variable de type ‘database_t’.
 *
 * 	•Procéder à son initialisation (tous les champs à 0) à l’aide d’une fonction
 * 	init_database()à implémenter dans database.c.
 *
 * 	•Ouvrir en lecture le fichierClimatDepCSV.csv
 *
 * 	•Extraire  à  l’aide  d’une  boucle  chaque  ligne du  fichier,
 * 	à  tour  de  rôle,  afin  de  la  passer  en  argument à la fonction parse_csv_line()
 * 	qui devra à son tour s’appuyer sur les fonctions de database.c pour effectuer le remplissage de la base de données.
 *
 * 	•Fermer le fichier ClimatDepCSV.csv
 */

#define MAX_LENGTH 2500

int main(){
	// Buffer qui contiendra les lignes du fichier .CSV
	char * buffer = (char *) malloc( MAX_LENGTH );
	int serie = 0; // Valeur de la série concernée (alternance périodique de 0 à 3)

	// Question 1:
	database_t bdd;
	init_database(&bdd);

	// Ouverture du document en lecture
	FILE* climat;
	climat = fopen("ClimatDepCSV.csv", "r");

	/*___________EXTRACTION DES DONNÉES___________*/

	// On ingnore la première ligne
	if(!feof(climat)){
		fgets(buffer, MAX_LENGTH, climat);
	}

	// On récupère une ligne
	fgets(buffer, MAX_LENGTH, climat);

	// Tant que pas la fin du fichier
	while(!feof(climat)){

		// Si il y a une erreur on l'affiche
		if(ferror(climat)){
			fprintf(stderr, "Erreur de lecture du fichier, erreur code : %d\n", errno);
			break;
		}
		// Si la série dépasse 3 on la fait revenir à 0
		serie = (serie == NB_VARIABLES) ? 0 : serie;
		// On remplis la bdd avec les données
		//puts(buffer);
		parse_csv_line(buffer, &bdd, serie);
		// On incrémente la série
		serie++;
		// On récupère la prochaine ligne
		fgets(buffer, MAX_LENGTH, climat);
	}

	/*___________EXPLOITATION DES DONNÉES___________*/

	// Calcul des moyennes
	average_by_region(&bdd);

	//variance_by_region(&bdd, 0);
	int a = find_region(&bdd, "Auvergne-Rh�ne-Alpes");
	int l = find_region(&bdd, "Languedoc-Roussillon-Midi-Pyr�n�es");

	printf("Auvergne-Rh�ne-Alpes : %d\n", a);
	printf("Languedoc-Roussillon-Midi-Pyr�n�es : %d\n\n", l);


	pearson_btw_regions(&bdd, a, l, 0);

	for(int j = 0; j < NB_VARIABLES; j++){
		regression_lineaire(&bdd, 34, j, 2050);
	}

	tab_avg_region(&bdd, l);

	//int index_ldr = find_region(&bdd, "Languedoc-Roussillon-Midi-Pyrenees");

	//float t[5] = {6, 9, 88, 0, 56};
	//printf("variance pourri : %f\n In : %d\n", stat_var(t, 5), index_ldr);
	//variance_region(&bdd, index_ldr, 0);
	//printf("Variance du Languedoc-Roussillon-Midi-Pyrénées en température : %f\n", variance_region(&bdd, index_ldr, 0));

	// Fermeture du document
	fclose(climat);
	return 0;
}


void init_database(database_t* bdd){
	memset(bdd, 0, sizeof(database_t));
}

void init_region(region_t *region, char name[]){
	memset(region, 0, sizeof(region_t));
	strcpy(region->name, name);
}

void init_department(department_t *department, unsigned int region_index,
                     char name[], unsigned int num){
	memset(department, 0, sizeof(department_t));
	strcpy(department->name, name);
	department->region_index = region_index;
	department->numero = num;
}

//_________________________________find_indexes_________________________________
//******************************************************************************

int find_department(database_t *database, unsigned int department_num){
	int i;
	// Pour tout les departement dans la database
	for(i = 0; i< database->nb_departments; i++){
		// Si le numero de departement est celui qu'on cherche
		if(database->departments[i].numero == department_num){
			// On renvoi son indice
			return i;
		}
	}
	// Si nous sommes ici, le dep n'est pas dans la bdd
	// On renvoie -1
	return -1;
}

int find_region(database_t *database, char region_name[]){
	int i;
	// Pour toutes les régions dans la database
	for(i = 0; i< database->nb_regions; i++){
		// Si le nom de la région est identique à celle qu'on cherche
		//printf("%s = %s ? %d\n",database->regions[i].name,region_name,strcmp(database->regions[i].name, region_name));
		if(strcmp(database->regions[i].name, region_name) == 0){
			// On renvoi son indice
			return i;
		}
	}
	// Si nous sommes ici, la region n'est pas dans la bdd
	// On renvoie -1
	return -1;
}

//___________________________fill_structures_from_csv___________________________
//******************************************************************************


int find_or_create_region(database_t *database, char name[]){
	unsigned int index = find_region(database, name);
	// Si la région existe déjà dans la database, on renvoie son indexe
	if(index == -1){
		// On rajoute la région si c'est possible
		if(database->nb_regions < MAX_NB_REGIONS){
			// On garde l'indexe de la région à créer
			index = database->nb_regions;
			// On initialise la région
			init_region(&database->regions[index], name);
			// On incrémente le nombre de régions
			database->nb_regions += 1;
		}
	}

	return index;
}

int find_or_create_department(database_t *database, char department_name[],
                               unsigned int department_num, char region_name[]){
	// Tout d'abord on trouve ou créer la région du dep
	unsigned int index_region = find_or_create_region(database, region_name);
	if(index_region == -1){
		printf("Il n'y a plus de place pour créer une région supplémentaire : erreur\n");
		return -1;
	}
	// On essaye de trouver le department
	unsigned int index_dep = find_department(database, department_num);
	// Si il n'existe pas
	if(index_dep == -1){
		// Si on peut le rajouter dans la bdd
		if(database->nb_departments < MAX_NB_DEPARTMENTS){
			// On récupère le nouvel indice
			index_dep = database->nb_departments;
			// On initialise le nouveau departement
			init_department(&database->departments[index_dep], index_region, department_name, department_num);
			// On inrémente toutes les valeurs qu'il faut
			database->nb_departments += 1;
			database->regions[index_region].nb_departments += 1;
		}
	}

	return index_dep;
}

void parse_csv_line(char line[], database_t *database, unsigned int serie){
	// On déclare le séparateur et le compteur d'annee
	const char* separator = ";";
	int annee = 0;
	// Récupération des infos essentielles pour créer ou trouver le département
	char * name_dep = strtok(line, separator);
	unsigned int num_dep = atoi(strtok(NULL, separator));
	char * name_region = strtok(NULL, separator);
	// Recherche ou création du département
	unsigned int dep_index = find_or_create_department(database, name_dep, num_dep, name_region);

	// On sute deux ligne qui nous intéresse pas ( série et unitée )
	char* strToken = strtok(NULL, separator);
	strToken = strtok(NULL, separator);

	//On récupère les première données
	strToken = strtok(NULL, separator);
	// Tant qu'on a pas fini la ligne
	while(strToken != NULL){
		// on remplie avec la bonne valeur
		database->departments[dep_index].values[serie][annee] = atof(strToken);
		// On récupère lma prochaine ligne
		strToken = strtok(NULL, separator);

		annee+=1;
	}
	return;
}

