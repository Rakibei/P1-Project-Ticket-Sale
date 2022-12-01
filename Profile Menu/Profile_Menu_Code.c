//
// Created by Mikkel on 29-11-2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Profile_Menu_Code.h"


#define FILENAME_SIZE 1024
#define MAX_LINE 2048

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
void print_tickets(){
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
    char s;
    while((ifp = fopen("Profile_Data_Storage.txt", "r")) != NULL) {
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


void delete_profile(profile_struct* my_profile){

    /* Stykket herunder finder den linje hvor username er i */
    /* https://stackoverflow.com/questions/61891221/c-program-to-print-line-number-in-which-given-string-exists-in-a-text-file */
    FILE *ifp, *temp;
    ifp = fopen("Profile_Data_Storage.txt", "r");
    char string[50];
    char student[100];
    strcpy (student, my_profile->username);
    int line_number = 1;

    while (fgets(string, sizeof string, ifp)) {
        if (strstr(string, student)) {
            printf("line number is: %d\n", line_number);
        }
        if (strchr(string, '\n')) {
            line_number += 1;
        }
        fclose(ifp);
    }



    /* ALT HERUNDER ER TIL AT SLETTE LINJE FUNDET HEROVER I FIL*/
    /* https://github.com/portfoliocourses/c-example-code/blob/main/delete_line.c */

    char temp_filename[FILENAME_SIZE];


    // creates a temp filename "temp___filename.txt" where filename.txt is the
    // name of the file entered by the user by first copying the prefix temp____
    // to temp_filename and then appending the original filename
    strcpy(temp_filename, "temp____");
    strcat(temp_filename, "Profile_Data_Storage.txt");

    // open the original file for reading and the temp file for writing
    ifp = fopen("Profile_Data_Storage.txt", "r");
    temp = fopen(temp_filename, "w");

    // will store each line in the file, and the line to delete
    char buffer[MAX_LINE];
    int delete_line = line_number;

    // if there was a problem opening either file let the user know what the error
    // was and exit with a non-zero error status
    if (ifp == NULL || temp == NULL)
    {
        printf("Error opening file(s)\n");
    }

    // current_line will keep track of the current line number being read
    bool keep_reading = true;
    int current_line = 1;
    do
    {
        // stores the next line from the file into the buffer
        fgets(buffer, MAX_LINE, ifp);

        // if we've reached the end of the file, stop reading from the file,
        // otherwise so long as the current line is NOT the line we want to
        // delete, write it to the file
        if (feof(ifp)){
            keep_reading = false;
        }
        else if (current_line != delete_line) {
            fputs(buffer, temp);
        }
        // keeps track of the current line being read
        current_line++;

    } while (keep_reading);

    // close our access to the files
    fclose(ifp);
    fclose(temp);

    // delete the original file, give the temp file the name of the original file
    remove("Profile_Data_Storage.txt");
    rename(temp_filename, "Profile_Data_Storage.txt");


    /* Go back to login/registration page */

}

void run_profile(profile_struct* user){
    int choice;
    options(&choice);

    if (choice == 1){
        print_tickets();
    }

    if (choice == 2){
        profile_balance(user);
    }

    if (choice == 3){
        /* Delete profile*/

    }

    if (choice == 4){
        /* Log out, go back to log in menu */
    }

    if (choice == 5){
        /* Go back */
    }

}