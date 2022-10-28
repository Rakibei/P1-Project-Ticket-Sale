#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    char username[30];
    char password[20];
};

int login(void) {
    char username[30],password[20];
    int succes;

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
            succes = 1;
        } else {
            printf("Username or Password is incorrect\n");
            printf("Username: %s and acc.username: %s\n", username, acc.username);
            printf("Password: %s and acc.password: %s\n", password, acc.password);
        }
    }

    fclose(sc);
    return succes;
}

void regis(void) {
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


    fwrite(&acc,sizeof(acc),1,sc);
    fclose(sc);
    printf("\nRegistration Successful!");
}

void s_option() {
    int option;

    printf("Press 1 to Login\nPress 2 to Register\n");
    scanf("%i", &option);
    if (option == 1) {
        login();
    } else if (option == 2){
        regis();
    } else {
        exit(0);
    }
}

int main() {
    s_option();
    return 0;
}