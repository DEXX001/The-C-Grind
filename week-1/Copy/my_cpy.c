#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
    if (ac != 3)
    {
        perror("ERROR FATALE");
        exit(EXIT_FAILURE);
    }

    FILE *src = fopen(av[1], "rb");
    FILE *dest = fopen(av[2], "wb");

    if  (src == NULL || dest == NULL)
    {
        perror("ERROR SUR LES FILES");
        exit(EXIT_FAILURE);
    }

    fseek(src, 0, SEEK_SET);

    unsigned char buffer[4096];
    size_t nb_lus;

    while ((nb_lus = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        fwrite(buffer, 1, nb_lus, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
    
}