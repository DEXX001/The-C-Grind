#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 4)
    {
        perror("ERROR - Argument");
        exit(EXIT_FAILURE);
    }

    FILE *src = fopen(av[1], "rb");
    FILE *dest = fopen(av[2], "wb");

    if (src == NULL || dest == NULL)
    {
        perror("ERROR SUR LES FILES");
        exit(EXIT_FAILURE);
    }

    unsigned char key = (unsigned char)atoi(av[3]);

    unsigned char buffer[4096];
    size_t nb_lus;

    while ((nb_lus = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        for (int i = 0; i < nb_lus; i++)
        {
            buffer[i] = buffer[i] ^ key;
        }

        fwrite(buffer, 1, nb_lus, dest);
        
    }

    fclose(src);
    fclose(dest);

    return 0;
    
}