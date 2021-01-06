#include "annuaire.h"


int main(int argc, const char * argv[])
{
    database_t database;
//
//    printf("%d\n",database_open(&database, "Contacts-Ouverture.csv"));
//
//    //printf("%d\n", contact_match(&database.contacts[8], NULL, NULL, QUALIF_AGENT, MONTPELLIER));
//    //database_remove(&database,  "G", NULL, QUALIF_AGENT, MONTPELLIER);
//
//    printf("%d\n",database_import(&database, "Contacts-Nouveaux.csv"));
//
//
//    //contact_csv_write(&database.contacts[1], stdout);
//
//    database_save(&database, "test.csv");

    // Initialize, fill, and print a new database based using contacts from a CSV file
	database_open(&database, "Contacts-Ouverture.csv");

	// Perform searches and print list of results
    database_search(&database, "Martin", "Nathalie", QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "CH", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "RO", "bert", QUALIF_UNKNOWN, SITE_UNKNOWN);

	// Add new contacts in the existing database using contacts from a CSV file
	database_import(&database, "Contacts-Nouveaux.csv");

	// Perform searches and print list of results
	database_search(&database, "DARTAGNAN", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "CH", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, NULL, "Marie", QUALIF_UNKNOWN, SITE_UNKNOWN);
	database_search(&database, NULL, NULL, QUALIF_CADRE_SUPERIEUR, SITE_UNKNOWN);

	// Remove contact in the database and check with a search
    database_remove(&database, "ZHOU", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "ZHOU", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);

    database_remove(&database, NULL, "Marie", QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, NULL, "Marie", QUALIF_UNKNOWN, SITE_UNKNOWN);

    database_search(&database, "A", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_remove(&database, "A", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "A", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);

    database_search(&database, "ZOUC", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_remove(&database, "ZOUC", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "ZOUC", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);

    database_search(&database, "Z", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_remove(&database, "Z", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "Z", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);

    database_search(&database, "E", "e", QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_remove(&database, "E", "e", QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "E", "e", QUALIF_UNKNOWN, SITE_UNKNOWN);

    database_search(&database, "O", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_remove(&database, "O", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);
    database_search(&database, "O", NULL, QUALIF_UNKNOWN, SITE_UNKNOWN);

	// Save (export) the current database in a CSV file
	database_save(&database, "Contacts-saved.csv");

    return 0;
}
