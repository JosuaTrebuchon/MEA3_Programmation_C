#ifndef __ANNUAIRE_H__
#define __ANNUAIRE_H__

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

//##############################################################################
//#                    CONSTANTS, ENUMERATIONS, STRUCTURES                     #
//##############################################################################

#define NBR_MAX_CONTACT (300) ///< Maximum number of contacts in the database

#define MAX_LAST_NAME_LENGTH (15) ///< Maximum length of a contact's last name
#define MAX_FIRST_NAME_LENGTH (20) ///< Maximum length of a contact's first name
#define MAX_TEL_LENGTH (5) ///< Maximum length of a contact's phone number
#define MAX_ROOM_LENGTH (12) ///< Maximum length of a contact's phone number

/**
 * Qualification of a contact
 */
typedef enum {
    QUALIF_UNKNOWN = 0,
    QUALIF_AGENT = 1,
    QUALIF_MAITRISE = 2,
    QUALIF_CADRE = 3,
    QUALIF_CADRE_SUPERIEUR = 4
} qualification_t;

/**
 * site where the contact is located
 */
typedef enum {
    SITE_UNKNOWN = 0,
	MONTPELLIER,
	PARIS,
	STRASBOURG
} site_t;

/**
 * Contact defined by his/her last name, first name, qualification,
 * site (s)he works at and room number (s)he is in, and internal phone number.
 * This structure also contains the index to the next contact in the database
 */
typedef struct
{
    char last_name[MAX_LAST_NAME_LENGTH];
    char first_name[MAX_FIRST_NAME_LENGTH];
    qualification_t qualification;
    site_t site;
    char room[MAX_ROOM_LENGTH];
    int internal_phone_number[MAX_TEL_LENGTH];

    int next_c;
} contact_t;

/**
 * Contains an array of contacts and the linked lists that use this array:
 * one linked list for the contacts stored, and one for the free elements
 * in the array. Linked list are defined by their first element's index.
 * When a list is empty, its head index is set to -1.
 */
typedef struct
{
    contact_t contacts[NBR_MAX_CONTACT];
    int tete;
    int libre;
} database_t;

//##############################################################################
//#                      QUALIFICATION AND SITE FUNCTIONS                      #
//##############################################################################

/**
 * Convert the string into a qualification, or QUALIF_UNKNOWN if there is no
 * correspondance.
 *
 * @param str - the string to convert to qualification
 * @return the corresponding qualification, or QUALIF_UNKNOWN
 */
qualification_t qualification_parse(const char str[]){
	qualification_t qualif = atoi(str);
	return qualif;
}

/**
 * Print the qualification in the file. A minmum of characters to print
 * can be specified. Space characters will be used to fill the space
 * after printing the name if necessary.
 *
 * @param qualif - qualification to print
 * @param out - output file to use. Can be stdout.
 * @param min_chars - minimum number of characters to use
 */
void qualification_print(qualification_t qualif, FILE* out, int min_chars){
	int length;
	switch(qualif){
		case 1:
			fprintf(out, "1-agent");
			length = strlen("1-agent");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
		case 2:
			fprintf(out, "2-maitrise");
			length = strlen("2-maitrise");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
		case 3:
			fprintf(out, "3-cadre");
			length = strlen("3-cadre");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
		case 4:
			fprintf(out, "4-cadre superieur");
			length = strlen("4-cadre superieur");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
		default:
			fprintf(out, "0-unknown");
			length = strlen("0-unknown qualif");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
	}
}

/**
 * Convert the string into a site, or SITE_UNKNOWN if there is no
 * correspondance
 * @param str - the string to convert to site
 * @return the corresponding site, or SITE_UNKNOWN
 */
site_t site_parse(const char str[]){
	if(strcmp("Paris", str) == 0){
		return (site_t) PARIS;
	}
	if(strcmp("Montpellier", str) == 0){
		return (site_t) MONTPELLIER;
	}
	if(strcmp("Strasbourg", str) == 0){
		return (site_t) STRASBOURG;
	}
	return (site_t) SITE_UNKNOWN;
}

