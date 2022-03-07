#include "includes.h"

int ls_ls_dir(char *tab, int isOpt[]);

int ls_ls_file(char *tab, int isOpt[]);

char    *link_normalizer(char *tab, char *fileName);

int my_ls_l(char *tab, int isOpt[], int numArg) {

    struct stat stats;

    if (stat(tab, &stats) == 0) { 
        if ((stats.st_mode & S_IFMT) == S_IFDIR && isOpt[7] == 0) {
            ls_ls_dir(tab, isOpt);
        } else {
            ls_ls_file(tab, isOpt);
        }
    } else {
        my_putstr("error when get Stas");
        return 0;
    }
 
    if (numArg){  
    }
    return 1;
}

int ls_ls_dir(char *tab, int isOpt[]){

    int nbrDir = 0;
    int ttblocks = 0;
    int i = 0;

    char **rDirectory;
    rDirectory = NULL;
    char *linkname;

    ssize_t r;
    struct stat stats;
    struct passwd *p;
    struct group *grp;
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
                ttblocks = ttblocks + stats.st_blocks;
                if (isOpt[3] == 1 && (stats.st_mode & S_IFMT) == S_IFDIR && pDirent->d_name[0] != '.' ){
                    nbrDir++;
                }
                
            }
        }
    }
    closedir (pDir);

    my_putstr("total ");
    my_putnbr(ttblocks);
    my_putstr("\n");
    
    if (isOpt[3] == 1)
    {
        rDirectory = malloc(sizeof(char *) * nbrDir);
    }
    

    pDir = opendir(tab);

    while ((pDirent = readdir(pDir)) != NULL) {

        if ((pDirent->d_name[1] && pDirent->d_name[1] != '.' && isOpt[5] == 1) || (pDirent->d_name[0] != '.' || isOpt[4] == 1)) {

            if ((isOpt[1] == 1 ? stat(link_normalizer(tab, pDirent->d_name), &stats) : lstat(link_normalizer(tab, pDirent->d_name), &stats)) == 0 ) { 
                switch (stats.st_mode & S_IFMT) {
                    case S_IFBLK:  my_putstr("b"); break;
                    case S_IFCHR:  my_putstr("c"); break;
                    case S_IFDIR:  my_putstr("d"); break;
                    case S_IFIFO:  my_putstr("p"); break;
                    case S_IFLNK:  my_putstr("l"); break;
                    case S_IFREG:  my_putstr("-"); break;
                    case S_IFSOCK: my_putstr("s"); break;
                    default:       my_putstr("?"); break;
                }

                if ((stats.st_mode & S_IFMT) == S_IFDIR && isOpt[3] == 1 && pDirent->d_name[0] != '.') {
                    rDirectory[i] = my_strdup(pDirent->d_name);
                    i++;
                }
            
                my_putstr(stats.st_mode & S_IRUSR ? "r" : "-");
                my_putstr(stats.st_mode & S_IWUSR ? "w" : "-");
                my_putstr(stats.st_mode & S_IXUSR ? "x" : "-");
                my_putstr(stats.st_mode & S_IRGRP ? "r" : "-");
                my_putstr(stats.st_mode & S_IWGRP ? "w" : "-");
                my_putstr(stats.st_mode & S_IXGRP ? "x" : "-");
                my_putstr(stats.st_mode & S_IROTH ? "r" : "-");
                my_putstr(stats.st_mode & S_IWOTH ? "w" : "-");
                my_putstr((stats.st_mode & S_IXOTH) ? ("x  ") : ("-  "));
                my_putnbr(stats.st_nlink);
                my_putstr(" ");
                uid_t  uid=stats.st_uid;
                if ((p = getpwuid(uid)) == NULL){
                    perror("error with the function getpwuid()");
                } else {
                    my_putstr(p->pw_name);
                }
                my_putstr("  ");
                if ((grp = getgrgid(stats.st_gid)) == NULL){
                    perror("getgrgid() error");
                } else {
                    my_putstr(grp->gr_name);
                }
                my_putstr("  ");
                my_putnbr(stats.st_size);
                my_putstr(" ");
                write(1, (ctime(&stats.st_mtime) + 4), (my_strlen(ctime(&stats.st_mtime)) -13));
                my_putstr(" ");
                my_putstr(pDirent->d_name);
                
                if ((stats.st_mode & S_IFMT) == S_IFLNK)
                {
                    my_putstr(" -> ");
                    linkname = malloc(stats.st_size + 1);
                    if (linkname == NULL) {
                        my_putstr("");
                        return 0;
                    }

                    r = readlink(link_normalizer(tab, pDirent->d_name), linkname, stats.st_size + 1);

                    linkname[stats.st_size] = '\0';

                    my_putstr(linkname);
                }
                
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
            my_ls_l(link_normalizer(tab, rDirectory[i]) , isOpt, 1);
            i++;
        }
    free(rDirectory);  
    }
    return 1;
}

int ls_ls_file(char *tab, int isOpt[]){
    
    
    struct stat stats;
    struct passwd *p;
    struct group *grp;
     
    if ( (isOpt[1] == 1 ? stat(tab, &stats) : lstat(tab, &stats)) == 0 ) {
        switch (stats.st_mode & S_IFMT) {
            case S_IFBLK:  my_putstr("b"); break;
            case S_IFCHR:  my_putstr("c"); break;
            case S_IFDIR:  my_putstr("d"); break;
            case S_IFIFO:  my_putstr("p"); break;
            case S_IFLNK:  my_putstr("l"); break;
            case S_IFREG:  my_putstr("-"); break;
            case S_IFSOCK: my_putstr("s"); break;
            default:       my_putstr("?"); break;
        }

    my_putstr(stats.st_mode & S_IRUSR ? "r" : "-");
    my_putstr(stats.st_mode & S_IWUSR ? "w" : "-");
    my_putstr(stats.st_mode & S_IXUSR ? "x" : "-");
    my_putstr(stats.st_mode & S_IRGRP ? "r" : "-");
    my_putstr(stats.st_mode & S_IWGRP ? "w" : "-");
    my_putstr(stats.st_mode & S_IXGRP ? "x" : "-");
    my_putstr(stats.st_mode & S_IROTH ? "r" : "-");
    my_putstr(stats.st_mode & S_IWOTH ? "w" : "-");
    my_putstr((stats.st_mode & S_IXOTH) ? ("x  ") : ("-  "));
    my_putnbr(stats.st_nlink);
    my_putstr(" ");

    uid_t  uid=stats.st_uid;

    if ((p = getpwuid(uid)) == NULL){
        perror("error with the function getpwuid()");
    } else {
        my_putstr(p->pw_name);
    }
    my_putstr("  ");
    if ((grp = getgrgid(stats.st_gid)) == NULL){
        perror("getgrgid() error");
    } else {
        my_putstr(grp->gr_name);
    }
    my_putstr("  ");
    my_putnbr(stats.st_size);
    my_putstr(" ");
    write(1, (ctime(&stats.st_mtime) + 4), (my_strlen(ctime(&stats.st_mtime)) -13));
    my_putstr(" ");
    my_putstr(tab);
    my_putstr("\n");

    } else {
        my_putstr("Something is wrong with the colect of the stats\n");
        return 0;
    }

    return 1;
}

char    *link_normalizer(char *tab, char *fileName){
    char *link;

    if (tab[my_strlen(tab)-1] == '/' ){
        link = my_strcat(tab , fileName);
    } else {
        link = my_strcat(tab , my_strcat("/", fileName));
    }
    
    return(link);
}