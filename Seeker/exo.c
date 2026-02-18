#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 2) 
    {
        fprintf(stderr, "Usage: %s <chemin_du_fichier>\n", av[0]);
        return 1;
    }

    FILE *p;

    p = fopen(av[1], "rb");

    if (p == NULL)
    {
        perror("ERREUR FATALE");
        exit(EXIT_FAILURE);
    }

    fseek(p, 0, SEEK_END);

    long position = ftell(p);

    rewind(p);

    printf("Taille du fichier : %ld octets\n", position);

    fclose(p);

    return 0;


}