#include <stdio.h>
#include <string.h>

int main(void)
{
    char name[20];
    printf("Hello. What's your name?\n");

    fgets(name, 20, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Hi there, %s, you are playing an advendure game!", name);

    return 0;
}