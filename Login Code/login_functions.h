#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef P1_PROJECT_FUNCTIONS_H
#define P1_PROJECT_FUNCTIONS_H

//Structures

struct Account {
    char username[30];
    char password[20];
};

//Functions

int login(int);

void regis(void);

void s_option();

#endif //P1_PROJECT_FUNCTIONS_H
