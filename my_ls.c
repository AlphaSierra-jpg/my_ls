#include "includes.h"

int my_ls(char **tab,int isOpt[], int numArg) {
    int i = 0;
    if (isOpt[0]==1){
        if (numArg==0) {
            my_ls_l(tab[0], isOpt, numArg);
        } else {

            while (i < numArg) {
                if (numArg > 1){
                    my_putstr(tab[i]);
                    my_putstr(":\n");
                }

                my_ls_l(tab[i], isOpt, numArg);
                
                if (numArg > 1){
                    my_putstr("\n");
                }
                i++;
            } 
        }
    } else {
        if (numArg==0) {
            my_ls_diffl(tab[0], isOpt, numArg);
        } else {

            while (i < numArg) {
                if (numArg > 1){
                    my_putstr(tab[i]);
                    my_putstr(":\n");
                }

                my_ls_diffl(tab[i], isOpt, numArg);
                
                i++;
            } 
        }
    }
    return 1;
}

