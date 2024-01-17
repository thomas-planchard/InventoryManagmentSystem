#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "back.h"

// LOAD DATABASE TESTS =================================================================

void TestLoadDatabase_Success() {
    Product_t testProducts[MAX_PRODUCTS];
    int testNumProducts = 0;

    // Ensure the bin exists and is in the correct format

    int result = LoadDatabase(testProducts, &testNumProducts);
    assert(result == 0);  
    assert(testNumProducts > 0);  
    printf("TestLoadDatabase_Success passed\n");
}

void TestLoadDatabase_FileOpenFailure() {
    Product_t testProducts[MAX_PRODUCTS];
    int testNumProducts = 0;

    // Rename or remove the bin temporarily

    int result = LoadDatabase(testProducts, &testNumProducts);
    assert(result == -1);  // Assert that LoadDatabase returns failure
    printf("TestLoadDatabase_FileOpenFailure passed\n");

}

// SAVE DATABASE TESTS =================================================================

void TestSaveDatabase_Success() {
    Product_t testProducts[MAX_PRODUCTS];
    int testNumProducts = 2; // Assuming we have 2 products for testing

    // Populate testProducts with dummy data

    int result = SaveDatabase(testProducts, testNumProducts);
    assert(result == 0);  // Assert that SaveDatabase returns success

    // Optionally, verify the file's existence and content
    printf("TestSaveDatabase_Success passed\n");
}

void TestSaveDatabase_FileOpenFailure() {
    Product_t testProducts[MAX_PRODUCTS];
    int testNumProducts = 2; // Assuming we have 2 products for testing

    // Ensure the bin cannot be opened (e.g., by setting inappropriate permissions)

    int result = SaveDatabase(testProducts, testNumProducts);
    assert(result == -1);  // Assert that SaveDatabase returns failure
    printf("TestSaveDatabase_FileOpenFailure passed\n");

}


// MAIN TEST FUNCTION =======================================================================

int main() {
    TestSaveDatabase_Success();
    TestSaveDatabase_FileOpenFailure();

    TestLoadDatabase_Success();
    TestLoadDatabase_FileOpenFailure();

    printf("All tests passed!\n");
    return 0;
}

