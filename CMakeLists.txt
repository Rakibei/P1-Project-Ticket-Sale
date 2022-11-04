cmake_minimum_required(VERSION 3.23)
project(p1_project C)

set(CMAKE_C_STANDARD 99)

add_executable(p1_project main.c "Login Code/login_functions.c" "Login Code/login_functions.h" "Menu Code/menu_functions.c" "Menu Code/menu_functions.h")
