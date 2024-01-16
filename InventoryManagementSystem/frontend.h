#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 50
#define MAX_QUANTITY 999
#define MAX_EMPLOYEES 100

typedef struct {
    char id[10];
    char name[MAX_NAME];
    int quantity; 
    double price;
} Product;

typedef struct {
    Product products[MAX_EMPLOYEES];
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
    FILE *file = fopen("../employees.txt", "w");
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

    FILE *file = fopen("../products.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char id[10];
    char name[MAX_NAME];
    int quantity; 
    double price;

    while (fscanf(file, "%s\n", name) != EOF) {
        strcpy(productList.products[productList.count].name, name);
        fscanf(file, "%s\n", phone);
        strcpy(productList.products[productList.count].phone, phone);
        fscanf(file, "%s\n", email);
        strcpy(productList.products[productList.count].email, email);
        fscanf(file, "%s\n", address);
        strcpy(productList.products[productList.count].address, address);
        fscanf(file, "%d\n", &age);
        employeeList.employees[employeeList.count].age = age;
        fscanf(file, "%s\n", role);
        strcpy(employeeList.employees[employeeList.count].role, role);

        employeeList.count++;
    }

    fclose(file);

    return employeeList;
}

int main() {
    EmployeeList employeeList = loadEmployeeList();

    while (true) {
        #ifdef _WIN32
                system("cls");
        #else
                system("clear");
        #endif
        printf(" _____ _____ _____ _____ _____\n");
        printf("|   __|   __|  _  |_   _|   __|\n");
        printf("|   __|__   |     | | | |__   |\n");
        printf("|_____|_____|__|__| |_| |_____|\n\n\n\n");
        printf("\n\t **** Welcome to Contact Management System ****");
        printf("\n\n\n\t\t\tMAIN MENU");
        printf("\n\t\t=====================");
        printf("\n\t\t[1] Add a new Employee");
        printf("\n\t\t[2] Remove an employee");
        printf("\n\t\t[3] Edit an employee");
        printf("\n\t\t[4] Search an employee");
        printf("\n\t\t[5] Print all employees");
        printf("\n\t\t[6] Exit");
        printf("\n\t\t=================\n\t\t");

        int choice;
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 1) {
            Employee employee;
            int newId = generateEmployeeId(&employeeList);
            snprintf(employee.id, sizeof(employee.id), "%d", newId);

            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
            printf("\n\n\n\t\t\tEmployee Creation");
            printf("\n\t\t=====================");
            printf("\n\t\tEnter name: ");
            readStringWithSpaces(employee.name, MAX_NAME);
            printf("\n\t\tEnter phone: ");
            readStringWithSpaces(employee.phone, MAX_PHONE);
            printf("\n\t\tEnter email: ");
            readStringWithSpaces(employee.email, MAX_EMAIL);
            printf("\n\t\tEnter address: ");
            readStringWithSpaces(employee.address, MAX_ADDRESS);
            printf("\n\t\tEnter age: ");
            scanf("%d", &employee.age);
            getchar();
            printf("\n\t\tEnter role: ");
            readStringWithSpaces(employee.role, MAX_ROLE);
            printf("\n\t\t=====================");

            addEmployee(&employeeList, employee);
        } else if (choice == 2) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
            printf("\n\n\n\t\t\tEmployee Deletion");
            printf("\n\t\t=====================");
            printf("\n\t\tEnter any user information (Role, Phone number, etc.) : ");
            char data[MAX_ADDRESS];
            scanf("%s", data);
            int index = searchEmployee(employeeList, data);
            if (index == -1) {
                printf("\n\t\tEmployee not found!\n");
            } else {
                removeEmployee(&employeeList, index);
            }
        } else if (choice == 3) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
            printf("\n\n\n\t\t\tEmployee Edition");
            printf("\n\t\t=====================");
            printf("Enter any user information (Role, Phone number, etc.) : ");
            char data[MAX_ADDRESS];
            scanf("%s", data);

            int index = searchEmployee(employeeList, data);
            if (index == -1) {
                printf("Employee not found!\n");
            } else {
                #ifdef _WIN32
                                system("cls");
                #else
                                system("clear");
                #endif
                Employee employee;
                printf("\n\n\n\t\t\tEdit Employee");
                printf("\n\t\t=====================");
                printf("\n\t\tEnter name: ");
                readStringWithSpaces(employee.name, MAX_NAME);
                printf("\n\t\tEnter phone: ");
                readStringWithSpaces(employee.phone, MAX_PHONE);
                printf("\n\t\tEnter email: ");
                readStringWithSpaces(employee.email, MAX_EMAIL);
                printf("\n\t\tEnter address: ");
                readStringWithSpaces(employee.address, MAX_ADDRESS);
                printf("\n\t\tEnter age: ");
                scanf("%d", &employee.age);
                getchar();
                printf("\n\t\tEnter role: ");
                readStringWithSpaces(employee.role, MAX_ROLE);
                printf("\n\t\t=====================");

                updateEmployee(&employeeList, index, employee);
            }
        } else if (choice == 4) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
            printf("\n\n\n\t\t\tEmployee Search");
            printf("\n\t\t===============================\n");
            printf("\t\tEnter any user information \n\t\t(Role, Phone number, etc.) : ");
            char data[MAX_ADDRESS];
            scanf("%s", data);

            int index = searchEmployee(employeeList, data);
            if (index == -1) {
                printf("Employee not found!\n");
            } else {
                printEmployee(employeeList.employees[index]);
            }
        } else if (choice == 5) {
            printEmployeeList(employeeList);
        } else if (choice == 6) {
            saveEmployeeList(employeeList);
            break;
        }
    }
}

// Path: main.c