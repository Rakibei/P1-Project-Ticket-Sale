//
// Created by alexa on 06/12/2022.
//
#include "Data.h"
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

void initialize(profile_struct* my_profile)
{
    FILE* file;
    char txt[] = ".txt";
    char filename[35] = "../Server/";
    strcat(filename, my_profile->username);
    strcat(filename,txt);

    file = fopen(filename,"r");
    if(file == NULL)
    {
        fclose(file);
        file = fopen(filename,"w");
    }
    fclose(file);
}