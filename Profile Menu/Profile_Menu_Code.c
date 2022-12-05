//
// Created by Mikkel on 29-11-2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Profile_Menu_Code.h"


#define MAX_LINES 100
#define MAX_LEN 1000

/**
 *
 * @param choice = What Profile Menu the user wants
 * @return the chosen choice
 */
int options(int *choice) {
    printf("1. My Tickets\n");
    printf("2. Balance\n");
    printf("3. Delete Profile\n");
    printf("4. Log Out\n");
    printf("5. Back to Main Menu\n");

    scanf("%d", choice);
    return *choice;
}

/**
 * Prints users tickets from .txt file
 */
void print_tickets(profile_struct* my_profile){
    int choice = 0;

    FILE *ifp;
    ifp = fopen("Profile_Data_Storage.txt", "r");


    /* Fejl besked hvis file pointer returnerer NULL*/
    if ((ifp = fopen("Profile_Data_Storage.txt", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        exit(1);
    }


    /* Hvis file pointer ikke retunerer NULL kører dette*/
    /* Printer billetter fra .txt fil */
    char txt[] = ".txt";
    char filename[35];
    strcat(filename, my_profile->username);
    strcat(filename,txt);
    char s;

    while((ifp = fopen(filename, "r")) != NULL) {
        while(s != EOF) {
            s = fgetc(ifp);
            printf("%c", s);

        }
    }
    fclose(ifp);
    printf("\nPress 1 to go back \n");
    scanf("%d", &choice);
    if (choice == 1){
        /* Go back */
    }
}

/**
 * Displays users balance and can add a deposit to balance
 * @param my_profile = The users profile
 */
void profile_balance(profile_struct* my_profile) {
    int b_choice;
    printf("Your balance is %d\n", my_profile->balance);
    printf("1. Deposit balance\n");
    printf("2. Go back\n");
    scanf("%d", &b_choice);

    if (b_choice == 1) {
        int deposit, choice;
        printf("Amount to be deposited: \n");
        scanf("%d", &deposit);
        my_profile->balance = my_profile->balance + deposit;
        printf("New balance is: %d", my_profile->balance);

        printf("\nPress 1 to go back \n");
        scanf("%d", &choice);
        if (choice == 1) {
            /* Go back */
        }
    }
    if (b_choice == 2) {
        /* Go back */
    }

}

/**
 * Deletes logged in user from server_users.txt file
 * @param user = The logged in user
 */
void delete_profile( profile_struct* user){

    char data[MAX_LINES];

    FILE *ifp;
    ifp = fopen("server_users.txt", "r");

    /* This section gets liens from server_users.txt and saves each line as individual elements of char array data*/
    if (ifp == NULL){
        printf("Error opening file.\n");
    }

    int line = 0;
    while(!feof(ifp) && !ferror(ifp)){
        if(fgets(&data[line], MAX_LEN, ifp) != NULL){
            line++;
        }
    }
    fclose(ifp);


    /* This section writes all lines from data array into server_users.txt as long as the current logged in users username isn't part of the string*/
    ifp = fopen("server_users.txt", "w");

    int linew = 0;

    while(!feof(ifp) && !ferror(ifp)){
        if(strstr(&data[linew], user->username) == NULL){       /*  if strstr returns NULL username isnt part of data line, and is not the username being searched for*/
            printf("%s", &data[linew]);
            linew++;
        }
    }
    fclose(ifp);

}


/**
 *
 * @param user = The logged in user
 * @param logout = Tells run_navigation_menu if user wants to log out
 */
void run_profile(profile_struct* user, int* logout){
    int choice;

    options(&choice);

    if (choice == 1){
        print_tickets(user);
    }

    if (choice == 2){
        profile_balance(user);
    }

    if (choice == 3){
        /* Delete profile*/
        delete_profile(user);
        *logout = 1;
    }

    if (choice == 4){
        /* Log out, go back to log in menu */
        *logout = 1;

    }

}