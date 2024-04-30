#include "minishell.h"

char *create_path(char *cmd)
{
    char *path;
    struct stat statbuf;

    path = ft_strjoin("/bin/", cmd);
    if (stat(path, &statbuf) == 0)
    {
        return(path);
    }
    else
    {
        path = ft_strjoin("/usr/bin/", cmd);
        if (stat(path, &statbuf) == 0)
        {
            return(path);
        }
    }
    printf(RED "-minishell: %s: command not found \n" WHT, cmd);
    return(0);
}