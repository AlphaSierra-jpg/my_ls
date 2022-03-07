#include "includes.h"

int ls_ls_dir_diff(char *tab, int isOpt[]);

int my_ls_diffl(char *tab, int isOpt[], int numArg) {

    struct stat stats;

    if (stat(tab, &stats) == 0) { 
        if ((stats.st_mode & S_IFMT) == S_IFDIR && isOpt[7] == 0) {
            ls_ls_dir_diff(tab, isOpt);
        } else {
            my_putstr(tab);
            my_putstr("\n");
        }
    } else {
        my_putstr("error when get Stas");
        return 0;
    }
 
    if (numArg){  
    }
    return 1;
}

int ls_ls_dir_diff(char *tab, int isOpt[]){

    int nbrDir = 0;
    int i = 0;

    char **rDirectory;
    rDirectory = NULL;

    struct stat stats;

    struct dirent *pDirent;
    DIR *pDir;
    pDir = opendir(tab);
    
    if (!pDir){
        if (errno == ENOENT){
            my_putstr("ls: ");
            my_putstr(tab);
            perror(": This directory doesn't exist");
        }
        else{    
            perror("Unable to read directory");
        }
        return 0;
    }
    
    while ((pDirent = readdir(pDir)) != NULL) {
        if ((pDirent->d_name[1] && pDirent->d_name[1] != '.' && isOpt[5] == 1) || (pDirent->d_name[0] != '.' || isOpt[4] == 1)){
            if ((isOpt[1] == 1 ? stat(link_normalizer(tab, pDirent->d_name), &stats) : lstat(link_normalizer(tab, pDirent->d_name), &stats)) == 0 ) { 
                
                if (isOpt[3] == 1 && (stats.st_mode & S_IFMT) == S_IFDIR && pDirent->d_name[0] != '.' ){
                    nbrDir++;
                }
                
            }
        }
    }
    closedir (pDir);
    
    if (isOpt[3] == 1)
    {
        rDirectory = malloc(sizeof(char *) * nbrDir);
    }
    
    pDir = opendir(tab);

    while ((pDirent = readdir(pDir)) != NULL) {

        if ((pDirent->d_name[1] && pDirent->d_name[1] != '.' && isOpt[5] == 1) || (pDirent->d_name[0] != '.' || isOpt[4] == 1)) {

            if ((isOpt[1] == 1 ? stat(link_normalizer(tab, pDirent->d_name), &stats) : lstat(link_normalizer(tab, pDirent->d_name), &stats)) == 0 ) { 

                if ((stats.st_mode & S_IFMT) == S_IFDIR && isOpt[3] == 1 && pDirent->d_name[0] != '.') {
                    rDirectory[i] = my_strdup(pDirent->d_name);
                    i++;
                }

                my_putstr(pDirent->d_name);
                my_putstr("\n");

                } else {
                    my_putstr("Something is wrong with the colect of the stats\n");
                return 0;
            }
        }
    }
    my_putstr("\n");
    closedir (pDir);

    if (isOpt[3] == 1)
    {
        i = 0;
        while (i < nbrDir) {
            my_putstr(link_normalizer(tab, rDirectory[i]));
            my_putstr(":\n");
            my_ls_diffl(link_normalizer(tab, rDirectory[i]) , isOpt, 1);
            i++;
        }
    free(rDirectory);  
    }
    return 1;
}
