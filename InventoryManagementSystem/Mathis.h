
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char id[10];
    char name[50];
    int quantity;
    double price;
} Product_t;

#define MAX_PRODUCTS 10
#define DB_FILE "database.bin"

Product_t products[MAX_PRODUCTS];
int num_products = 0;


// LOAD DATABASE ====================================
int LoadDatabase(Product_t *products, int *num_products) {
    FILE *file = fopen(DB_FILE, "rb");
    if (!file) {
        perror("Error opening database file");
        return -1;  // Return an error code
    }

    int read_count = fread(products, sizeof(Product_t), MAX_PRODUCTS, file);
    if (read_count != MAX_PRODUCTS) {
        if (feof(file)) {
            printf("End of file reached, %d products loaded\n", read_count);
        } else if (ferror(file)) {
            perror("Error reading database file");
            fclose(file);
            return -1;
        }
    }

    *num_products = read_count;

    fclose(file);
    return 0;  // Success
}

// SAVE DATABASE ==============================

int SaveDatabase(const Product_t *products, int num_products) {
    FILE *file = fopen(DB_FILE, "wb");
    if (!file) {
        perror("Error opening database file for writing");
        return -1;  // Return an error code
    }

    int write_count = fwrite(products, sizeof(Product_t), num_products, file);
    if (write_count != num_products) {
        perror("Error writing to database file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;  // Success
}


// ADD PRODUCT ===============================================
Product_t products[MAX_PRODUCTS];
int num_products;

int AddProduct() {
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
    if (quantity < 0 || price < 0.0) {
        printf("Invalid input: Negative values are not allowed.\n");
        return -1;
    }

    // Check if the product already exists
    bool exists = false;
    for (int i = 0; i < num_products; i++) {
        if (strcmp(products[i].id, id) == 0) {
            exists = true;
            products[i].quantity += quantity; // Update quantity
            products[i].price = price;        // Update price
            break;
        }
    }

    // Add a new product if it does not exist
    if (!exists) {
        if (num_products >= MAX_PRODUCTS) {
            printf("Error: Inventory is full.\n");
            return -1;
        }
        strcpy(products[num_products].id, id);
        strcpy(products[num_products].name, name);
        products[num_products].quantity = quantity;
        products[num_products].price = price;
        num_products++;
    }

    return 0;  // Success
}

// REMOVE PRODUCT ====================================================

int RemoveProduct() {
    char id[10];
    printf("Enter product ID to remove from stock: ");
    scanf("%9s", id);

    int remove_quantity;
    printf("Enter quantity to remove: ");
    scanf("%d", &remove_quantity);

    // Data validation for quantity
    if (remove_quantity <= 0) {
        printf("Invalid input: Quantity must be positive.\n");
        return -1;
    }

    // Search for the product
    bool found = false;
    for (int i = 0; i < num_products; i++) {
        if (strcmp(products[i].id, id) == 0) {
            found = true;
            if (products[i].quantity >= remove_quantity) {
                products[i].quantity -= remove_quantity; // Decrease stock
                printf("Product stock updated. New quantity: %d\n", products[i].quantity);
            } else {
                printf("Insufficient stock. Available quantity: %d\n", products[i].quantity);
                return -1;
            }
            break;
        }
    }

    if (!found) {
        printf("Product ID not found in inventory.\n");
        return -1;
    }

    return 0;  // Success
}

// MODIFY ITEM ====================================================

int ModifyProduct() {
    char id[10];
    printf("Enter product ID to modify: ");
    scanf("%9s", id);

    // Search for the product
    int index = -1;
    for (int i = 0; i < num_products; i++) {
        if (strcmp(products[i].id, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Product ID not found in inventory.\n");
        return -1;
    }

    int choice;
    printf("Select attribute to modify:\n");
    printf("1. Name\n2. Quantity\n3. Price\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Modify name
            printf("Enter new name: ");
            scanf("%49s", products[index].name);
            break;

        case 2: // Modify quantity
            printf("Enter new quantity: ");
            scanf("%d", &products[index].quantity);
            if (products[index].quantity < 0) {
                printf("Invalid input: Negative quantity is not allowed.\n");
                return -1;
            }
            break;

        case 3: // Modify price
            printf("Enter new price: ");
            scanf("%lf", &products[index].price);
            if (products[index].price < 0.0) {
                printf("Invalid input: Negative price is not allowed.\n");
                return -1;
            }
            break;

        default:
            printf("Invalid choice.\n");
            return -1;
    }

    printf("Product modified successfully.\n");
    return 0;  // Success
}

// WRITE REPORT =====================================================

int WriteReport() {
    char report_name[100];
    printf("Enter report name: ");
    scanf("%99s", report_name);

    char report_content[1024];
    printf("Enter report content (max 1024 characters): ");
    scanf("%1023s", report_content);

    char report_file_name[120];
    snprintf(report_file_name, sizeof(report_file_name), "%s.txt", report_name);

    FILE *file = fopen(report_file_name, "w");
    if (!file) {
        perror("Error opening report file for writing");
        return -1;
    }

    fprintf(file, "Report Name: %s\n\n", report_name);
    fprintf(file, "Content:\n%s\n", report_content);

    fclose(file);
    printf("Report '%s' saved successfully.\n", report_name);
    return 0;  // Success
}


// DISPLAY TRANSACTION MENU =================================

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

// DISPLAY INVENTORY MENU ==============================

void InventoryMenu() {
    int choice;
    do {
        printf("\n--- Inventory Menu ---\n");
        printf("1. Display the whole inventory\n");
        printf("2. Search an item\n");
        printf("9. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Placeholder for inventory functions
        // TODO: Implement DisplayInventory and SearchProduct

        switch (choice) {
            case 9:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
}

// DISPLAY REPORTS MENU ===============================

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

        // Placeholder for reports functions
        // TODO: Implement ListReports and WriteReport

        switch (choice) {
            case 2:
                WriteReport();
            case 9:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
}
    
// DISPLAY MAIN MENU ==========================================

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
    } 
    while (choice != 9);
}
