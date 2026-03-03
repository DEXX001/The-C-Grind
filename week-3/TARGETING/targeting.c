#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *path;
    
    #ifdef _WIN32
        path = getenv("USERPROFILE");
        printf("[+] Environnement détecté : Windows\n");
    #else
        path = getenv("HOME");
        printf("[+] Environnement détecté : Linux\n");
    #endif

    if (path == NULL)
    {
        printf("[-] Aucun dossier trouvé !");
        return 1;
    }

    printf("[+] Cible identifiée : %s\n", path);

    return 0;

}
