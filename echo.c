#include "headers.h"

int echo(char *cmd)
{
    char *token1;
    char *res = cmd;
    strtok_r(NULL, " ", &res);
    while ((token1 = strtok_r(NULL, " ", &res)))
    {
            token1[strcspn(token1, "\n")] = 0;

        printf("%s ",token1);
    }
    printf("\n");
    return 0;
}