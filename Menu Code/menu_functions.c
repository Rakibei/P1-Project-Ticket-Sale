#include <stdlib.h>
#include <stdio.h>
#include "menu_functions.h"
#include "../Login Code/login_functions.h"

void menu(int x) {
    int option, j = 10, l = 2;
    if (x == 1) {
        printf("Press the number corresponding to the menu you want to enter\n");
        /*scanf("%i", &option);
        while (l < j) {
            printf("%i. TEAM vs TEAM", l);
            l++;
            if (option == l) {
                printf("You selected something");
            }
        } */
    } else {
        printf("%i", x);
        exit(2);
    }
}
