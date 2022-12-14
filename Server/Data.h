//
// Created by alexa on 06/12/2022.
//

#ifndef P1_PROJECT_DATA_H
#define P1_PROJECT_DATA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NORMAL_PRICE 100
#define VIP_PRICE 200

typedef struct{
    char category[20];
    char genre[20];
    char performing[20];
    char opponent[20];
    char time[20];
    char date[20];
    char location[30];
    int available;
    char type[20];
    char price[20];
} ticket_struct;

typedef struct ticket_node{
    ticket_struct ticket;
    struct ticket_node* next;
} ticket_node;

typedef struct{
    ticket_node* head;
} ticket_list;

typedef struct{
    char username[30];
    int balance;
    ticket_list list_of_tickets;
} profile_struct;

typedef struct{
    char username[30];
    char password[30];
    int balance;
} accounts;

void login(profile_struct *user, int nr_users, bool *next);
void regis(int* nr_users);
void view_tickets(int nr_tickets, profile_struct* user);
void run_navigation_menu(profile_struct *user, int* nr_users, bool next);
void main_menu(profile_struct *user, int choice, int* nr_users, bool next);
void run_profile(profile_struct *user, int* logout, int* nr_users,profile_struct* my_profile);
void print_tickets(profile_struct* my_profile);
void profile_balance(profile_struct* my_profile);
void delete_profile(profile_struct* user, int* nr_users);
void run_purchase_tickets(int choice, profile_struct* user, ticket_struct new_ticket);
int amount_of_tickets(int *number_of_tickets, int *amount_choice);
int type_of_ticket(int *ticket_type, int *ticket_choice);
int payment(int *checkout_choice, int ticket_type, int number_of_tickets, profile_struct* user, ticket_struct new_ticket);
void update_profile(ticket_struct new_ticket, profile_struct* my_profile, int prize);
void run_return_tickets(profile_struct* my_profile);
void initialize(profile_struct* my_profile);
void nr_users_on_server(int* nr_users);
void update_nr_users_on_server(int nr_users);
void update_available_tickets(ticket_struct changed_ticket, bool buy);
void update_balance(profile_struct* my_profile, int nr_users);
#endif //P1_PROJECT_DATA_H