//
// Created by alexa on 06/12/2022.
//
#include "Data.h"

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

void nr_users_on_server(int* nr_users)
{
    FILE* server;
    server = fopen("../Server/nr_users.txt", "r");
    if(server == NULL)
    {
        fclose(server);
        server = fopen("../Server/nr_users.txt","w");
        fprintf(server,"%d", *nr_users);
        fclose(server);
    }
    else
    {
        fscanf(server,"%d", nr_users);
        fclose(server);
    }
}

void update_nr_users_on_server(int nr_users)
{
    FILE* server;
    server = fopen("../Server/nr_users.txt", "w");
    fprintf(server,"%d", nr_users);
    fclose(server);
}

void update_available_tickets(ticket_struct changed_ticket, bool buy)
{
    int nr_events = 10;//We currently have 10 different events
    int temp;
    ticket_struct list_of_events[50];
    FILE* file;

    file = fopen("../Server/List_of_events.txt","r");
    if (file == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    for(int i = 0; i < nr_events; i++)
    {
        fscanf(file,"%s  %s  %s  %s  %s  %s  %s  %d\n",
               list_of_events[i].category,
               list_of_events[i].genre,
               list_of_events[i].performing,
               list_of_events[i].opponent,
               list_of_events[i].time,
               list_of_events[i].date,
               list_of_events[i].location,
               &temp);
        list_of_events[i].available = temp;
    }
    fclose(file);

    file = fopen("../Server/List_of_events.txt","w");
    for(int i = 0; i < nr_events; i++)
    {
        if(strcmp(list_of_events[i].category, changed_ticket.category) == 0
            && strcmp(list_of_events[i].genre, changed_ticket.genre) == 0
            && strcmp(list_of_events[i].performing, changed_ticket.performing) == 0
            && strcmp(list_of_events[i].opponent, changed_ticket.opponent) == 0
            && strcmp(list_of_events[i].time, changed_ticket.time) == 0
            && strcmp(list_of_events[i].date, changed_ticket.date) == 0
            && strcmp(list_of_events[i].location, changed_ticket.location) == 0)
        {
            if(buy == true)
            {
                temp = list_of_events[i].available - 1;
            }
            else
            {
                temp = list_of_events[i].available + 1;
            }
            if(temp < 0)
            {
                temp = 0;
            }
        }
        else
        {
            temp = list_of_events[i].available;
        }
        fprintf(file,"%s  %s  %s  %s  %s  %s  %s  %d\n",
               list_of_events[i].category,
               list_of_events[i].genre,
               list_of_events[i].performing,
               list_of_events[i].opponent,
               list_of_events[i].time,
               list_of_events[i].date,
               list_of_events[i].location,
               temp);
    }
    fclose(file);
}

void update_balance(profile_struct* my_profile, int nr_users)
{
    FILE* file;
    accounts user_list[nr_users];

    file = fopen("../Server/server_users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
    }
    else
    {
        for(int i = 0; i < nr_users; i++)
        {
            fscanf(file,"%s\t%s\t%d", user_list[i].username, user_list[i].password, &user_list[i].balance);
        }
    }
    fclose(file);

    file = fopen("../Server/server_users.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
    }
    else
    {
        for(int i = 0; i < nr_users; i++)
        {
            if(strcmp(user_list[i].username,my_profile->username) == 0)
            {
                fprintf(file,"%s\t%s\t%d\n", user_list[i].username, user_list[i].password, my_profile->balance);
            }
            else
            {
                fprintf(file,"%s\t%s\t%d\n", user_list[i].username, user_list[i].password, user_list[i].balance);
            }
        }
    }
}