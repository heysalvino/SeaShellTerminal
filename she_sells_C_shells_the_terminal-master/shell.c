// Shell
// Jessica Salvino
// Parker Smith

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
        
        char **commands = malloc(INPUT_LEN * sizeof(char*));
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
        
        char *builtin_cmds[3];
        builtin_cmds[0] = "exit";
        builtin_cmds[1] = "pwd";
        builtin_cmds[2] = "cd";
        
        if (strcmp(commands[0], builtin_cmds[0]) == 0) {
            break;
        }
        
        if (strcmp(commands[0], builtin_cmds[1]) == 0) {
            char pwd[INPUT_LEN];
            getcwd(pwd, sizeof(pwd));
        }
        
        if (strcmp(commands[0], builtin_cmds[2]) == 0) {
            chdir(commands[1]);
            continue;
        }
        
        int rc = fork();
        int redirect = -1;
        
        if (rc == 0) {
            
            int i = 0;
            while(commands[i] != NULL) {
                if (strcmp(commands[i], ">") == 0) {
                    redirect = i;
                }
                
                i++;
            }
            
            if (redirect != -1) {
                close(1);
                open(commands[redirect + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
                i = redirect;
                
                while (i < INPUT_LEN) {
                    commands[i] = NULL;
                    i++;
                }
            }
            execvp(commands[0], commands);
            
            perror("execvp");
            return -1;
        } else if (rc > 0) {
            int rc = wait(NULL);
            if (rc < 0) {
                perror("wait");
                return -1;
            }
        } else {
            perror("fork");
        }
        
        free(input);
    }
    return 0;
}
