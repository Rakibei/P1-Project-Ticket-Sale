#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Purchasing of tickets/Purchase_tickets_functions.h"

void login(profile_struct* user, int nr_users, bool* next);
void regis();

int main()
{
    int choice = 1, balance = 1000, nr_users = 1;
    bool next = false;
    profile_struct user = {"Test", balance, NULL};

    do
    {
        printf("Do you wish to Login [1] or Register [2]?\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            login(&user, nr_users, &next);
        }
        else if (choice == 2)
        {
            regis();
        }
        else
        {
            exit(0);
        }
    } while(next == false);

    run_purchase_tickets(choice, &user);



    deallocate_ticket_list(&user.list_of_tickets);
    return 0;
}

void login(profile_struct* user, int nr_users, bool* next)
{
    char username[30],password[20];
    FILE *sc;
    accounts placeholder;

    sc = fopen("login.txt","r");
    if (sc == NULL)
    {
        printf("Error at opening File!");
        exit(1);
    }

    printf("Enter your username\n");
    scanf("%s", username);
    printf("Enter password\n");
    scanf("%s", password);

    for(int i = 0; i < nr_users; i++)
    {
        fscanf(sc, "%s\t%s", placeholder.username, placeholder.password);
        if(strcmp(username, placeholder.username) == 0 && strcmp(password, placeholder.password) == 0)
        {
            printf("\nSuccessful Login\n");
            strcpy(user->username, username);
            *next = true;
            break;
        }
    }
    fclose(sc);

    if(next == false)
    {
        printf("Username or Password is incorrect\n");
    }
}

void regis()
{
    int x;
    char username[30], password[30], repassword[30];
    FILE *sc;

    sc = fopen("login.txt","w");
    if (sc == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    printf("Please choose a username and password.\n");
    printf("Enter Username:\n");
    scanf(" %s", username);
    printf("Enter Password:\n");
    scanf(" %s", password);
    printf("Re-enter Password:\n");
    scanf(" %s", repassword);

    if (strcmp(repassword,password) == 0)
    {
        fprintf(sc, "%s\t%s\n", username, password);
        fclose(sc);
        printf("\nRegistration Successful!\n");
    }
    else
    {
        printf("Passwords did not match\n");
        regis();
    }
}