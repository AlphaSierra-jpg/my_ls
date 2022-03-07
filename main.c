#include "includes.h"

void opth();

int main(int argc, char *argv[])
{   
    int isOpt[8] = {0,0,0,0,0,0,0,0};

    int optind;
    int numArg = 0;
    int idArg = 0;

    char **tab;
    tab = NULL;

    for (optind = 1; optind < argc && argv[optind][0] == '-'; optind++) {
        switch (argv[optind][1]) {
            case 'l': isOpt[0] = 1; break;
            case 'L': isOpt[1] = 1; break;
            case 'r': isOpt[2] = 1; break;
            case 'R': isOpt[3] = 1; break;
            case 'a': isOpt[4] = 1; break;
            case 'A': isOpt[5] = 1; break;
            case 't': isOpt[6] = 1; break;
            case 'd': isOpt[7] = 1; break;
            case 'h': opth(); break;
            default:
                my_putstr("Something is wrong with the arguments. Using ./my_ls -h for help\n");
                exit(EXIT_FAILURE);
        }   
    }
    for (int i = optind; i < argc; i++){
        numArg++;
    }
    
    if (argv[optind] == NULL) {
        tab = malloc(sizeof(char *));
        tab[0] = ".";      
    } else {
        tab = malloc(sizeof(char *) * numArg);

        for (int i = optind; i < argc; i++){   
            
            tab[idArg]= my_strdup(argv[i]);
            idArg++;
        }
    }
    my_ls(tab,isOpt,numArg);
}

void opth(){
    my_putstr("./my_ls -A -l ... [path...]\n");
    my_putstr("\n");
    my_putstr("-l : List information about the files\n");
    my_putstr("-L : Using with -l for display information of the file target by the symbolique link\n");
    my_putstr("-r : Reverse the selection. When using with -t reverse the time\n");
    my_putstr("-R : When reading the folder -R reads the contents of the lister folders and displays them with recursivity\n");
    my_putstr("-a : Display hidden files\n");
    my_putstr("-A : Same as -a but hide \".\" and \"..\"\n");
    my_putstr("-t : Sort by time\n");
    my_putstr("-d : Directories are listed as plain files (not searched recursively)\n");
    exit(EXIT_FAILURE);
}


