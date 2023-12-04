#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "game_logic.h"

void play_game_server();
void play_game_client();

int main() {
    int mode;

    printf("Tic-Tac-Toe Game\n");
    printf("1. Play as server\n");
    printf("2. Play as client\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &mode);

    if (mode == 1) {
        play_game_server();
    } else if (mode == 2) {
        play_game_client();
    } else {
        printf("Invalid choice. Exiting.\n");
    }

    return 0;
}
