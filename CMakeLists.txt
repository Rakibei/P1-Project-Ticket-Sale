cmake_minimum_required(VERSION 3.23)
project(p1_project C)

set(CMAKE_C_STANDARD 99)

add_executable(p1_project main.c "Menu Code/menu_functions.c" "Menu Code/menu_functions.h" "Purchasing of tickets/Purchase_tickets_functions.c" "Purchasing of tickets/Purchase_tickets_functions.h" "Storage Code/data_storage.c" "Storage Code/data_storage.h" "Profile Menu/Profile_Menu_Code.c" "Profile Menu/Profile_Menu_Code.h")