/**
 * Print the site in the file. A minmum of characters to print
 * can be specified. Space characters will be used to fill the space
 * after printing the name if necessary.
 *
 * @param qualif - site to print
 * @param out - output file to use. Can be stdout.
 * @param min_chars - minimum number of characters to use
 */
void site_print(site_t site, FILE* out, int min_chars){
	int length;
	switch(site){
		case PARIS :
			fprintf(out, "Paris");
			length = strlen("Paris");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
		case MONTPELLIER:
			fprintf(out, "Montpellier");
			length = strlen("Montpellier");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
		case STRASBOURG:
			fprintf(out, "Strasbourg");
			length = strlen("Strasbourg");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
		default:
			fprintf(out, "Unknown site");
			length = strlen("Unknown site");
			if(length < min_chars){
				for(int i = length; i <= min_chars; i++){fprintf(out, " ");}
			}
			break;
	}


}

/**
 * Compares the two qualifications
 *
 * @param qualif1 - first qualification to compare
 * @param qualif2 - second qualification to compare
 * @return -1 if qualif1 < qualif2
 *         0 if qualif1 == qualif2
 *         1 if qualif1 > qualif2
 */
int qualification_compare(qualification_t qualif1, qualification_t qualif2){
	if(qualif1 < qualif2){
		return -1;
	}
	if(qualif1 > qualif2){
		return 1;
	}
	return 0;
}

/**
 * Compares the two sites
 *
 * @param site1 - first site to compare
 * @param site2 - second site to compare
 * @return -1 if site1 < site2
 *         0 if site1 == site2
 *         1 if site1 > site2
 */
int site_compare(site_t site1, site_t site2){
	if(site1 < site2){
		return -1;
	}
	if(site1 > site2){
		return 1;
	}
	return 0;
}

//##############################################################################
//#                             CONTACT FUNCTIONS                              #
//##############################################################################

/**
 * Calculate the order of the two specified contacts.
 * Contacts are sorted by last name alphabetical order first, then first name
 * alphabetical order, then qualification descending order, then site
 * alhpabetical order and finally phone number ascending (alphabetical) order.
 * @param contact1 - first contact to compare
 * @param contact2 - second contact to compare
 *
 * @return the order (-1, 0 or 1) of the two specified contacts. (-1 if site1 < site2 alphabeticaly, ex : compare(contact_0, contact_10) = -1)
 */
int contact_compare(const contact_t* const contact1,
                    const contact_t* const contact2){
	int last_n, first_n, qualif, site, i;
	last_n = strcmp(contact1->last_name, contact2->last_name);
	// If last names equals
	if(last_n == 0){
		first_n = strcmp(contact1->first_name, contact2->first_name);
		// If first names equals too
		if(first_n == 0){
			qualif = qualification_compare(contact1->qualification, contact2->qualification);
			// If qualification are the sames
			if(qualif == 0){
				site = site_compare(contact1->site, contact2->site);
				// If site are equals
				if(site == 0){
					// Comparison of each numbers of the phone number
					for(i = 0; i < MAX_TEL_LENGTH; i++){
						if(contact1->internal_phone_number[i] > contact2->internal_phone_number[i]){ return 1;}
						if(contact1->internal_phone_number[i] < contact2->internal_phone_number[i]){ return -1;}
						return 0;
					}
				}
				return site;
			}
			return qualif;
		}
		return (first_n < 0) ? -1 : 1;
	}
	return (last_n < 0) ? -1 : 1;
}

/**
 * Initialize the contact by filling all the attributes with a default value
 * (empty string for strings), and sets the index of the next element
 * in the linked list to -1.
 *
 * @param contact - contact to initialize
 */
void contact_init(contact_t *const contact){
	memset(contact, 0, sizeof(contact_t));
	contact->next_c = -1;
}

