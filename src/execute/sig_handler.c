#include "minishell.h"

void sig_handler(int sig)
{
  if (sig == SIGINT)
  {
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
  }
}