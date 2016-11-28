#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

char str[512];
char *cmd1[32];
char *cmd2[32];
char *cmd3[32];
int i = 0;
int j = 0;
char *p;
int fd1[2], fd2[2];
int pid1, pid2;


int main()
{
    printf("[myshell]$ ");
    fgets(str, 512, stdin);
    str[strlen(str)-1] = '\0';
    p = strtok (str," ");
    while (p != NULL)
    {
        if (i == 0) {
            if(p[0] == '|') {
                cmd1[j] = NULL;
                i = i + 1;
                j = 0;
            } else {
                cmd1[j] = p;
                j = j + 1;
            }
        } else if (i == 1) {
            if(p[0] == '|') {
                cmd2[j] = NULL;
                i = i + 1;
                j = 0;
            } else {
                cmd2[j] = p;
                j = j + 1;
            }
        } else {
            if(p[0] == '|') {
                cmd3[j] = NULL;
                i = i + 1;
                j = 0;
            } else {
                cmd3[j] = p;
                j = j + 1;
            }
        }
        p = strtok (NULL, " ");
    }
    if (i == 0) {
        cmd1[j] = NULL;
    } else if (i == 1) {
        cmd2[j] = NULL;
    } else {
        cmd3[j] = NULL;
    }
    
    
    if (pipe(fd1) == -1) {
        printf("Error: Pipe failed.\n");
        return 1;
    }
    if (pipe(fd2) == -1) {
        printf("Error: Pipe failed.\n");
        return 1;
    }
    
    
    if (i > 0) {
        pid1 = fork();
        if (pid1 == 0) {
            if (i == 2) {
                pid2 = fork();
                if (pid2 == 0) {
                    close (fd1[1]);
                    close (fd1[0]);
                    dup2(fd2[0], 0);
                    close(fd2[1]);
                    execvp(cmd3[0], cmd3);
                    perror(cmd3[0]);
                } else if (pid2 > 0) {
                    dup2(fd1[0], 0);
                    dup2(fd2[1], 1);
                    close(fd1[1]);
                    close(fd2[0]);
                    execvp(cmd2[0], cmd2);
                    perror(cmd2[0]);
                } else {
                    perror("fork");
                    exit(1);
                }
            } else {
                dup2(fd1[0], 0);
                close(fd1[1]);
                execvp(cmd2[0], cmd2);
                perror(cmd2[0]);
            }
        } else if (pid1 > 0) {
            dup2(fd1[1], 1);
            close(fd1[0]);
            execvp(cmd1[0], cmd1);
            perror(cmd1[0]);
        } else {
            perror("fork");
            exit(1);
        }
    } else {
        execvp(cmd1[0], cmd1);
    }
    
}
