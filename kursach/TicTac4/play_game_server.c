#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "game_logic.h"

#define PORT 8080

//void print_board(char board[3][3]);
void initialize_board(char board[3][3]);
int make_move(char board[3][3], int row, int column, char mark);
//bool check_win(char board[3][3], char mark);


int check_win(char pString[3][3]);

void read_socket(int socket, void *buffer, size_t length) {
    size_t bytesRead = 0;
    while (bytesRead < length) {
        ssize_t result = read(socket, buffer + bytesRead, length - bytesRead);
        if (result < 0) {
            perror("Error reading from socket");
            exit(EXIT_FAILURE);
        } else if (result == 0) {
            fprintf(stderr, "Connection closed\n");
            exit(EXIT_FAILURE);
        }
        bytesRead += result;
    }
}

void write_socket(int socket, const void *buffer, size_t length) {
    size_t bytesWritten = 0;
    while (bytesWritten < length) {
        ssize_t result = write(socket, buffer + bytesWritten, length - bytesWritten);
        if (result < 0) {
            perror("Error writing to socket");
            exit(EXIT_FAILURE);
        }
        bytesWritten += result;
    }
}

void play_game_server() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for client connections
    if (listen(server_fd, 1) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for client connection...\n");

    // Accept the client connection
    if ((client_fd = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    char board[BOARD_SIZE][BOARD_SIZE];
    char input[10];
    int row, column;

    initialize_board(board);

    while (1) {
        // Make a move for the server
        make_computer_move(board, 'X');

        // Send the updated board state to the client
        write_socket(client_fd, board, sizeof(board));

////    Check for a win condition
        int win = check_win(board);
        if (win == 1) {
            printf("Server wins!\n");
            break;
        } else if (win == -1) {
            printf("Client wins!\n");
            break;
        } else if (win == 2) {
            printf("It's a draw!\n");
            break;
        }

        // Read and print the current board state from the client
        read_socket(client_fd, board, sizeof(board));
        print_board(board);

        // Get user input for the move
        printf("Enter your move (row [0-%d] column [0-%d]): ", BOARD_SIZE - 1, BOARD_SIZE - 1);
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d %d", &row, &column);

        // Make the move on the board
        if (make_move(board, row, column, 'O')) {
            // Send the updated board state to the client
            write_socket(client_fd, board, sizeof(board));
        } else {
            printf("Invalid move. Try again.\n");
        }

//// Check for a win condition
        win = check_win(board);
        if (win == 1) {
            printf("Server wins!\n");
            break;
        } else if (win == -1) {
            printf("Client wins!\n");
            break;
        } else if (win == 2) {
            printf("It's a draw!\n");
            break;
        }
    }

    close(client_fd);
    close(server_fd);
}

int check_win(char pString[3][3]) {
    return 0;
}
