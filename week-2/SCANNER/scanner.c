#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int ac, char *av[])
{
    if (ac != 2)
    {
        perror("ERREUR SUR LES ARGUMENTS");
        exit(EXIT_FAILURE);
    }

    DIR *lecture = opendir(av[1]);
    struct dirent *dir; 
    char buffer[4096];

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
            printf("%s\n", buffer);
        }
    }

    closedir(lecture);

    return 0;
    
}