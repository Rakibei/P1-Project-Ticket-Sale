#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_functions.h"

int login(int i) {
    char username[30],password[20];
    int success;

    FILE *sc;
    sc = fopen("Login.txt","r");
    if (sc == NULL) {
        printf("Error at opening File!");
        exit(1);
    }

    struct Account acc;

    printf("Enter your username\n");
    scanf("%s", username);
    printf("Enter password\n");
    scanf("%s", password);

    while(fread(&acc,sizeof(acc),1,sc)) {
        if(strcmp(username,acc.username)==0 && strcmp(password,acc.password)==0) {
            printf("\nSuccessful Login\n");
            success = 1;
        } else {
            printf("Username or Password is incorrect\n");
            printf("Username: %s and acc.username: %s\n", username, acc.username);
            printf("Password: %s and acc.password: %s\n", password, acc.password);
        }
    }

    fclose(sc);
    return success;
}

void regis(void) {
    char rpassword[20];
    FILE *sc;

    sc=fopen("login.txt","w");
    if (sc == NULL) {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    struct Account acc;

    printf("Please choose a username and password.\n");
    printf("Enter Username:\n");
    scanf(" %s",acc.username);
    printf("Enter Password:\n");
    scanf(" %s",acc.password);
    printf("Re-enter Password:\n");
    scanf(" %s", rpassword);

    if (strcmp(rpassword,acc.password)==0) {
        fwrite(&acc,sizeof(acc),1,sc);
        fclose(sc);
        printf("\nRegistration Successful!\n");
        s_option();
    } else if (strcmp(rpassword,acc.password)!=0) {
        printf("Passwords did not match\n");
        regis();
    }

}

int s_option(int x) {
    int option;

    printf("Press 1 to Login\nPress 2 to Register\n");
    scanf("%i", &option);
    if (option == 1) {
        x = login(x);
        return x;
    } else if (option == 2){
        regis();
    } else {
        exit(0);
    }
}