/**
 * Check if the contact matches the specified filters.
 *
 * @param contact - contact to test.
 * @param last_name_filter - the last name must start with this string to match.
 *                           Can be null to match all contacts.
 * @param first_name_filter - the first name must start with this string
 *                            to match. Can be null to match all contacts.
 * @param qualif_filter - qualification the contact must have to match. Can be
 *                        QUALIF_UNKNOWN to match all contacts.
 * @param site_filter - site the contact must have to match. Can be SITE_UNKNOWN
 *                      to match all contacts.
 * @return 1 if the contact matches to filters, 0 otherwise.
 */
int contact_match(const contact_t *const contact,
                   const char last_name_filter[],
                   const char first_name_filter[],
                   const qualification_t qualif_filter,
                   const site_t site_filter){
	int i;
	if(last_name_filter){
		// Comparison with the last name filter
		i = 0;
		while(last_name_filter[i] != '\0' && contact->last_name[i] != '\0'){
			// If the characters are different at the same index
			if(last_name_filter[i] != contact->last_name[i]){
				// Not matching
				return 0;
			}
			i++;
		}
	}

	if(first_name_filter){
		// Comparison with the first name filter
		i = 0;
		while(first_name_filter[i] != '\0' && contact->first_name[i] != '\0'){
			// If the characters are different at the same index
			if(first_name_filter[i] != contact->first_name[i]){
				// Not matching
				return 0;
			}
			i++;
		}
	}
	// Comparison with the qualification
	if(qualif_filter != 0){
		if(qualification_compare(qualif_filter, contact->qualification) != 0){
			return 0;
		}
	}
	// Comparison with the site
	if(site_filter != 0){
		if(site_compare(site_filter, contact->site) != 0){
			return 0;
		}
	}
	// Otherwise, all filters matching
	return 1;
}

/**
 * Check that no information is missing in the contact, and that there is
 * no issue with the string length: all strings must end must character '\0'.
 *
 * @param contact - contact to check.
 * @return 1 if everything is fine, 0 otherwise.
 */
int contact_check(const contact_t *const contact){
	int i = 0, sum = 0;
	// Checking last name
	while(i < MAX_LAST_NAME_LENGTH && contact->last_name[i] != '\0'){
		i++;
	}
	if(i == MAX_LAST_NAME_LENGTH) return 0;

	// Checking first name
	i = 0;
	while(i < MAX_FIRST_NAME_LENGTH && contact->first_name[i] != '\0'){
		i++;
	}
	if(i == MAX_FIRST_NAME_LENGTH) return 0;

	// Checking qualification
	if(contact->qualification < 0) return 0;
	// Checking site
	if(contact->site < 0) return 0;
	// Checking room
	i = 0;
	while(i < MAX_ROOM_LENGTH && contact->room[i] != '\0'){
		i++;
	}
	if(i == MAX_ROOM_LENGTH) return 0;

	// Checking phone number
	i = 0;
	while(i < MAX_TEL_LENGTH){
		sum+=contact->internal_phone_number[i];
		i++;
	}
	if(sum == 0) return 0;

	if(contact->next_c > NBR_MAX_CONTACT || contact->next_c < -1) return 0;
	return 1;
}

/**
 * Print the contact's informations in the specified file. This file can be
 * stdout to print to the console. All attributes are printed with fixed size to
 * vertically align all contacts printed with this function.
 *
 * @param contact - the contact to print.
 * @param out - file in which the contact will be printed.
 */
