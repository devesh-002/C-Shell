#include "headers.h"


int main()
{
    size_t size = 30;
    char *commands = (char *)malloc(sizeof(char) * size);
    bgProcessNum = 0;
    getcwd(mydir, MAX_SIZE);
    getcwd(initialDir, MAX_SIZE);
    getcwd(homeDir, MAX_SIZE);
    processes = (struct backgroundProcess *)malloc(sizeof(struct backgroundProcess) * MAX_SIZE);
    signal(SIGCHLD, checkIfProcessIsOver);

    while (1)
    {
        printDetails();
        int len;
        if ((len = getline(&commands, &size, stdin)) < 0)
        {

            printf("Error hi\n");
            return 0;
        }
        commands[len] = '\0';
        char *token1;
        token1 = strtok_r(commands, ";", &commands);
        while (token1 != NULL)
        {
            token1[strcspn(token1, "\n")] = 0;
            int countTokensOfAnd = 0;
            char token_handle1[200];
            strcpy(token_handle1, token1);

            if (strchr(token_handle1, '&') != NULL)
            {
                countTokensOfAnd++;
                char *token_handle;
                char *token_handle11 = token_handle1;
                int countAndChar = 0;
                for (int i = 0; i < strlen(token_handle1); i++)
                {
                    if (token_handle1[i] == '&')
                    {
                        countAndChar++;
                    }
                }
                token_handle = strtok(token_handle11, "&");
                char prev[200];
                while (token_handle != NULL && countAndChar != 0)
                {
                    // printf("%s\n", token_handle);
                    background(token_handle);

                    countAndChar--;
                    token_handle = strtok(NULL, "&");
                }
                if (token_handle != NULL)
                {
                    // printf("%s\n",token_handle);
                    support(token_handle);
                }
                //                     printf("%s\n",token1);
                // char *token_final;
                //                 for (int i = 0; i < countTokensOfAnd; i++)
                //                 {
                //                     background(token1);
                //                     // printf("%d\n",countTokensOfAnd);
                //                     token1 = strtok(NULL, "&");

                //                 }
            }
            else if (token1 != NULL)
            {
                printf("hii\n");
                support(token1);
            }
            token1 = strtok_r(NULL, ";", &commands);
        }
    }
}