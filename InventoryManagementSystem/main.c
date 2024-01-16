#include "frontend.h"

int main() {
    ProductList productList = loadProductList();

    while (true) {
        #ifdef _WIN32
                system("cls");
        #else
                system("clear");
        #endif
        printf(".___________.__    __   _______    .______    _______     _______.___________.     _______ .______       ______    __    __  .______   \n");   
        printf("|           |  |  |  | |   ____|   |   _  \  |   ____|   /       |           |    /  _____||   _  \     /  __  \  |  |  |  | |   _  \ \n");   
        printf("`---|  |----|  |__|  | |  |__      |  |_)  | |  |__     |   (----`---|  |----`   |  |  __  |  |_)  |   |  |  |  | |  |  |  | |  |_)  | \n");  
        printf("    |  |    |   __   | |   __|     |   _  <  |   __|       \   \       |  |        |  | |_ | |      /   |  |  |  | |  |  |  | |   ___/  \n"); 
        printf("    |  |    |  |  |  | |  |____    |  |_)  | |  |____.----)   |      |  |        |  |__| | |  |\  \----|  `--'  | |  `--'  | |  |  \n"); 
        printf("    |__|    |__|  |__| |_______|   |______/  |_______|_______/       |__|         \______| | _| `._____|\______/   \______/  | _|   \n\n\n\n");
        printf("\n\t **** Welcome to Inventory Management System ****");
        printf("\n\n\n\t\t\tMAIN MENU");
        printf("\n\t\t=====================");
        printf("\n\t\t[1] Add a new Product");
        printf("\n\t\t[2] Remove a product");
        printf("\n\t\t[3] Edit a product");
        printf("\n\t\t[4] Search a product");
        printf("\n\t\t[5] Print all product");
        printf("\n\t\t[6] Exit");
        printf("\n\t\t=================\n\t\t");

        int choice;
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 1) {
            Product product;
            int newId = generateProductId(&productList);
            snprintf(product.id, sizeof(product.id), "%d", newId);

            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
            printf("\n\n\n\t\t\tItem Creation");
            printf("\n\t\t=====================");
            printf("\n\t\tEnter name: ");
            readStringWithSpaces(product.name, MAX_NAME);
            printf("\n\t\tEnter quantity: ");
            char quantityString[MAX_QUANTITY];
            snprintf(quantityString, sizeof(quantityString), "%d", product.quantity);
            readStringWithSpaces(quantityString, MAX_QUANTITY);
            printf("\n\t\tEnter price: ");
            char priceString[MAX_QUANTITY];
            snprintf(priceString, sizeof(priceString), "%.2f", product.price);
            readStringWithSpaces(priceString, MAX_QUANTITY);

            addProduct(&productList, product);
        } else if (choice == 2) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
            printf("\n\n\n\t\t\tItem Deletion");
            printf("\n\t\t=====================");
            printf("\n\t\tEnter any user information : ");
            char data[MAX_QUANTITY];
            scanf("%s", data);
            int index = searchProduct(productList, data);
            if (index == -1) {
                printf("\n\t\tItem not found!\n");
            } else {
                removeProduct(&productList, index);
            }
        } else if (choice == 3) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
            printf("\n\n\n\t\t\tItem Edition");
            printf("\n\t\t=====================");
            printf("Enter any user information : ");
            char data[MAX_PRODUCT];
            scanf("%s", data);

            int index = searchProduct(productList, data);
            if (index == -1) {
                printf("Item not found!\n");
            } else {
                #ifdef _WIN32
                                system("cls");
                #else
                                system("clear");
                #endif
                Product product;
                printf("\n\n\n\t\t\tEdit Product");
                printf("\n\t\t=====================");
                printf("\n\t\tEnter name: ");
                readStringWithSpaces(&product.name, MAX_NAME);
                printf("\n\t\tEnter quantity: ");
                readStringWithSpaces(product.quantity, MAX_QUANTITY);
                printf("\n\t\tEnter price: ");
                char priceString[MAX_QUANTITY];
                snprintf(priceString, sizeof(priceString), "%.2f", product.price);
                readStringWithSpaces(priceString, MAX_QUANTITY);
                printf("\n\t\t=====================");

                updateProduct(&productList, index, product);
            }
        } else if (choice == 4) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
            printf("\n\n\n\t\t\t Product Search");
            printf("\n\t\t===============================\n");
            printf("\t\tEnter any user information \n\t\t(Role, Phone number, etc.) : ");
            char data[MAX_QUANTITY];
            scanf("%s", data);

            int index = searchProduct(productList, data);
            if (index == -1) {
                printf("Product not found!\n");
            } else {
                printProduct(productList.products[index]);
            }
        } else if (choice == 5) {
            printProductList(productList);
        } else if (choice == 6) {
            saveProductList(productList);
            break;
        }
    }
}

// Path: main.c