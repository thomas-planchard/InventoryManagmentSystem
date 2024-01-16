#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product
{
    char id[10];
    char name[50];
    int quantity;
    int price;
} product_t;

/**
 * This function creates a file with every products specified in an array of products
 * @param filename (char pointer): the name of the txt file.
 * @param products (product_t array): the array of products.
 * @param length (int): the length of the array.
 * @result  It returns 0 if the writting is successful and 1 if it fails.
*/
int CreateFile(char *filename, product_t products[], int length)
{
    // Check if the file is a .txt or not
    char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".txt") != 0)
    {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(filename, "w");

    for (int count = 0; count < length; count++)
    {
        fprintf(file, "Product n°:%s\n", products[count].id);
        fprintf(file, "Name :%s\n", products[count].name);
        fprintf(file, "Price:%d\n", products[count].quantity);
        fprintf(file, "Product n°:%d\n\n", products[count].price);
    }
    fclose(file);
}

/**
 * This function deletes a file with every products specified in an array of products
 * @param filename (char pointer): the name of the txt file.
 * @result  It returns 0 if the deleting is successful and 1 if it fails.
*/
int DeleteFile(char *filename){
    int result= remove(filename);
    return result;
}
