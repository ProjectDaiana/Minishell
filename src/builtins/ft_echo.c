#include "minishell.h"

void ft_echo(t_data *data, char **args)
{
    (void) data;
    int i;
    
    i = 1;
    printf(GRN "Executing builtin echo\n" RESET);
    while (args[i])
    {
        if (i > 1)
            printf(" ");
        if (ft_strcmp(args[i], "-n") == 0)
            i++;
        printf("%s", args[i]);
        i++;
    }
    if (ft_strcmp(args[1], "-n") != 0)
        printf("\n");
}