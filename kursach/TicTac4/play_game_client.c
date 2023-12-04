#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "game_logic.h"


//void print_board(char board[3][3]);
void initialize_board(char board[3][3]);
int make_move(char board[3][3], int row, int column, char mark);
//bool check_win(char board[3][3], char mark);


bool check_win(char i);

#define PORT 8080

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

void play_game_client() {
    int client_fd;
    struct sockaddr_in server_address;

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server.\n");

    char board[BOARD_SIZE][BOARD_SIZE];
    char input[10];
    int row, column;

    initialize_board(board);

    while (1) {
        // Read and print the current board state
        read_socket(client_fd, board, sizeof(board));
        print_board(board);

        // Get user input for the move
        printf("Enter your move (row [0-%d] column [0-%d]): ", BOARD_SIZE - 1, BOARD_SIZE - 1);
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d %d", &row, &column);

        // Make the move on the board
        if (make_move(board, row, column, 'X')) {
            // Send the updated board state to the server
            write_socket(client_fd, board, sizeof(board));
        } else {
            printf("Invalid move. Try again.\n");
        }

        //// Check for a win condition
        if(check_win == true) {
            int win = check_win(
            const char[3] *board,
            char mark);
            int win;
            if (win == 1) {
                printf("You win!\n");
                break;
            } else if (win == -1) {
                printf("Server wins!\n");
                break;
            } else if (win == 2) {
                printf("It's a draw!\n");
                break;
            }
        }

        // Make a move for the server
        read_socket(client_fd, board, sizeof(board));
        make_computer_move(board, 'O');

        // Send the updated board state to the server
        write_socket(client_fd, board, sizeof(board));

////         Check for a win condition
        win = check_win(board);
        if (win == 1) {
            printf("You win!\n");
            break;
        } else if (win == -1) {
            printf("Server wins!\n");
            break;
        } else if (win == 2) {
            printf("It's a draw!\n");
            break;
        }
    }

    close(client_fd);
}
