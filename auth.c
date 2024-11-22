#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "auth.h"



char *readData(void)
{
    char *buffer = (char *) malloc(sizeof(char) * 500);

    if (buffer == NULL)
    {
        fprintf(stderr, "Buffer cannot be allocated");
        return NULL;
    }

    FILE* authF = fopen(LOGIN, "r");

    if (authF == NULL)
    {
        perror("File Does not exit creating file");
        authF = fopen(LOGIN, "w");
        if (authF == NULL)
        {
            perror("Error creating file");
            free(buffer);
            return NULL;
        }
    }

    if (fscanf(authF, "%s", buffer) == 1)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("%s", buffer);
    }
    return buffer;
}


int main(void)
{
    char* b = readData();
    free(b);
    return 0;
    
}