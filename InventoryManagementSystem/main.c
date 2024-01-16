#include <frontend.h>

int main() {
    ProductList productList = loadProductList();

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