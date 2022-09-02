#include "headers.h"
void delProcess(int id)
{
    int check = 0;
    for (int i = 0; i < bgProcessNum; i++)
    {
        if (processes[i].pid == id)
        {
            check = 1;
            for (int j = i + 1; j < bgProcessNum; j++)
            {
                processes[j - 1] = processes[j];
            }
            bgProcessNum--;
            break;
        }
    }
}
void checkIfProcessIsOver()
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    // printf("%d",pid);
    for (int x = 0; x < bgProcessNum; x++)
    {
        if (pid < 0)
        {
            perror(RED "Error in process over" RESET);
        }
        int exit = WEXITSTATUS(status);
        if ((WIFEXITED(status) && pid == processes[x].pid))
        {
            if (exit == 0)
            {
                printf("Exited normally with status 0\n");
                printDetails();
            }
            else
            {
                printf("Some error in exiting, status:%d\n", exit);
            }
            fflush(stdout);
            delProcess(pid);
        }
    }
}
int background(char *cmd)
{
    char buf1[200];
    char *arr[MAX_SIZE];
    char *token;
    strcpy(buf1, cmd);
    char *buf = buf1;
    token = strtok_r(buf, " ", &buf);
    int i;
    // strcpy(arr[0],token);
    for (i = 0; token != NULL; i++)
    {

        arr[i] = token;
        token = strtok_r(NULL, " ", &buf);
    }
    arr[i] = NULL;
    pid_t pid = fork();
        setpgid(0, 0);
    if (pid < 0)
    {
        perror(RED "fork not working" RESET);
    }
    else if(!pid)
    {
        pid_t check=getpid();
        if(!(execvp(arr[0],arr)));
        {
            perror(RED"Error in execvp\n"RESET);
        }
        return 0;
    }
    else
    {
        processes[bgProcessNum].pid = pid;
        strcpy(processes[bgProcessNum].jobname, arr[0]);
        bgProcessNum += 1;
        // printf("%s\n",processes[0].jobname);
    }
}
int foreground(char *cmd)
{
    char buf1[200];
    char *arr[MAX_SIZE];
    char *token;
    strcpy(buf1, cmd);
    char *buf = buf1;

    token = strtok_r(buf, " ", &buf);
    int i;
    // strcpy(arr[0],token);
    for (i = 0; token != NULL; i++)
    {

        arr[i] = token;
        token = strtok_r(NULL, " ", &buf);
    }
    arr[i] = NULL;
    pid_t pid = fork();
    if (pid < 0)
    {
        perror(RED "fork not working" RESET);
    }

    else
    {
        forepid = pid;
        strcpy(forepname, arr[0]);

        if (!pid)
        {
            if (execvp(arr[0], arr) == -1)
            {
                perror(RED "error in execvp, command not found" RESET);
            }
        }
        else
        {
            int lmao;
            waitpid(pid, &lmao, WUNTRACED);
        }
    }
}