void contact_print(const contact_t *const contact, FILE *out){
	int i;
	char separator = ';';
	// Last name print
	for(i = 0; i < MAX_LAST_NAME_LENGTH; i++){
		char c = contact->last_name[i];
		if(c == '\0'){
			fprintf(out," ");
		}else{
			fprintf(out,"%c", c);
		}
	}
	fprintf(out, "%c", separator);
	// First name print
	for(i = 0; i < MAX_FIRST_NAME_LENGTH; i++){
		char c = contact->first_name[i];
		if(c == '\0'){
			fprintf(out," ");
		}else{
			fprintf(out,"%c", c);
		}
	}
	fprintf(out, "%c", separator);
	// Qualification print
	qualification_print(contact->qualification, out, 18);
	fprintf(out, "%c", separator);
	// Site print
	site_print(contact->site, out, 12);
	fprintf(out, "%c", separator);
	// Room number
	for(i = 0; i < MAX_ROOM_LENGTH; i++){
		char c = contact->room[i];
		if(c == '\0'){
			fprintf(out," ");
		}else{
			fprintf(out,"%c", c);
		}
	}
	fprintf(out, "%c", separator);
	// Internal number phone print
	int not_in = 1;
	for(i = 0; i < MAX_TEL_LENGTH; i++){
		int num = contact->internal_phone_number[i];
		if(num == 0 && not_in){
			fprintf(out," ");
		}else{
			fprintf(out,"%d", num);
			not_in = 0;
		}
	}
	fprintf(out, "%c", separator);
	fprintf(out, "\n");
}

/**
 * Fill the contact with the fields decoded from the csv line
 *
 * @param csv_line - csv line string containing contact informations.
 * @param contact - contact to fill with the fields in the csv line.
 */
void contact_csv_read(char csv_line[], contact_t *const contact){
	/****** Data recuperation ******/

	const char* separator = ";";

	// Last name reading
	char* strToken = strtok(csv_line, separator);
	assert(strToken != NULL);
	strcpy(contact->last_name, strToken);

	// Fisrt name reading
	strToken = strtok(NULL, separator);
	assert(strToken != NULL);
	strcpy(contact->first_name, strToken);

	// Qualification reading
	strToken = strtok(NULL, separator);
	assert(strToken != NULL);
	contact->qualification = qualification_parse(strToken);

	// Site reading
	strToken = strtok(NULL, separator);
	assert(strToken != NULL);
	contact->site = site_parse(strToken);

	// Room reading
	strToken = strtok(NULL, separator);
	assert(strToken != NULL);
	strcpy(contact->room, strToken);

	// Tel number reading
	strToken = strtok(NULL, separator);
	assert(strToken != NULL);
	int i = 0;
	while((strToken[i] != '\0') && (strToken[i] - 48 >= 0) && (strToken[i] - 48 <= 9) && (i <= MAX_TEL_LENGTH)){
		contact->internal_phone_number[MAX_TEL_LENGTH-(1+i)] = strToken[i]-48;
		i++;
	}

	assert(contact_check(contact) == 1);
}

/**
 * Write the contact informations to the csv file with the following format:
 * LAST_NAME;FIRST_NAME;QUALIFICATION;SITE;ROOM;PHONE\n
 *
 * @param contact - contact to write in the file.
 * @param out - csv file to write the contact to.
 *
 */
void contact_csv_write(const contact_t *const contact, FILE *out){
	int length_names = strlen(contact->last_name) + strlen(contact->first_name)+3;
	int length_room = strlen(contact->room)+8;
	char names[length_names], room[length_room];
	memset(names, '\0', sizeof(char)*length_names);
	memset(room, '\0', sizeof(char)*length_room);
	// Concatenate last name
	strcat(names, contact->last_name);
	strcat(names, ";");
	// Concatenate fisrt name
	strcat(names, contact->first_name);
	strcat(names, ";");
	// Print the last and first name
	if ( 1 != fwrite( names, sizeof(char)*length_names, 1, out ) ) {
	    fprintf( stderr, "Cannot write block in file\n" );
	}
	// Print the qualification & site
	qualification_print(contact->qualification, out, 18);
	if ( 1 != fwrite( ";", sizeof(char), 1, out ) ) {
		fprintf( stderr, "Cannot write block in file\n" );
	}
	site_print(contact->site, out, 12);
	if ( 1 != fwrite( ";", sizeof(char), 1, out ) ) {
		fprintf( stderr, "Cannot write block in file\n" );
	}
	// Room concat
	strcat(room, contact->room);
	strcat(room, ";");

	// Tel print
	// Internal number phone print
	int in = 0, j=0;
	char temp[5];
	int num;
	memset(temp, '\0', sizeof(char)*5);
	for(int i = 0; i < MAX_TEL_LENGTH; i++){
		num = contact->internal_phone_number[i];
		if(num != 0 || in){
			temp[j] = (num + 48);
			in = 1;
			j++;
		}
	}
	strcat(room, temp);
	strcat(room, ";\r\n");
	if ( 1 != fwrite( room, sizeof(char)*length_room, 1, out ) ) {
		fprintf( stderr, "Cannot write block in file\n" );
	}
}

