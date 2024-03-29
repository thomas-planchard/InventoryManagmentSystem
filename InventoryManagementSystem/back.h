
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>  

typedef struct
{
    char id[10];
    char name[50];
    int quantity;
    double price;
} Product_t;

#define MAX_PRODUCTS 10
#define DB_FILE "database.bin"

Product_t products[MAX_PRODUCTS];
int num_products = 0;

void printProduct(Product_t product) {
    printf("ID : %s\n", product.id);
    printf("Name: %s\n", product.name);
    printf("Price: %f\n",product.price);
    printf("Quantity: %d\n",product.quantity);
}

void printProductList(Product_t products[MAX_PRODUCTS], int num_products) {
    for (int i = 0; i < num_products; ++i) {
        printf("Product %d:\n", i + 1);
        printProduct(products[i]);
    }
}

/**
 * This function loads the database into the memory.
 * @param products (product_t): this is a product.
 * @param num_products this is the number of product.
 * @result return 0 if sucess, -1 if failure.
 */
int LoadDatabase(Product_t *products, int *num_products)
{
    FILE *file = fopen(DB_FILE, "rb");
    if (!file)
    {
        perror("Error opening database file");
        return -1; // Return an error code
    }

    int read_count = fread(products, sizeof(Product_t), MAX_PRODUCTS, file);
    if (read_count != MAX_PRODUCTS)
    {
        if (feof(file))
        {
            printf("End of file reached, %d products loaded\n", read_count);
        }
        else if (ferror(file))
        {
            perror("Error reading database file");
            fclose(file);
            return -1;
        }
    }

    *num_products = read_count;

    fclose(file);
    return 0; // Success
}

// SAVE DATABASE ==============================

/**
 * This function saves a bin file named database.
 * @param products (product_t): this is a product.
 * @param num_products this is the number of product.
 * @result return 0 if sucess, -1 if failure.
 */
