#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void scan_folder(char *path)
{
    DIR *doss = opendir(path);
    struct dirent *dir;
    char buffer[4096];

    if (doss == NULL)
    {
        perror("erreur dossier");
        return;
    }
    
    while ((dir = readdir(doss)) != NULL)
    {
        if (dir->d_type == DT_REG)
        {
            snprintf(buffer, sizeof(buffer), "%s/%s", path, dir->d_name);
            printf("%s\n", buffer);
        }
        else if (dir->d_type == DT_DIR)
        {
            if (strcmp(dir->d_name, ".")== 0 
            ||  strcmp(dir->d_name, "..")== 0)
                continue;
            char new_path[4096];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, dir->d_name);
            printf("%s\n", new_path);
            scan_folder(new_path);
        }
    }

    closedir(doss);
    
}

int main(int ac, char **av) {
    if (ac < 2) return 1;
    scan_folder(av[1]);
    return 0;
}
