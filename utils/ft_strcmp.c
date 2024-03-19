#include "../minishell.h"

int ft_strcmp(const char *str1, const char *str2)
{
    int i;

    i = 0;
    if (str1 == NULL || str2 == NULL)
        return(-1);
    while(str1[i] && (str1[i] == str2[i]))
        i++;
    if (str1[i] != str2[i])
        return(1);
    return(0); 
}