//##############################################################################
//#                             DATABASE FUNCTIONS                             #
//##############################################################################

/**
 * Resets and initialize the database : initialize all the contacts
 * in the array, and set the free contacts list to cover the whole array,
 * from the first contact to the last one. The occupied contacts list
 * is set to empty.
 *
 * @param database - contacts database to initialize.
 */
void database_init(database_t *const database){
	for(int j = 0; j < NBR_MAX_CONTACT; j++){
		contact_init(&database->contacts[j]);
	}
	database->tete= -1;
	database->libre = 0;
	for(int i = database->libre; i < NBR_MAX_CONTACT; i++){
		database->contacts[i].next_c = (i < NBR_MAX_CONTACT-1) ? ( i+1 ) : -1;
	}
}

/**
 * Check all the occupied contacts, make sure the contacts are in
 * alphabetical order, and the lengths of the occupied list and the free list
 * sum up to the total array length.
 *
 * @param database - database to check.
 * @return 1 if everything is fine, 0 otherwise.
 */
int database_check(const database_t *const database){
	int index_c = database->tete, next, nbr_contacts = 0, nbr_free = 0, nb_total;
	// Verification on the contact saved in database
	while(index_c != -1){
		nbr_contacts++;
		// If the contact haven't filled well
		if(contact_check(&database->contacts[index_c]) == 0) return 0;
		// If the contact have a successor
		if(database->contacts[index_c].next_c > -1){
			// If it's not in the correct order
			next = database->contacts[index_c].next_c;
			//printf("%d\n",contact_compare(&database->contacts[index_c], &database->contacts[next]));
			if(contact_compare(&database->contacts[index_c], &database->contacts[next]) > 0){
				return 0;
			}
		}
		index_c = database->contacts[index_c].next_c;
	}
	// Verification of the global number of cases
	index_c = database->libre;

	while(index_c != -1){
		nbr_free++;
		index_c = database->contacts[index_c].next_c;
	}

	nb_total = (nbr_free+nbr_contacts);
	// Checking the number of entries that can be stored in the database
	return (nb_total == NBR_MAX_CONTACT) ? 1 : 0;
}

/**
 * Print all the contacts in the database using the contact_print() function.
 * To make debugging easier, each line is preceded by its rank in the list
 * and its index in the array:
 * [rnk@idx] LASTNAME       FIRSTNAME   QUALIFICATION   ...
 * At the end, print the number of contacts in the database and the place left
 * for new contacts.
 *
 * @param database - database to print.
 * @param out - file to print the database to. Can be stdout.
 */
void database_print(const database_t *const database, FILE *out){
	int index_c = database->tete;
	fprintf(out, "\n");
	while(index_c != -1){
		contact_print(&database->contacts[index_c], out);
		index_c = database->contacts[index_c].next_c;
	}
	fprintf(out, "\n");
}

/**
 * Reset the database and import all the contacts from the csv file.
 * Contacts in the file are considered sorted alphabetically
 * (LastName, FirstName).
 *
 * @param database - database to store new contacts into.
 * @param file - csv file path to read.
 * @return 1 if all the contacts have been stored,
 *         0 otherwise (database is full).
 */
