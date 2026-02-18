#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 2) 
    {
        fprintf(stderr, "Usage: %s <chemin_du_fichier>\n", av[0]);
        return 1;
    }

    FILE *fp;

    fp = fopen(av[1], "rb");

    if (fp == NULL)
    {
        perror("ERREUR FATALE");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);

    long position = ftell(fp);

    rewind(fp);
    unsigned char buffer[16]; 
    unsigned char header[4];
    fread(header, 1, 4, fp);
    size_t bytes_read;    

    
    printf("\n--- DEBUT DU DUMP ---\n");

    printf("Vérification du type du fichier ...\n\n");

    if (header[0] == 0XFF && header[1] == 0XD8 && header[2] == 0XFF) 
        printf("Fichier = JPEG\n");
    else if (header[0] == 0X89 && header[1] == 0X50 && header[2] == 0X4E && header[3] == 0X47) 
        printf("FIchier = PNG\n");
    else if (header[0] == 0X4D && header[1] == 0X5A )
        printf("Ficher = EXE\n");

    rewind(fp);

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        for (int i = 0; i < bytes_read; i++)
        {
            printf("%02X", buffer[i]);
        }
        
        printf("\n");
    }
    
    printf("--- FIN DU DUMP ---\n\n");

    printf("Taille du fichier : %ld octets\n", position);

    fclose(fp);

    return 0;


}