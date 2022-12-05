#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Purchasing of tickets/Purchase_tickets_functions.h"

void login(profile_struct *user, int nr_users, bool *next);

void regis(int* nr_users);

void view_tickets(int nr_tickets, profile_struct* user);

void run_navigation_menu(profile_struct *user, int nr_users, bool next);

void auth_menu(profile_struct *user, int choice, int nr_users, bool next);

void run_profile(profile_struct *user, int* logout);


int main()
{
    int choice = 1, balance = 1000, nr_users = 1;//nr_users should be updated on the server side.
    bool next = false;                           //We must do it manually.
    profile_struct user = {"Test", balance, NULL};

    auth_menu(&user, choice, nr_users, next);

    run_navigation_menu(&user, nr_users, next);

    deallocate_ticket_list(&user.list_of_tickets);

    return 0;
}


void auth_menu(profile_struct *user, int choice, int nr_users, bool next)
{
    do
    {
        printf("Do you wish to Login [1] or Register [2]?\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            login(user, nr_users, &next);
        }
        else if (choice == 2)
        {
            regis(&nr_users);
        }
        else
        {
            exit(0);
        }
    } while(next == false);
}


void run_navigation_menu(profile_struct *user, int nr_users, bool next)//this is the menu function
{
    int logout = 0;
    int choice = 1;
    next == true;

    while (true)
    {
        printf("1) Purchase ticket\n");
        printf("2) Logout\n");
        printf("3) Profile Menu\n");
        printf("4) Exit program\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_tickets(4, user);//We have 4 tickets in the temp file right now.
                break;

            case 2:
                auth_menu(user, choice, nr_users, next);

                break;

            case 3:
                run_profile(user,&logout);
                if (logout == 1){
                    auth_menu(user, choice, nr_users, next);
                }

                break;

            case 4:
                exit(0);

            default:
                printf("incorrect input\n");
        }
    }
}


void login(profile_struct* user, int nr_users, bool* next)
{
    char username[30],password[20];
    FILE *sc;
    accounts placeholder;

    sc = fopen("server_users.txt","r");
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


void regis(int* nr_users)
{
    int x;
    char username[30], password[30], repassword[30];
    FILE *sc;

    sc = fopen("server_users.txt","a");//a means "update file or create new"
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
        *nr_users = *nr_users + 1;
    }
    else
    {
        printf("Passwords did not match\n");
        regis(nr_users);
    }
}


void view_tickets(int nr_tickets, profile_struct* user)
{
    int temp, choice = 0;
    ticket_struct tickets[nr_tickets];
    FILE* ticket_file;

    ticket_file = fopen("ticket_list.txt","r");
    if (ticket_file == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    for(int i = 0; i < nr_tickets; i++)
    {
        fscanf(ticket_file,"%s - %d\n", tickets[i].location, &temp);
        tickets[i].time = temp;
    }
    fclose(ticket_file);

    temp = 0;
    do{
        printf("Ticket-%d\n%s - %d\n", (temp + 1), tickets[temp].location, tickets[temp].time);
        printf("Type the number corresponding to your choice:\n"
               "[1] Buy ticket\t[2] Next ticket\t[3] Previous ticket\t[4] Back\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                run_purchase_tickets(1, user, tickets[temp]);
                break;
            case 2:
                temp = temp + 1;
                if(temp > nr_tickets)
                {
                    temp = temp - 1;
                    printf("There are no next ticket.\n");
                }
                break;
            case 3:
                temp = temp - 1;
                if(temp > nr_tickets)
                {
                    temp = temp + 1;
                    printf("There are no previous ticket.\n");
                }
                break;
            case 4:
                choice = -1;//temporary, should send to main menu.
                break;
            default:
                printf("wrong input, try again.\n");
                break;
        }
    } while(choice >= 0);
}