#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

extern char** environ;
int child_status;

void output_environment();
char* get_environment(char** environment, char* str);

int main (int argc, char *argv[], char* envp[])
{
    if (argc < 2) {
        printf("No path in command line parametres\n");
        exit(EXIT_FAILURE);
    }
    output_environment();

    char* envp_path = get_environment(envp, "CHILD_PATH");
    char* environ_path = get_environment(environ, "CHILD_PATH");
    for (int index = 0; index <= 99; index++) {
        fprintf(stdout, "Choose one of: '*', '+', '&' (default - exit from program))\n");
        char choice = getchar();
        getchar();
        
        if (choice != '+' && choice != '&' && choice != '*') {
            break;
        }
        
        char number[3];
        //itoa(index, number, 10);
        sprintf(number, "%d", index);
        char* name = (char*)calloc(9, sizeof(char));
        strcpy(name, "CHILD_");
        name = strcat(name, number);
        char* child_args[] = {name, argv[1], (char*)0};
        
        pid_t pid = fork();
        if (pid == -1){
            fprintf(stderr, "Error %d in making new process\n", errno);
            exit(EXIT_FAILURE);
        }
		if (pid == 0) {
            switch (choice){
            case '*':
                fprintf(stdout, "Start process * ...\n");
                execve(envp_path, child_args, envp);
                break;
            case '+':
                fprintf(stdout, "Start process + ...\n");
                execve(getenv("CHILD_PATH"), child_args, envp);
                break;
            case '&':
                fprintf(stdout, "Start process & ...\n");
                execve(environ_path, child_args, envp);
                break;
            }
		}
		wait(&child_status);
        free(name);
        fprintf(stdout, "Child process finished with code %d\n", child_status);
    }
    free(envp_path);
    free(environ_path);
    return (0);
}

void output_environment(){
    int counter = 0;
    for (char** env = environ; *env;env++){
        counter++;
    }

    fprintf(stdout, "Environment:\n");
    for (int i = 0 ; i < counter - 1;i++){
        int min = i;
        for (int j = i + 1;j < counter;j++){
            if (strcoll(environ[j], environ[min]) < 0){
                min = j;
            }
        }

        if (min != i){
            char* temp = environ[i];
            environ[i] = environ[min];
            environ[min] = temp;
        }

        fprintf(stdout, "%s\n", environ[i]);
    }
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
        index++;
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