int database_open(database_t *const database, const char*const file){
	database_init(database);
	char * buffer = (char *) malloc(1000);
	int temp, last = -1;
	/****** File opening ******/

	FILE* contacts;
	contacts = fopen(file, "r");

	if(!feof(contacts)){
		fgets(buffer, 1000, contacts);
	}

	database->tete = database->libre;
	fgets(buffer, 1000, contacts);
	while(!feof(contacts)){
		// In case of a error
		if(ferror(contacts)){
			fprintf(stderr, "Erreur de lecture du fichier, erreur code : %d\n", errno);
			break;
		}

		// If the database is full
		if(database->libre == -1){
			return 0;
		}

		// Saving contact in database
		contact_csv_read(buffer, &database->contacts[database->libre]);
		// Modification of the lists's indexes
		temp = database->libre;
		// We change the next contact index for the latest contact added
		if(last != -1){
			database->contacts[last].next_c = temp;
		}
		database->libre = database->contacts[database->libre].next_c;
		database->contacts[temp].next_c = -1;
		last = temp;

		fgets(buffer, 1000, contacts);
	}
	// If there has no saving done
	if(database->tete == database->libre){
		database->tete = -1;
	}
	fclose(contacts);
	free(buffer);
	//database_print(database, stdout);

	return database_check(database);
}

/**
 * Insert new contacts from the csv file into the database. Contacts that were
 * previously stored are not modified. Multiple contacts with the same name
 * but different other attributes are permitted.
 * The csv is not considered sorted.
 * The first row of the csv contains a header and is ignored.
 * The function stops when the file is completely parsed, or when there is
 * no room left for new contacts
 *
 * @param file - csv file to read, contains new contacts to import
 * @param database - contacts database to store new contacts into
 * @return 1 if all the new contacts are stored in the database, or
 *         0 if the database is full and the csv is not entirely stored
 *         in the database
 */
int database_import(database_t *const database, const char*const file){
	char * buffer = (char *) malloc(1000);
	int pere = -1, insert, temp;
	FILE* contacts;
	contacts = fopen(file, "r");

	if(!feof(contacts)){
		fgets(buffer, 1000, contacts);
	}
	// ignoring the first line
	fgets(buffer, 1000, contacts);
	while(!feof(contacts)){
		// In case of a error
		if(ferror(contacts)){
			fprintf(stderr, "Erreur de lecture du fichier, erreur code : %d\n", errno);
			break;
		}

		// If the database is full
		if(database->libre == -1){
			return 0;
		}
		//puts(buffer);
		// Saving contact in database
		contact_csv_read(buffer, &database->contacts[database->libre]);
		// Making the right links
		insert = database->tete;
		pere = -1;
		while(insert != -1 && contact_compare(&database->contacts[insert], &database->contacts[database->libre]) != 1){
			pere = insert;
			insert = database->contacts[insert].next_c;
		}
		temp = database->contacts[database->libre].next_c;
		if(insert == database->tete && pere == -1){
			database->contacts[database->libre].next_c = database->tete;
			database->tete = database->libre;
		}else{
			// We place the new node before the node insert
			database->contacts[database->libre].next_c = insert;
			// We make the next node of the dad node pointing on the new node
			database->contacts[pere].next_c = database->libre;
			//database->contacts[insert].next_c = database->libre;
		}
		// We change the pointer on the free list
		database->libre = temp;

		fgets(buffer, 1000, contacts);
	}
	fclose(contacts);
	free(buffer);
	printf("\nNew database after importing new datas :\n");
	database_print(database, stdout);

	assert(database_check(database) == 1);
	return database_check(database);
}

/**
 * Write the entire database in the csv file. The format is identical
 * to when it is read in database_open(). The first row must be the header.
 * At the end, the number of contacts saved is printed in the console.
 *
 * @param database - database to save.
 * @param file - csv file path to save the database to.
 */
