#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  // For system calls
#include <unistd.h>     // For system calls
#include <sys/wait.h>   // For wait()
#include <colors.h>     //Personal header for text color

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int main()
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    char *token;
    pid_t pid;
    int status;

    while (1)
    {
        // Just like printf() but colorful, A red colored $ will appear - NULL value is for background argument
        colprint("$ ","red",NULL);  //printf("$ "); Can be replaced(comment the color.h header)
        fflush(stdout);

        if(fgets(input , sizeof(input) , stdin) == NULL)
        {
            break; // Breaks when input is null
        }

        // Remove newline character
        input[strcspn(input, "\n")] = '\0';

        // Tokenize the entire input
        int i = 0;
        token = strtok(input, " ");
        while( token != NULL && i < MAX_ARGS-1 )
        {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL; // execvp() Requires a NULL-terminated array

        // From this point, The actual shell implementation will begin
        // Befor running existing scripts for shell, built-in commands must be build
        // For this program only two built in commands(cd and exit) is considered

        // exit , EXIT
        if(strcmp(args[0],"exit") == 0 || strcmp(args[0],"EXIT") == 0 )
        {
            exit(0);
        }

        //cd (change directory)
        if(strcmp(args[0],"cd") == 0)
        {
            if(args[1] == NULL)
                fprintf(stderr, "cd: missing argument\n");
            else
            {
                //The chdir() function is a system call used to change the current working directory of the calling process.
                if (chdir(args[1]) != 0)

                {
                    perror("cd");
                }
            }
            continue;
        }

        // Making a child process
        else
        {
            pid = fork();
            // Error handling if fork failed
            if(pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            else if(pid == 0)   // Which means child process was succeed
            {
                // This will read args and pass them to the invoked program, args[0] is likely the program and the rest are arguments of
                // That program. execv itself, Pass the arguments to program.
                execvp(args[0] , args);
                // This part will execute only when execv fails
                perror("execv");
                exit(EXIT_FAILURE);
            }
            else    // pid > 0 means in parallel runing the parent process
            {
                wait(&status);  // wait() is neccessary for preventing zombie leak

                // To be aware of status, Uncomment following instructions
                //if (WIFEXITED(status)) Did the child exit normally (not by a signal)?
                //{
                //  printf("Child exited with status: %d\n", WEXITSTATUS(status));
                //}
            }
        }

    }

    return 0;
}
