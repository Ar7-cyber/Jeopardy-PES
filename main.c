#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeopardy.h"

int main() {
    int playerCount;
    printf("Welcome to Jeopardy - PES Edition!\n");
    printf("Enter number of players: ");
    scanf("%d", &playerCount);
    getchar(); // consume newline

    Player *front = NULL, *rear = NULL;
    for (int i = 0; i < playerCount; i++) {
        char name[MAX_NAME_LEN];
        printf("Enter name for Player %d: ", i + 1);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        rear = enqueuePlayer(rear, name);
        if (!front) front = rear;
    }

    startGame(front, playerCount);
    freePlayers(front);
    return 0;
}