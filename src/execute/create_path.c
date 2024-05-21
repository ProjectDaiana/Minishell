#include "minishell.h"

char    *create_path(char *cmd, t_data *data)
{
    char        *path;
    struct stat statbuf;

    path = ft_strjoin("/bin/", cmd);
    if (stat(path, &statbuf) == 0)
        return (path);
    free(path);
    path = ft_strjoin("/usr/bin/", cmd);
    if (stat(path, &statbuf) == 0)
            return (path);
    free(path);
    //printf("-minishell: %s: command not found \n", cmd);
    data->exit_code = 127;
    return (NULL);
}
