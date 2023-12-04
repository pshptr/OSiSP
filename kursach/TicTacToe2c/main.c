#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "server.h"
#include "client.h"

#define PORT 8080

int main() {
    int choice;

    printf("Choose an option:\n");
    printf("1. Play as server\n");
    printf("2. Play as client\n");
    scanf("%d", &choice);

    if (choice == 1) {
        play_game_server(PORT);
    } else if (choice == 2) {
        play_game_client(PORT);
    } else {
        printf("Invalid choice.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
