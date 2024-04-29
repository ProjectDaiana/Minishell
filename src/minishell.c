#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	static t_data data;
	

    (void)argc;
    (void)argv;

    cpy_envs(&data, envp);
    while (1)
    {
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN); 
        char *input = readline(YEL "Minishell > " RESET);
        if(!input)
            break;
        parse(input, &data);
        if (input != NULL)
            add_history(input);
    //    validate_cmds();
        if (data.num_of_children == 1 && is_builtin(data.commands))
        {
            printf(YEL "Executing simple cmd in main\n" RESET);
            exec_cmd(&data, data.commands);
        }
        else
		{
			printf(YEL "Fork\n" RESET);
        	pipe_cmds(&data);
		}
	    free(input);
    }
    return (0);
}
