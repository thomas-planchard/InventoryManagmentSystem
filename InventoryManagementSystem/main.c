// path/filename: inventory_management_system.c
#include "back.h"

// Main function to start the program
int main() 
{
    // Load the database
    if (LoadDatabase(products, &num_products) != 0) 
        {
        printf("Failed to load database. Exiting.\n");
        return 1;
        }

    // Display the main menu
    DisplayMainMenu();

    // Save any changes to the database before exiting
    if (SaveDatabase(products, num_products) != 0) {
        printf("Failed to save database. Data may be lost.\n");
    }

    return 0;

}