void database_save(const database_t *const database, const char file[]){
	//char * buffer = (char *) (1000);
	char* first_line = "NOM;PRENOM;QUALIFICATION;SITE;PIECE;TEL\n";
	FILE* save;
	int index_c = database->tete;
	save = fopen(file, "wa");
	// If cannot open
    if ( save == NULL ) {
        fprintf( stderr, "Cannot open file for writing\n" );
        exit( -1 );
    }
    // Writing the first line of the document
    if ( 1 != fwrite( first_line, sizeof(char)*strlen(first_line), 1, save ) ) {
    	fprintf( stderr, "Cannot write block in file\n" );
    }
    while(index_c != -1){
    	contact_csv_write(&database->contacts[index_c], save);
    	index_c = database->contacts[index_c].next_c;
    }

	fclose(save);
}

/**
 * Search in the database the contacts that match all the filters, and print
 * them in the console.
 *
 * @see contact_match for information on how to use the filters.
 *
 * @param database - the database to search the contacts in.
 * @param last_name_filter - last name filter, or NULL.
 * @param first_name_filter - first name filter, or NULL.
 * @param qualif_filter - qualification filter, or QUALIF_UNKNOWN.
 * @param site_filter - site filter, or SITE_UNKNOWN.
 */
void database_search(const database_t *const database,
                     const char last_name_filter[],
                     const char first_name_filter[],
                     const qualification_t qualif_filter,
                     const site_t site_filter){
	printf("\nNew search :\n");
	int index_c = database->tete, result = 0;
	while(index_c != -1){
		// If the conact match
		if(contact_match(&database->contacts[index_c], last_name_filter, first_name_filter, qualif_filter, site_filter) == 1){
			// We print the contact in the console
			contact_print(&database->contacts[index_c], stdout);
			result++;
		}
		// Go to the next index
		index_c = database->contacts[index_c].next_c;
	}
	if(!result) printf("No results");
	printf("\n");
}

/**
 * Remove from the database the contacts that match the specified filters.
 * The removed contacts are printed in the console, with their rank in the list
 * and index in the table. At the end,The number of removed contacts is printed
 * in the console.
 *
 * @see contact_match for information on how to use the filters.
 *
 * @param database - the database to search the contacts in.
 * @param last_name_filter - last name filter, or NULL.
 * @param first_name_filter - first name filter, or NULL.
 * @param qualif_filter - qualification filter, or QUALIF_UNKNOWN.
 * @param site_filter - site filter, or SITE_UNKNOWN.
 */
void database_remove(database_t *const database,
                     const char last_name_filter[],
                     const char first_name_filter[],
                     const qualification_t qualif_filter,
                     const site_t site_filter){
	int index_c = database->tete, pere = -1, rank = 0;
	printf("\nRemoving datas :\n");
	while(index_c != -1){
		// If the contact match
		if(contact_match(&database->contacts[index_c], last_name_filter, first_name_filter, qualif_filter, site_filter) == 1){
			// We print the contact in the console
			fprintf(stdout, "[rank - %d, index - %d] :\n", rank, index_c);
			contact_print(&database->contacts[index_c], stdout);
			// We remove it from the database
			// Pere does not change value
			if(pere != -1){
				database->contacts[pere].next_c = database->contacts[index_c].next_c;
			}else if(index_c == database->tete){
				// If we are removing the head of the list
				database->tete = database->contacts[index_c].next_c;
			}
			// Add the link to the free list
			contact_init(&database->contacts[index_c]);
			database->contacts[index_c].next_c = database->libre;
			database->libre = index_c;

			// index_c change value
			index_c = (pere != -1) ? database->contacts[pere].next_c : database->tete;
		}else{
			pere = index_c;
			// Go to the next index
			index_c = database->contacts[index_c].next_c;
		}
		rank++;
		assert(database_check(database) == 1);
	}
	//assert(database_check(database) == 1);
}

#endif //__ANNUAIRE_H__
