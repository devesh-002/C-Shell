#include "headers.h"

int support(char *cmd)
{
    char *token;
    char *token1;
    char res[MAX_SIZE];
    char forward[MAX_SIZE];
    strcpy(forward, cmd);
    char *res1 = cmd;
    strcpy(res, cmd);
    // token = strtok_r(res, " ", &res);
    int numOfTokens = 0;
    while ((token1 = strtok_r(res1, " ", &res1)))

    {
        if (numOfTokens == 0)
        {
            token = token1;
        }
        numOfTokens++;
    }
    // printf("%s\n",cmd);
    token[strcspn(token, "\n")] = 0;

    if (strcmp("echo", token) == 0)
    {
        // putInFile("echo\n");
        int x = echo(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("pwd", token) == 0)
    {
        if (numOfTokens > 1)
        {
            printf("Too many arguments\n");
            return 0;
        }
        // putInFile("pwd\n");
        int x = pwd();
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("cd", token) == 0)
    {

        int x = cd(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("pinfo", token) == 0)
    {

        int x = pinfo(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("history", token) == 0)
    {
        extractHistory(res);
    }
    else if (strcmp("ls", token) == 0)
    {
        int x = ls(res);
        if (x == 0)
        {
            putInFile(forward); // error with semicolon, ls -al;
        }
    }
    else if (strcmp("discover", token) == 0)
    {
        int x = discover(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else
    {

        // printf(RED"Invalid Argument %s\n"RESET, token);
        time_t t;
        t = time(NULL);
        int x = foreground(res);
        int time_taken = time(NULL) - t;
        // double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        if (time_taken > 1)
            printf("It took %d seconds to execute \n", time_taken);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
}