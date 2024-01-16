#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product
{
    char id[10];
    char name[50];
    int quantity;
    int price;
}product_t;


int CreateFile(char *filename, product_t products[],int length)
{
    // Check if the file is a .txt or not
    char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".txt") != 0)
    {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(filename, "w");
    
    for(int count=0;count<length;count++){
        fprintf(file,"Product n°:%s\n",products[count].id);
        fprintf(file,"Name :%s\n",products[count].name);
        fprintf(file,"Price:%d\n",products[count].quantity);
        fprintf(file,"Product n°:%d\n\n",products[count].price); 
    }


    fclose(file);
}