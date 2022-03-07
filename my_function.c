#include "includes.h"

char *my_strcpy(char *dest, const char *src);

char	*my_strdup(char const *src){
	char	*dest;

	dest = malloc(sizeof(char) * (my_strlen(src) + 1));
	dest = my_strcpy(dest, src);
	return (dest);
}

char *my_strcpy(char *dest, const char *src){
	int i =0;
		while(src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i]='\0';

	return(dest);
}
