#include <stdio.h>

int main() {
    char test = 'a';

    printf("Hello, World!\n");
    scanf(" %c", test);
    if (test == 'a') {
        printf("Test is 1");
    } else {
        printf("Test is %d", test);
    }
    return 0;
}
