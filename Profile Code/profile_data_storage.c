//
// Created by alexa on 21/11/2022.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char location[30];
    int time;
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
    int Saldo;
    ticket_list list_of_tickets;
} profile_struct;
/**
 * Adds the new_ticket to the list of tickets under my_profile. Afterwards the Profile along with
 * all its tickets are stored externally in the Profile_Data_Storage.txt file.
 * @param new_ticket = The ticket the user has purchased
 * @param my_profile = The user's profile
 * @param prize = The prize of the ticket
 */
void update_profile(ticket_struct new_ticket, profile_struct my_profile, int prize)
{
    ticket_node* new_node = (ticket_node*) malloc(sizeof(ticket_node));
    new_node->ticket = new_ticket;
    new_node->next = my_profile.list_of_tickets.head;
    my_profile.list_of_tickets.head = new_node;

    my_profile.Saldo = my_profile.Saldo - prize;

    FILE* storage = fopen("Profile_Data_Storage.txt", "w");
    fprintf(storage,"%s\n", my_profile.username);
    ticket_node* current = my_profile.list_of_tickets.head;
    while(current != NULL)
    {
        fprintf(storage,"%s - %d\n", current->ticket.location, current->ticket.time);
        current = current->next;
    }
    fclose(storage);
}
/**
 * Used to deallocate the memory used to store the user's tickets.
 * @param list = The list of tickets under the user's profile
 */
void deallocate_ticket_list(ticket_list* list)
{
    ticket_node* current = list->head;

    while(current != NULL)
    {
        ticket_node* next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
}