int SaveDatabase(const Product_t *products, int num_products)
{
    FILE *file = fopen(DB_FILE, "wb");
    if (!file)
    {
        perror("Error opening database file for writing");
        return -1; // Return an error code
    }

    int write_count = fwrite(products, sizeof(Product_t), num_products, file);
    if (write_count != num_products)
    {
        perror("Error writing to database file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0; // Success
}

// ADD PRODUCT ===============================================

Product_t products[MAX_PRODUCTS];
int num_products;

/**
 * This function adds a product into the the database.
 * @result return 0 if sucess, -1 if failure.
 */
int AddProduct()
{
    char id[10];
    printf("Enter product ID: ");
    scanf("%9s", id);

    char name[50];
    printf("Enter product name: ");
    scanf("%49s", name);

    int quantity;
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    double price;
    printf("Enter price: ");
    scanf("%lf", &price);

    // Data validation
    if (quantity < 0 || price < 0.0)
    {
        printf("Invalid input: Negative values are not allowed.\n");
        return -1;
    }

    // Check if the product already exists
    bool exists = false;
    for (int i = 0; i < num_products; i++)
    {
        if (strcmp(products[i].id, id) == 0)
        {
            exists = true;
            products[i].quantity += quantity; // Update quantity
            products[i].price = price;        // Update price
            break;
        }
    }

    // Add a new product if it does not exist
    if (!exists)
    {
        if (num_products >= MAX_PRODUCTS)
        {
            printf("Error: Inventory is full.\n");
            return -1;
        }
        strcpy(products[num_products].id, id);
        strcpy(products[num_products].name, name);
        products[num_products].quantity = quantity;
        products[num_products].price = price;
        num_products++;
    }

    return 0; // Success
}

// REMOVE PRODUCT ====================================================

/**
 * This function removes a product from the the database.
 * @result return 0 if sucess, -1 if failure.
 */
int RemoveProduct()
{
    char id[10];
    printf("Enter product ID to remove from stock: ");
    scanf("%9s", id);

    int remove_quantity;
    printf("Enter quantity to remove: ");
    scanf("%d", &remove_quantity);

    // Data validation for quantity
    if (remove_quantity <= 0)
    {
        printf("Invalid input: Quantity must be positive.\n");
        return -1;
    }

    // Search for the product
    bool found = false;
    for (int i = 0; i < num_products; i++)
    {
        if (strcmp(products[i].id, id) == 0)
        {
            found = true;
            if (products[i].quantity >= remove_quantity)
            {
                products[i].quantity -= remove_quantity; // Decrease stock
                printf("Product stock updated. New quantity: %d\n", products[i].quantity);
            }
            else
            {
                printf("Insufficient stock. Available quantity: %d\n", products[i].quantity);
                return -1;
            }
            break;
        }
    }

    if (!found)
    {
        printf("Product ID not found in inventory.\n");
        return -1;
    }

    return 0;
}

// MODIFY ITEM ====================================================

/**
 * This function modify a product from the the database.
 * @result return 0 if sucess, -1 if failure.
 */
int ModifyProduct()
{
    char id[10];
    printf("Enter product ID to modify: ");
    scanf("%9s", id);

    // Search for the product
    int index = -1;
    for (int i = 0; i < num_products; i++)
    {
        if (strcmp(products[i].id, id) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Product ID not found in inventory.\n");
        return -1;
    }

    int choice;
    printf("Select attribute to modify:\n");
    printf("1. Name\n2. Quantity\n3. Price\nChoice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Modify name
        printf("Enter new name: ");
        scanf("%49s", products[index].name);
        break;

    case 2: // Modify quantity
        printf("Enter new quantity: ");
        scanf("%d", &products[index].quantity);
        if (products[index].quantity < 0)
        {
            printf("Invalid input: Negative quantity is not allowed.\n");
            return -1;
        }
        break;

    case 3: // Modify price
        printf("Enter new price: ");
        scanf("%lf", &products[index].price);
        if (products[index].price < 0.0)
        {
            printf("Invalid input: Negative price is not allowed.\n");
            return -1;
        }
        break;

    default:
        printf("Invalid choice.\n");
        return -1;
    }

    printf("Product modified successfully.\n");
    return 0;
}

int ListReports() {
    const char *directory = ".";  // Assuming reports are in the current directory
    DIR *dir = opendir(directory);
    if (!dir) {
        perror("Unable to open directory");
        return -1;
    }
    struct dirent *entry;
    printf("Available Reports:\n");
    while ((entry = readdir(dir)) != NULL) {
        // Check if the file is a report (e.g., .txt extension)
        if (strstr(entry->d_name, ".txt")) {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
    return 0;  // Success
}

// WRITE REPORT =====================================================

int WriteReport()
{
    char report_name[100];
    printf("Enter report name: ");
    scanf("%99s", report_name);

    char report_content[1024];
    printf("Enter report content (max 1024 characters): ");
    scanf("%1023s", report_content);

    char report_file_name[120];
    snprintf(report_file_name, sizeof(report_file_name), "%s.txt", report_name);

    FILE *file = fopen(report_file_name, "w");
    if (!file)
    {
        perror("Error opening report file for writing");
        return -1;
    }

    fprintf(file, "Report Name: %s\n\n", report_name);
    fprintf(file, "Content:\n%s\n", report_content);

    fclose(file);
    printf("Report '%s' saved successfully.\n", report_name);
    return 0;
}



 int SearchProduct( Product_t *products, int num_products)
{
    char id[10];
    printf("Enter product ID to search: ");
    scanf("%9s", id);
    printf("----------------------\n");
    // Search for the product
    int index = -1;
    for (int i = 0; i < num_products; i++)
    {
        if (strcmp(products[i].id, id) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Product ID not found in inventory.\n");
        return -1;
    }

    printf("Product found:\n");
    printProduct(products[index]);
    printf("----------------------\n");

    int choice;
    printf("Select attribute to modify:\n");
    printf("1. Name\n2. Quantity\n3. Price\nChoice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Modify name
        printf("Enter new name: ");
        scanf("%49s", products[index].name);
        break;

    case 2: // Modify quantity
        printf("Enter new quantity: ");
        scanf("%d", &products[index].quantity);
        if (products[index].quantity < 0)
        {
            printf("Invalid input: Negative quantity is not allowed.\n");
            return -1;
        }
        break;

    case 3: // Modify price
        printf("Enter new price: ");
        scanf("%lf", &products[index].price);
        if (products[index].price < 0.0)
        {
            printf("Invalid input: Negative price is not allowed.\n");
            return -1;
        }
        break;

    default:
        printf("Invalid choice.\n");
        return -1;
    }

    printf("Product modified successfully.\n");
    return 0;
}


/**
 * This function prints the transaction menu and enable the interactions with it.
 * @result Nothing.
 */
void TransactionMenu()
{
    int choice;
    do
    {
        printf("\n--- Transaction Menu ---\n");
        printf("1. Add a product\n");
        printf("2. Remove a product\n");
        printf("3. Modify a product\n");
        printf("9. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            AddProduct();
            break;
        case 2:
            RemoveProduct();
            break;
        case 3:
            ModifyProduct();
            break;
        case 9:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
}
/**
 * This function prints the menu of the inventory and enable the interactions with it.
 * @result Nothing.
 */
void InventoryMenu()
{
    int choice;
    do
    {
        printf("\n--- Inventory Menu ---\n");
        printf("1. Display the whole inventory\n");
        printf("2. Search an item\n");
        printf("9. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // TODO: Implement SearchProduct

        switch (choice)
        {
        case 1:
            printProductList(products, num_products);
        case 2:
            SearchProduct(products, num_products);
            break;
        case 9:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
}
/**
 * This function prints the menu of the reports of the inventory and enable the interactions with it.
 * @result Nothing.
 */
void ReportsMenu()
{
    int choice;
    do
    {
        printf("\n--- Reports Menu ---\n");
        printf("1. List Reports\n");
        printf("2. Write a new report\n");
        printf("9. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // TODO: Implement  WriteReport

        switch (choice)
        {
        case 1:
            ListReports();
            break;
        case 2:
            WriteReport();
            break;
        case 9:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
}
/**
 * This function prints the main menu of the inventory and enable the interactions with it.
 * @result Nothing.
 */
void DisplayMainMenu()
{
    int choice;
    do
    {
        printf("\n=== Main Menu ===\n");
        printf("1. Make a transaction\n");
        printf("2. Inventory\n");
        printf("3. Reports\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            TransactionMenu();
            break;
        case 2:
            InventoryMenu();
            break;
        case 3:
            ReportsMenu();
            break;
        case 9:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
}