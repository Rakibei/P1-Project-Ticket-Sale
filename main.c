#include "Server/Data.h"

int main()
{
    int choice = 1, balance = 1000, nr_users = 1;
    bool next = false;
    profile_struct user = {"Test", balance, NULL};
    nr_users_on_server(&nr_users);

    main_menu(&user, choice, &nr_users, next);

    run_navigation_menu(&user, &nr_users, next);

    return 0;
}
//###########################################################################//
//                                Menus                                      //
//###########################################################################//
void main_menu(profile_struct *user, int choice, int* nr_users, bool next)
{
    do
    {
        printf("[1] Login\n[2] Register\n[3] Exit program\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                login(user, *nr_users, &next);
                break;
            case 2:
                regis(nr_users);
                break;
            case 3:
                printf("%d", *nr_users);
                update_nr_users_on_server(*nr_users);
                exit(0);
                break;
            default:
                printf("Invalid Input!");
                break;
        }
    } while(next == false);
}

void run_navigation_menu(profile_struct *user, int* nr_users, bool next)//this is the menu function
{
    int logout = 0;
    int choice = 1;

    while (true)
    {
        printf("[1] Purchase tickets\n");
        printf("[2] Logout\n");
        printf("[3] Profile Menu\n");
        printf("[4] Exit program\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_tickets(10, user);//We have 10 tickets right now.
                break;

            case 2:
                main_menu(user, choice, nr_users, next);
                break;

            case 3:
                run_profile(user,&logout, nr_users, user);
                if (logout == 1){
                    main_menu(user, choice, nr_users, next);
                }
                break;

            case 4:
                printf("%d", *nr_users);
                update_nr_users_on_server(*nr_users);
                exit(0);

            default:
                printf("incorrect input\n");
        }
    }
}
//###########################################################################//
//                             Login & Register                              //
//###########################################################################//
void login(profile_struct* user, int nr_users, bool* next)
{
    char username[30],password[20];
    FILE *sc;
    accounts placeholder;

    sc = fopen("../Server/server_users.txt","r");
    if (sc == NULL)
    {
        printf("Error at opening File!");
        exit(1);
    }

    printf("Enter username\n");
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
            initialize(user);
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

    sc = fopen("../Server/server_users.txt","a");//a means "update file or create new"
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
//###########################################################################//
//                               Tickets                                     //
//###########################################################################//
void view_tickets(int nr_tickets, profile_struct* user)
{
    int temp, choice = 0;
    ticket_struct tickets[nr_tickets];
    FILE* ticket_file;

    ticket_file = fopen("../Server/List_of_events.txt","r");
    if (ticket_file == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    for(int i = 0; i < nr_tickets; i++)
    {
        fscanf(ticket_file,"%s  %s  %s  %s  %s  %s  %s  %d\n",
               tickets[i].category,
               tickets[i].genre,
               tickets[i].performing,
               tickets[i].opponent,
               tickets[i].time,
               tickets[i].date,
               tickets[i].location,
               &temp);
        tickets[i].available = temp;
    }
    fclose(ticket_file);

    temp = 0;
    do{
        if(strcmp("Sport",tickets[temp].category) == 0)
        {
            printf("Number %d)\n%s %s - %s vs %s - %s: %d available\n", (temp + 1),
                   tickets[temp].date,
                   tickets[temp].time,
                   tickets[temp].performing,
                   tickets[temp].opponent,
                   tickets[temp].location,
                   tickets[temp].available);
        }
        else
        {
            printf("Number %d)\n%s %s - %s(%s) - %s: %d available\n", (temp + 1),
                   tickets[temp].date,
                   tickets[temp].time,
                   tickets[temp].performing,
                   tickets[temp].opponent,
                   tickets[temp].location,
                   tickets[temp].available);
        }
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
                if(temp >= nr_tickets)
                {
                    temp = temp - 1;
                    printf("There are no other next tickets.\n");
                }
                break;
            case 3:
                temp = temp - 1;
                if(temp < 0)
                {
                    temp = temp + 1;
                    printf("There is no previous ticket.\n");
                }
                break;
            case 4:
                choice = -1;
                break;
            default:
                printf("Wrong input, try again.\n");
                break;
        }
    } while(choice >= 0);
}

void run_purchase_tickets (int choice, profile_struct* user, ticket_struct new_ticket)
{
    int number_of_tickets,  amount_choice,  ticket_type,  ticket_choice,  total,  checkout_choice;

    do{
        if (amount_of_tickets(&number_of_tickets, &amount_choice) == 1)
        {
            if (type_of_ticket( &ticket_type,  &ticket_choice) ==1)
            {
                if(payment(&checkout_choice, ticket_type, number_of_tickets, user, new_ticket)==1)
                {
                    choice = 0;//BACK TO PROFILE OR TO TICKET INFO HERE
                }
            }
        }
        else if (amount_choice != 1)
        {
            choice = 0;
        }
        else if (ticket_choice != 1)
        {
            amount_of_tickets(&number_of_tickets, &amount_choice);
        }
        else if (checkout_choice != 1)
        {
            type_of_ticket(&ticket_type, &ticket_choice);
        }
    } while(choice == 1);
}

int amount_of_tickets(int *number_of_tickets, int *amount_choice)
{
    printf("How many ticket(s) would you like?\n");
    scanf("%d", number_of_tickets);

    printf("You have chosen %d ticket(s).\n[1] Continue\n[2] Back\n",*number_of_tickets);
    scanf("%d", amount_choice);
    return *amount_choice;
}

int type_of_ticket(int *ticket_type, int *ticket_choice)
{
    printf("Choose your type of ticket(s).\n");
    printf("[1] Normal ticket(s)\n[2] VIP ticket(s)\n");
    scanf("%d", ticket_type);

    printf("[1] Continue\n[2] Back\n");
    scanf("%d",ticket_choice);

    return *ticket_choice;
}

int payment(int *checkout_choice, int ticket_type, int number_of_tickets, profile_struct* user, ticket_struct new_ticket)
{
    int total = 0;

    if(ticket_type == 1)
    {
        printf("You have chosen %d normal ticket(s).\n",number_of_tickets);
        total = number_of_tickets * NORMAL_PRICE;
    }
    else if (ticket_type == 2)
    {
        printf("You have chosen %d VIP ticket(s).\n",number_of_tickets);
        total = number_of_tickets * VIP_PRICE;
    }

    printf("Your total is = %d\n",total);
    printf("Your balance is = %d\n", user->balance);
    printf("[1] Purchase\n[2] Back\n");
    scanf("%d", checkout_choice);

    if (*checkout_choice == 1)
    {
        if(user->balance >= total)
        {
            printf("Payment successful\n");
            printf("New balance is = %d\n", (user->balance - total));
            printf("You can now access your ticket(s) in the profile menu, enjoy your event.\n\n");
            // UPDATE NUMBER OF TICKETS HERE
            for(int i=0; i < number_of_tickets; ++i)
            {
                // UPDATE PROFILE WITH TICKETS FUNCTION HERE
                if(ticket_type == 1)
                {
                    strcpy(new_ticket.type, "Normal");
                    strcpy(new_ticket.price, "100");
                    update_profile(new_ticket, user, NORMAL_PRICE);
                }
                else if (ticket_type == 2)
                {
                    strcpy(new_ticket.type, "VIP");
                    strcpy(new_ticket.price, "200");
                    update_profile(new_ticket, user, VIP_PRICE);
                }
            }
        }
        else if(user->balance < total)
        {
            printf("Not enough funds for purchase, refill and try again\n");
        }
    }
    return *checkout_choice;
}
/**
 * Runs all the functions.
 * To be used in final program.
 * @param tickets_in_profile
 */
void run_return_tickets(int *tickets_in_profile,profile_struct* my_profile)
{
    fill_tickets_struct(tickets_in_profile, my_profile);
    return_function(tickets_in_profile, my_profile);
}
/**
 * Function fills struct with information while character in file is not EOF, also opens FILE with tickets in read mode
 * @param tickets_in_profile shows how many tickets are in profile
 * closes tickets FILE
 */
void fill_tickets_struct(int *tickets_in_profile,profile_struct* my_profile)
{
    int character;
    int j=0;
    ticket_return all_tickets[50];
    char txt[] = ".txt";
    char filename[35] = "../Server/";
    strcat(filename, my_profile->username);
    strcat(filename,txt);
    FILE* tickets_temp = fopen(filename,"r");// NAME OF FINAL TICKET TEXT FILE HERE

    if (tickets_temp == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    while((character = getc(tickets_temp))!= EOF)
    {
        ungetc(character,tickets_temp);
        fscanf(tickets_temp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",
                all_tickets[j].category,
                all_tickets[j].genre,
                all_tickets[j].performing,
                all_tickets[j].opponent,
                all_tickets[j].time,
                all_tickets[j].date,
                all_tickets[j].venue,
                all_tickets[j].type,
                all_tickets[j].price);
        ++j;
    }
    *tickets_in_profile = j;
    fclose(tickets_temp);
}
/**
 * Function that returns the tickets(deletes from text FILE), return balance to user and ups the number of available
 * tickets.
 * Function opens tickets FILE in write mode
 * Function shows all tickets with assigned numbers and asks user which are to be returned
 * Function runs through all ticket numbers and DOES NOT print the ticket(struct) which the user wanted returned
 * Function prints the rest of the tickets neatly in text FILE
 * Function returns balance spent on buying to user and ups amount of tickets returned to available tickets
 * @param tickets_in_profile
 */
void return_function(int *tickets_in_profile,profile_struct* my_profile)
{
    int ticket_number;
    ticket_return all_tickets[50];
    char txt[] = ".txt";
    char filename[35] = "../Server/";
    strcat(filename, my_profile->username);
    strcat(filename,txt);
    FILE* tickets_returned = fopen(filename,"w");// NAME OF FINAL TICKET TEXT FILE HERE


    if (tickets_returned == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    printf("Which ticket would you like to return?\n");
    for (int i = 0;  i < *tickets_in_profile; ++i )
    {
        printf("[%d] %s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
               i,
               all_tickets[i].category,
               all_tickets[i].genre,
               all_tickets[i].performing,
               all_tickets[i].opponent,
               all_tickets[i].time,
               all_tickets[i].date,
               all_tickets[i].venue,
               all_tickets[i].type,
               all_tickets[i].price);
        printf("\n");
    }
    scanf("%d",&ticket_number);


    for (int i = 0;  i < *tickets_in_profile; ++i )
    {
        if(i != ticket_number)
        {
            /*CHECKS IF THIS TICKET IS THE LAST, IF IT IS NO NEWLINE CHARACTER IS PRINTED, IF IT ALWAYS PRINTED NEWLINE
            TEXT FILE WOULD HAVE AN EXTRA EMPTY TICKET */

            //THIS IF IS FOR THE USER CHOOSING EVERY TICKET OTHER THAN THE LAST TO BE RETURNED
            if(*tickets_in_profile - ticket_number != 1)
            {
                if(*tickets_in_profile - i != 1)
                {
                    fprintf(tickets_returned,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
                            all_tickets[i].category,
                            all_tickets[i].genre,
                            all_tickets[i].performing,
                            all_tickets[i].opponent,
                            all_tickets[i].time,
                            all_tickets[i].date,
                            all_tickets[i].venue,
                            all_tickets[i].type,
                            all_tickets[i].price);
                }
                else if(*tickets_in_profile - i == 1)
                {
                    fprintf(tickets_returned,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",
                            all_tickets[i].category,
                            all_tickets[i].genre,
                            all_tickets[i].performing,
                            all_tickets[i].opponent,
                            all_tickets[i].time,
                            all_tickets[i].date,
                            all_tickets[i].venue,
                            all_tickets[i].type,
                            all_tickets[i].price);
                }
            }
                /* THIS ELSE IF IS FOR RETURNING THE LAST TICKET. TICKET NUMBER FOR LAST TICKET IS ALWAYS 1 LOWER THAN
                 * TICKETS_IN_PROFILE THEREFORE == 1*/
            else if(*tickets_in_profile - ticket_number == 1)
            {
                if(*tickets_in_profile - i != 2)
                {
                    fprintf(tickets_returned,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
                            all_tickets[i].category,
                            all_tickets[i].genre,
                            all_tickets[i].performing,
                            all_tickets[i].opponent,
                            all_tickets[i].time,
                            all_tickets[i].date,
                            all_tickets[i].venue,
                            all_tickets[i].type,
                            all_tickets[i].price);
                }

                    // IF WE WANT TO RETURN THE LAST TICKET LETS SAY NUMBER 5 OUT OF 5, IT WOULD BE CHOICE 4 BECAUSE
                    // 0 ALSO IS A PART OF THE STRUCT, THE NUMBER 4 WON'T ENTER THIS PART OF THE FUNCTION
                    // BECAUSE OF THE FIRST IF "if(i != ticket_number)", THEREFORE THE TICKET BEFORE 4 WILL BE THE LAST = 3.
                    // 5 (TICKETS) - 3(i, THE LAST 'i' BEFORE FUNCTION END) = 2, THEREFORE NO NEWLINE CHARACTER IN THIS ONE
                else if(*tickets_in_profile - i == 2)
                {
                    fprintf(tickets_returned,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",
                            all_tickets[i].category,
                            all_tickets[i].genre,
                            all_tickets[i].performing,
                            all_tickets[i].opponent,
                            all_tickets[i].time,
                            all_tickets[i].date,
                            all_tickets[i].venue,
                            all_tickets[i].type,
                            all_tickets[i].price);
                }
            }
        }
    }
    printf("The ticket has been returned! Your new balance will be shown below.\n");
    // BALANCE GOES UP, PRICES NEEDED, IDENTIFIER OF TICKET TYPE IN TEXT FILE NEEDED

    my_profile->balance = my_profile->balance + atoi(all_tickets[ticket_number].price);
    printf("YOUR NEW BALANCE IS = %d\n",my_profile->balance);
    // NUMBER OF TICKETS GOES UP HERE

    fclose(tickets_returned);
}
//###########################################################################//
//                               Profile                                     //
//###########################################################################//
void run_profile(profile_struct* user, int* logout, int* nr_users,profile_struct* my_profile)
{
    int choice;
    int tickets_in_profile;
    bool next = false;

    do{
        printf("[1] My Tickets\n"
               "[2] Return Tickets\n"
               "[3] Balance\n"
               "[4] Delete Profile\n"
               "[5] Log Out\n"
               "[6] Back to Main Menu\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                print_tickets(user);
                break;
            case 2:
                run_return_tickets(&tickets_in_profile, my_profile);
            case 3:
                profile_balance(user);
                break;
            case 4:
                delete_profile(user, nr_users);
                *logout = 1;
                next = true;
                break;
            case 5:
                *logout = 1;
                next = true;
                break;
            case 6:
                *logout = 0;
                next = true;
                break;
            default:
                printf("Invalid Input!");
        }
    } while(next == false);
}

void print_tickets(profile_struct* my_profile)
{
    char ch;
    FILE* file;
    char txt[] = ".txt";
    char filename[35] = "../Server/";
    strcat(filename, my_profile->username);
    strcat(filename,txt);

    file = fopen(filename, "r");
    do{
        ch = fgetc(file);
        printf("%c", ch);
    } while (ch != EOF);
    printf("\n");
    fclose(file);
}

void profile_balance(profile_struct* my_profile)
{
    int b_choice;

    printf("Your balance is %d\n", my_profile->balance);
    printf("[1] Deposit balance\n");
    printf("[2] Go back\n");
    scanf("%d", &b_choice);

    if (b_choice == 1)
    {
        int deposit;

        printf("Amount to be deposited:\n");
        scanf("%d", &deposit);

        my_profile->balance = my_profile->balance + deposit;

        printf("New balance is: %d\n", my_profile->balance);
    }
}

void delete_profile( profile_struct* user, int* nr_users)
{
    FILE* file;
    accounts user_list[*nr_users];

    file = fopen("../Server/server_users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
    }
    else
    {
        for(int i = 0; i < *nr_users; i++)
        {
            fscanf(file,"%s %s", user_list[i].username, user_list[i].password);
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
        for(int i = 0; i < *nr_users; i++)
        {
            if(strcmp(user_list[i].username,user->username) == 0)
            {}
            else
            {
                fprintf(file,"%s %s\n", user_list[i].username, user_list[i].password);
            }
        }
    }
    fclose(file);
    *nr_users = *nr_users - 1;
}
/**
 * Adds the new_ticket to the list of tickets under my_profile. Afterwards the Profile along with
 * all its tickets are stored externally in the Profile_Data_Storage.txt file.
 * @param new_ticket = The ticket the user has purchased
 * @param my_profile = The user's profile
 * @param prize = The prize of the ticket
 */
void update_profile(ticket_struct new_ticket, profile_struct* my_profile, int prize)
{
    my_profile->balance = my_profile->balance - prize;

    char txt[] = ".txt";
    char filename[30] = "../Server/";
    strcat(filename, my_profile->username);
    strcat(filename,txt);

    FILE* storage = fopen(filename, "a");
    fprintf(storage,"\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",
            new_ticket.category,
            new_ticket.genre,
            new_ticket.performing,
            new_ticket.opponent,
            new_ticket.time,
            new_ticket.date,
            new_ticket.location,
            new_ticket.type,
            new_ticket.price);
    fclose(storage);
}