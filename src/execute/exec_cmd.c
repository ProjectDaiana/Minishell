#include "minishell.h"

// void exec_ls(char *str)
// {
//     char *args[] = {"ls", "-l", NULL}; //
//     if (strcmp(str, "ls") == 0)
//     {
//         if (execve("/bin/ls", args, envp) == -1)
//         {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     }
// }

// void exec_cmd(t_data *data, char *args[])
// {
//     char *path;

//     path = create_path(args[0]);
//     if (args[0] == NULL)
//     {
//         printf(RED "Something is wrong. 'null' is being passed as cmd\n" RESET);
//         exit (1);
//     }
//     if (ft_strcmp(args[0], "cd") == 0)
//         ft_cd(data, data->commands->args[1]);
//     if (ft_strcmp(args[0], "echo") == 0)
//         ft_echo(data, data->commands->args);
//     if (ft_strcmp(args[0], "env") == 0)
//     {
//         printf(GRN "Executing builtin env\n" RESET);
//         ft_env(*data);
//     }    
//     // else if (ft_strcmp(args[0][0], "exit") == 0)
//     // {
//     //     printf("Executing builtin exit\n");
//     //     ft_exit();
//     // }  
//     // else if (ft_strcmp(args[0][0], "export") == 0)
//     // {
//     //     printf("Executing builtin export\n");
//     //     ft_export();
//     // }  
//     else if (ft_strcmp(args[0], "pwd") == 0)
//     {
//         //printf(GRN "Executing builtin pwd\n" RESET);
//         ft_pwd(data);
//     }
//     // else if (ft_strcmp(args[0][0], "unset") == 0)
//     // {
//     //     printf(GRN"Executing builtin unset\n"RESET);
//     //     ft_unset();
//     // }
//     else if (is_builtin(args[0]) == 0)
//     {
//         printf(GRN "Non-builtin" RESET);
//         //prototype: int execve(const char *path, char *const argv[], char *const envp[]);
//         if (execve(path, data->commands->args, data->envp) == -1)
//             {
//                 perror("execve");
//                 exit(EXIT_FAILURE);
//             }
//    }
//     //exit(0);
// }

void exec_cmd(t_data *data, char *cmd)
{
    char *path;

    path = create_path(cmd);
    if (cmd == NULL)
    {
        printf(RED "Something is wrong. 'null' is being passed as cmd\n" RESET);
        exit (1);
    }
    if (ft_strcmp(cmd, "cd") == 0)
        ft_cd(data, data->commands->args[1]);
    if (ft_strcmp(cmd, "echo") == 0)
        ft_echo(data, data->commands->args);
    if (ft_strcmp(cmd, "env") == 0)
    {
        printf(GRN "Executing builtin env\n" RESET);
        ft_env(*data);
    }    
    // else if (ft_strcmp(cmd[0], "exit") == 0)
    // {
    //     printf("Executing builtin exit\n");
    //     ft_exit();
    // }  
    // else if (ft_strcmp(cmd[0], "export") == 0)
    // {
    //     printf("Executing builtin export\n");
    //     ft_export();
    // }  
    else if (ft_strcmp(cmd, "pwd") == 0)
    {
        //printf(GRN "Executing builtin pwd\n" RESET);
        ft_pwd(data);
    }
    // else if (ft_strcmp(cmd[0], "unset") == 0)
    // {
    //     printf(GRN"Executing builtin unset\n"RESET);
    //     ft_unset();
    // }
    else if (is_builtin(cmd) == 0)
    {
        printf(GRN "Non-builtin" RESET);
        //prototype: int execve(const char *path, char *const argv[], char *const envp[]);
        if (execve(path, data->commands->args, data->envp) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
   }
    //exit(0);
}