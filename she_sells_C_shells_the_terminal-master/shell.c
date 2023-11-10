#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#define INPUT_LEN 1024

// Function to parse the input command
void parseInput(char *input, char **commands) {
    char *space = " ";
    char *token;
    int index = 0;

    token = strtok(input, space);
    while (token != NULL) {
        commands[index] = token;
        index++;
        token = strtok(NULL, space);
    }
    commands[index] = NULL;
}

// Function to execute built-in commands
int executeBuiltInCommands(char **commands) {
    if (strcmp(commands[0], "exit") == 0) {
        return 1; // Terminate the shell
    } else if (strcmp(commands[0], "pwd") == 0) {
        char pwd[INPUT_LEN];
        getcwd(pwd, sizeof(pwd));
        printf("%s\n", pwd);
        return 0;
    } else if (strcmp(commands[0], "cd") == 0) {
        if (commands[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(commands[1]) != 0) {
                perror("cd");
            }
        }
        return 0;
    }
    return -1; // Not a built-in command
}

// Function to execute external commands
void executeExternalCommand(char **commands) {
    int rc = fork();
    if (rc == 0) {
        execvp(commands[0], commands);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (rc > 0) {
        int status;
        waitpid(rc, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Command '%s' failed with exit status %d\n", commands[0], WEXITSTATUS(status));
        }
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

int main() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~__________~~~~~~~~~\n");
    printf("~~~~~~~~( || || || )~~~~~~~~\n");
    printf("~~~~~( ||WELCOME TO|| )~~~~~\n");
    printf("~~~~(SHE SELLS C SHELLS)~~~~\n");
    printf("~~~~~( |THE TERMINAL| )~~~~~\n");
    printf("~~~~~~(|| || || || ||)~~~~~~\n");
    printf("~~~~~~~~( || || || )~~~~~~~~\n");
    printf("~~~~~~~~~~~|_||_|~~~~~~~~~~~\n");
    printf("~~~~~~~~~(_(____)_)~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~ type 'exit' to terminate ~\n");

    char *input;

    while (1) {
        input = readline("shell$ ");

        char **commands = malloc(INPUT_LEN * sizeof(char *));
        parseInput(input, commands);

        int result = executeBuiltInCommands(commands);
        if (result == 1) {
            free(input);
            free(commands);
            break;
        } else if (result == 0) {
            // Continue the loop for built-in commands
        } else {
            executeExternalCommand(commands);
        }

        free(input);
        free(commands);
    }

    return 0;
}
