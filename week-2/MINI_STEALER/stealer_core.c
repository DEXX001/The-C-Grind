#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void encrypt_file(char *filepath, unsigned char key)
{   
    unsigned char buffer[4096];
    char dest_path[4096];
    size_t nb_lus;

    snprintf(dest_path, sizeof(dest_path), "%s.enc", filepath);

    FILE *src = fopen(filepath, "rb");
    FILE *dest = fopen(dest_path, "wb");

    if (src == NULL || dest == NULL)
    {
        perror("error open");
        return;
    }

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

    remove(filepath);
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        perror("erreur arguments");
        exit(EXIT_FAILURE);
    }

    DIR *lecture = opendir(av[1]);
    struct dirent *dir; 
    char buffer[4096];

    unsigned char key = (unsigned char)atoi(av[2]);

    if (lecture == NULL)
    {
        perror("ERREUR SUR LE DOSSIER");
        exit(EXIT_FAILURE);
    }

    while ((dir = readdir(lecture)) != NULL)
    {
        if (dir->d_type == DT_REG)
        {
            snprintf(buffer, sizeof(buffer), "%s/%s", av[1], dir->d_name);       
            encrypt_file(buffer, key);
        }
    }

    closedir(lecture);


    return 0;
}