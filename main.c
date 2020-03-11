#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 10
#define FILE_NAME "map.txt"
#define MAX_X 5
#define MAX_Y 5
#define START "S"
#define END "E"

struct game
{
    char coord[MAX_Y][MAX_X];
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int position_x;
    int position_y;
    bool play;
};

struct game loadMap()
{
    char line[SIZE][SIZE];
    struct game game;
    FILE *fptr = NULL;

    int i = 0;
    fptr = fopen(FILE_NAME, "r");
    while (fgets(line[i], SIZE, fptr))
    {
        char *p;
        p = line[i];

        for (int j = 0; p[j]; j++)
        {
            game.coord[i][j] = p[j];

            if (p[j] == *START)
            {
                game.start_x = game.position_x = j;
                game.start_y = game.position_y = i;
            }
            if (p[j] == *END)
            {
                game.end_x = j;
                game.end_y = i;
            }
        }
        i++;
    }
    return game;
}

struct game doAction(char action[1], struct game game)
{
    if (*action == 'l')
    {
        if (game.position_x == game.start_x && game.position_y == game.start_y)
        {
            printf("You are in a starting position.\n");
        }
    }
    if (*action == 'n')
    {
        game.position_y--;
    }
    if (*action == 's')
    {
        game.position_y++;
    }
    if (*action == 'w')
    {
        game.position_x++;
    }
    if (*action == 'e')
    {
        game.position_x--;
    }
    if (*action == 'i')
    {
        // TODO inventory functionality
        printf("Your inventory is empty\n");
    }

    // check if nswe position is allowed and change it, also check if E is reached
    if (0 > game.position_y || game.position_y >= MAX_Y)
    {
        printf("You cannot go here\n");
        if (*action == 'n')
        {
            game.position_y++;
        }
        else
        {
            game.position_y--;
        }
    }
    if (0 > game.position_x || game.position_x >= MAX_X)
    {
        printf("You cannot go here\n");
        if (*action == 'e')
        {
            game.position_x++;
        }
        else
        {
            game.position_x--;
        }
    }
    if (game.coord[game.position_y][game.position_x] == 'E')
    {
        printf("You reached the END!");
        game.play = false;
    }

    return game;
}

int main(void)
{
    char name[20];
    printf("Hello. What's your name?\n");

    fgets(name, 20, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Hi there, %s, you are playing an adventure game!\n", name);

    struct game game = loadMap();
    game.play = true;

    while (game.play)
    {
        printf("You are in a position: %d:%d\n", game.position_x, game.position_y);

        printf("Which action you want to do [l,n,s,w,e,i]?\n");

        char action[1];

        fgets(action, 20, stdin);
        action[strcspn(action, "\n")] = 0;

        game = doAction(action, game);
    }

    return 0;
}