#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char* get_environment(char** environment, char* str);

int main(int argc, char* argv[], char* envp[]){
    if (argc < 2) {
        printf("No path in command line parametres\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Process %s start\n", argv[0]);
    fprintf(stdout, "pid = %d \nppid  = %d\n", (int)getpid(), (int)getppid());
    fprintf(stdout, "File path = '%s'\n", argv[1]);
    FILE* file = fopen(argv[1], "r");
    if (file) {
        char file_buffer[255];
        while (fgets(file_buffer, 255, file) != NULL){
            int buffer_length = strlen(file_buffer);
            file_buffer[buffer_length - 1] = 0;
            char* name = get_environment(envp, file_buffer);
            if (strlen(name))fprintf(stdout, "%s%s\n", file_buffer, name);
            free(name);
        }
        fclose(file);
    } else {
        fprintf(stdout, "Can't open file '%s'", argv[1]);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

char* get_environment(char** environment, char* str){
    char* result = (char*)calloc(255, sizeof(char));
    for (;*environment; environment++){
        int flag = 1;
        int index = 0;
        for (;index < (int)strlen(str);index++){
            if (str[index] != (*environment)[index]) {
                flag = 0;
                break;
            }
        }
        int res_index = 0;
        if (flag == 1){
            while (index < (int)strlen(*environment)){
                result[res_index++] = (*environment)[index++];
            }
            break;
        }
    }
    return result;
}
