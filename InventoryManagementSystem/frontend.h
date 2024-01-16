#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 50
#define MAX_QUANTITY 65535
#define MAX_PRODUCT 65535

typedef struct {
    char id[10];
    char name[MAX_NAME];
    int quantity; 
    double price;
} Product;

typedef struct {
    Product products[MAX_PRODUCT];
    int count;
} ProductList;

void trimNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void readStringWithSpaces(char *output, int maxLen) {
    fgets(output, maxLen, stdin);
    trimNewline(output);
}

int generateProductId(ProductList *list) {
    int newId = 1;
    if (list->count > 0) {
        sscanf(list->products[list->count - 1].id, "%d", &newId);
        newId++;
    }
    return newId;
}

void printProduct(Product product) {
    printf("ID : %s\n", product.id);
    printf("Name: %s\n", product.name);
    printf("Price: %f\n",product.price);
    printf("Quantity: %d\n",product.quantity);
}

void printProductList(ProductList productList) {
    for (int i = 0; i < productList.count; ++i) {
        printf("Product %d:\n", i + 1);
        printProduct(productList.products[i]);
    }
}

void addProduct(ProductList *productList, Product product) {
    productList->products[productList->count] = product;
    productList->count++;
}

void removeProduct(ProductList *productList, int index) {
    for (int i = index; i < productList->count - 1; ++i) {
        productList->products[i] = productList->products[i + 1];
    }
    productList->count--;
}

void updateProduct(ProductList *productList, int index, Product product) {
    productList->products[index] = product;
}

int searchProduct(ProductList productList, char *data) {
    for (int i = 0; i < productList.count; ++i) {
        if (strcmp(productList.products[i].id, data) == 0 ||
            strcmp(productList.products[i].name, data) == 0 ||
            productList.products[i].price == (double)*data ||
            productList.products[i].quantity == (int)*data ) {
            return i;
        }
    }
    return -1;
}

void saveProductList(ProductList productList) {
    FILE *file = fopen("./product.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < productList.count; ++i) {
        fprintf(file, "%s\n", productList.products[i].id);
        fprintf(file, "%s\n", productList.products[i].name);
        fprintf(file, "%f\n", productList.products[i].price);
        fprintf(file, "%d\n", productList.products[i].quantity);
    }

    fclose(file);
}

ProductList loadProductList() {
    ProductList productList;
    productList.count = 0;

    FILE *file = fopen("./products.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char id[10];
    char name[MAX_NAME];
    int quantity; 
    double price;

    while (fscanf(file, "%s\n", id) != EOF) {
        fscanf(file, "%s\n", name);
        float price;
        fscanf(file, "%lf\n", &price);
        fscanf(file, "%d\n", &quantity);

        Product product;
        strcpy(product.id, id);
        strcpy(product.name, name);
        product.price = price;
        product.quantity = quantity;

        addProduct(&productList, product);

    }


    fclose(file);

    return productList;
}

