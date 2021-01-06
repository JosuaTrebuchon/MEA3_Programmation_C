/*
 * database.h
 *
 *  Created on: 13 nov. 2020
 *      Author: mea
 */

#ifndef __DATABASE_H__
#define __DATABASE_H__

//##############################################################################
//#                            CONSTANTS DEFINITION                            #
//##############################################################################

#define MAX_DEPARTMENT_NAME_LENGTH (30)
#define MAX_REGION_NAME_LENGTH (40)
#define MAX_NB_DEPARTMENTS (100)
#define MAX_NB_REGIONS (12)

#define NB_VARIABLES (4)
#define NB_YEARS (46)

//##############################################################################
//#                           STRUCTURES DECLARATION                           #
//##############################################################################

/**
 * Represents one particular region and the mean values
 * of all of its departments.
 */
typedef struct
{
    char 			name[MAX_REGION_NAME_LENGTH]; 		///< name of the region
    unsigned int 	nb_departments; 					///< number of department in the region
    float 			values[NB_VARIABLES][NB_YEARS]; 	///< mean values of the meteorologic values from the department
} region_t;

/**
 * Represents one particular department.
 */
typedef struct
{
    char 			name[MAX_DEPARTMENT_NAME_LENGTH]; 	///< name of the region
    unsigned int 	numero; 							///< identification number of the region
    unsigned int 	region_index; 						///< related region index in the database
    float 			values[NB_VARIABLES][NB_YEARS]; 	///< annual mean meteorologic values
} department_t;

/**
 * A database to store all the data of the regions and departments
 * extracted from the csv file.
 */
typedef struct
{
    region_t 		regions[MAX_NB_REGIONS]; 			///< array of the regions
    department_t 	departments[MAX_NB_DEPARTMENTS]; 	///< array of the departments
    unsigned int 	nb_regions; 						///< number of regions stored in the database
    unsigned int	nb_departments;						///< number of departments stored in the database
} database_t;

//##############################################################################
//#                           FUNCTIONS DECLARATION                            #
//##############################################################################

//___________________________structure_initialization___________________________
//******************************************************************************

/**
 * Initialize the database by filling all the arrays with 0 and setting
 * the number of regions and departments to 0.
 *
 * @param database - the database to initialize
 */
void init_database(database_t *database);

/**
 * Initialize the region with its name and sets the number of departments
 * and the mean values to 0.
 *
 * @param region - the region to initialize
 * @param name - name of the region
 */
void init_region(region_t *region, char name[]);

/**
 * Initialize the department with its name, its number and its region.
 * Sets the meteorologic values to 0.
 *
 * @param department - the department to initialize
 * @param region_index - index of the region in the database
 * @param name - name of the department
 * @param num - number of the department (its id)
 */
void init_department(department_t *department, unsigned int region_index,
                     char name[], unsigned int num);


//_________________________________find_indexes_________________________________
//******************************************************************************

/**
 * Find the index of the department in the database.
 *
 * @param database - the database in which to search the department
 * @param department_num - number of the department to search
 * @return the index of the department if found, or -1 if it is not present
 *         in the database
 */
int find_department(database_t *database, unsigned int department_num);

/**
 * Find the index of the region in the database.
 *
 * @param database - the database in which to search the region
 * @param region_name - name of the region to search
 * @return the index of the region if found, or -1 if it is not present
 *         in the database
 */
int find_region(database_t *database, char region_name[]);


//___________________________fill_structures_from_csv___________________________
//******************************************************************************

/**
 * Find the specified region in the database
 * and if it does not exist, create it.
 *
 * @param database - the database in which to search or create the region
 * @param name - name of the region
 * @return index of the region in the database
 */
int find_or_create_region(database_t *database, char name[]);

/**
 * Find the specified department in the database and if it does not exist,
 * create it. if the region does not exist either, it is also created.
 *
 * @param database - the database in chich to search or create the department
 *                   and the region
 * @param department_name - name of the department
 * @param department_num - number of the department (its id)
 * @param region_name - name of the region to find or create
 * @return index of the department in the database
 */
int find_or_create_department(database_t *database, char department_name[],
                               unsigned int department_num, char region_name[]);

/**
 * Read the semicolon-separated values from the string line and place
 * the read data in the database with the appropriate department.
 * Initilize all the necessary structures in the database.
 *
 * @param line - the string from which all the information will be taken.
 *               Will be modified by this function.
 * @param database - the database in which the informations will be stored
 * @param serie - the serie this line is about.
 *                Between 0 and (NB_VARIABLES-1) included.
 */
void parse_csv_line(char line[], database_t *database, unsigned int serie);

#endif // __DATABASE_H__
