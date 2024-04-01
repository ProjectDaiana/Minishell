#include "minishell.h"

int parse(char *input, t_data *data)
{
    char    *line_copy;
    char    **future_children;
    int     index;

    check_NULL(input);
    line_copy = strdup(input);
    check_NULL(line_copy);
    
    sub_quot(line_copy, data); //substitute double quotes

    future_children = ft_split(line_copy, '|');
    free(line_copy);

    t_cmd *head = NULL;
    t_cmd *current = NULL;
    index = 0;
    while (future_children[index])
    {
        t_cmd *newNode = (t_cmd *)malloc(sizeof(t_cmd));
        newNode->args = ft_split(future_children[index], ' ');
        newNode->num_args = 0;
        newNode->pipe_in = -1;
        newNode->pipe_out = -1;
        newNode->redirect_in = -1;
        newNode->redirect_out = -1;
        newNode->next = NULL;

        if (head == NULL)
            head = newNode;
        else
            current->next = newNode;
        current = newNode;
        index++;
    }
    data->commands = head;
    data->num_of_children = index;

    current = head;
    t_cmd *previous = NULL;
    while (current)
    {
        if (previous)
        {
            int p[2];
            pipe(p);
            previous->pipe_out = p[PIPE_WRITE];
            current->pipe_in = p[PIPE_READ];
        }
        previous = current;
        current = current->next;
    }

    // current = head;
    // while (current)
    // {
    //     printf("PIPE IN: %d\n", current->pipe_in);
    //     printf("PIPE OUT: %d\n", current->pipe_out);
    //     previous = current;
    //     current = current->next;
    // }
    return (0);
}


// int pipe_it(t_data *data)
// {
//     pid_t pid;
//     int i = 0;

//     char **commands;
//     commands = malloc(5 * sizeof(char *));
//     commands[0] = *data->commands[0].args;
//     commands[1] = *data->commands[1].args;
//     // commands[2] = data->commands[2].args;

//     int read_e = data->commands[0].pipe_out;
//     int write_e = data->commands[1].pipe_in;
//     // printf("PIPE 1: %d\n", read_e);
//     // printf("PIPE 2: %d\n", write_e);

//     int pipe[2];
//     pipe[PIPE_READ] = read_e;
//     pipe[PIPE_WRITE] = write_e;
//     printf(BLU "Num of int children passed to struct: %d\n " RESET, data->num_of_children);
//     while (i < data->num_of_children)
//     {
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork error");
//             return (1);
//         }
//         if (pid == 0)
//         {
//             if (i == 0)
//             {
//                 printf("Loop1 %s ", commands[i]);
//                 close(pipe[PIPE_READ]);
//                 dup2(pipe[PIPE_WRITE], STDOUT);
//                 close(pipe[PIPE_WRITE]);
//             }
//             if (i == 1)
//             {
//                 printf("Loop2 %s ", commands[i]);
//                 close(pipe[PIPE_WRITE]);
//                 dup2(pipe[PIPE_READ], STDIN);
//                 close(pipe[PIPE_READ]);
//             }
//             printf(BLU "Passing command: %s\n " RESET, commands[i]);
//             // PROTOTYPE: void exec_cmd(t_data *data, char *const cmd[])
//             //   exec_cmd(data, &commands[i]);
//             //  if (execve(paths[i], &commands[i], NULL) == -1)
//             //  {
//             //      perror(RED"execve"RESET);
//             //      exit(1);
//             //  }
//         }
//         else
//         {
//             printf("%d\n", pid);
//             printf("Parent waiting\n");
//             wait(NULL);
//             close(pipe[PIPE_READ]);
//             close(pipe[PIPE_WRITE]);
//         }
//         i++;
//     }
//     return 0;
// }
