#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../my_assets.h"

void my_putchar(char c);
int my_strlen(const char *str);
void my_putstr(const char *str);
void nbr(long int nbr);
int my_putnbr(long int a);

void my_putchar(char c)
{
	write(1, &c, 1);
}

int my_strlen(const char *str)
{

	int lng = 0;

	while (*str != 0)
	{
		str++,
			lng++;
	}
	return (lng);
}

void my_putstr(const char *str)
{
	int i = 0;	 //là i vaut 0 et c est un entier
	int lng = 0; //pareil pour la longueur de la chaine de caractere
	const char *pt;
	pt = str; //passage par adresse
	while (*pt != 0)
	{
		pt++;
		lng++; //longueur de la chaine de caractere
	}

	while (i <= lng - 1)
	{
		my_putchar(str[i]); // on parse la chaine element par element
		i++;
	}
}

void nbr( long int nbr)
{
    long int lng;
    long int value;
    long int temp = nbr;
    value = 1;
    
    while (temp / 10 != 0)
        {
            
            temp = temp / 10;
            
            value = value * 10;
        }
    
    
    lng = value;

    while (lng != 0)
        {
            my_putchar(nbr / lng + '0');
            nbr = nbr % lng;
            lng = lng / 10;
        }
    
}

int my_putnbr(long int a)
{
    if (a >= 0)
    {
        nbr(a);
    }else{
        my_putchar('-');
        a=-a;
        nbr(a);
    }
    return(0);
    
}
//                      chat               poisson
  char	*my_strcat(char *dest, char const *src){
	int     i = 0;
	int     count = 0;
	char    *res;
//								|				12
	res = malloc(sizeof(*res) * (my_strlen(dest) + my_strlen(src) + 1) );
	//res[] = { , , , , , , , , , , , }
	//src[] = {p,o,i,s,s,o,n,\0}
	// dest[] = {c,h,a,t,\0}
	while (dest[i]) {
	// Pour i = 0
	//	Rentrer dans la case 0 de res[0] <- case dest[0] "c"
		res[i] = dest[i];
		i++;
	}
	// res[] = {c,h,a,t, , , , , , , , }
	//src[] = {p,o,i,s,s,o,n,\0}
	
	while (src[count]) {
		res[i + count] = src[count];
		count++;
	}
	// res[] = {c,h,a,t,p,o,i,s,s,o,n, }
	res[i + count] = '\0';
	// res[] = {c,h,a,t,p,o,i,s,s,o,n,\0}
	return (res);
}



