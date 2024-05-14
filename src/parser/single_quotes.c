#include "minishell.h"

// ech"o" hi = hi
// ech"o" h''i = hi
// [1:02 PM] plandolf
// ech"o" h'""'i = h""i
// [1:02 PM] plandolf
// ech"o" h"'""'"i = h''i
// e''ch"o" h"'""'"i = h''i
// [1:05 PM] plandolf
// e' 'ch"o" h"'""'"i = command not found
// e" "ch"o" h"'""'"i = command not found
// 'ech"o"' h"'""'"i = not found
// 'ech"'o'"' h"'""'"i = not found
// 'ech'o'' h"'""'"i = h''i
// ''ech'o''' h"'""'"i = h''i
// ARG= ho
// ec$ARG hi = hi
// ec$ARG $A''RG = RG :cara_pensativa::cara_pensativa::cara_pensativa:
// [1:05 PM] plandolf
// ec$A''RG hi = ecRG: command not found


// void rm_quotes(char *str)
// {
//     int len = ft_strlen(str);
//     if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
// 	{
//         ft_memmove(str, str + 1, len - 2);
//         str[len - 2] = '\0';
//     }
// }

//When quotes check if quotes are closed
//If not closed, wait for closing quote

//Check for number of pairs, if number of pairs is impair quotes are valid,
//If number of pairs is pair quotes are invalid

//If quotes are closed and valid, remove quotes and store in quoted, avoid interpreting inside

//else if quotes are invalid ignore them and continue with rest of the code

//If there is a pair of double quotes inside the single quotes, interpret input and write double quotes or not depending if single quotes are escaoing them or not
//else
///Wait for closing quote

int is_even(char *str, char c)
{
    int count = 0;
    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
	if ((count/2) % 2 == 0)
		return (0);
	return (count);
}

void rm_quotes(char *str)
{
	char *unquoted;
	unquoted = ft_strtrim(str, "'");
	printf(GRN "removed: %s\n" RESET, unquoted);
	free(str);
	str = ft_strdup(unquoted);
	free(unquoted);
}

void add_quotes_pair(char *args)
{
	char *quoted;

	quoted = ft_strjoin("'", args);
	quoted = ft_strjoin(quoted, "'");
	printf(BLU "added: %s\n" RESET, quoted);
	free(args);
	args = ft_strdup(quoted);
	free(quoted);
}

void sin_quotes(char *args)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (ft_strchr(args, '\'') == NULL) //If no quotes, return
		return ;
	else
	{
		// Check if quotes are closed
		// Check for number of pairs, if number of pairs is impair keep 1 pair
		if(is_even(args, '\'') == 0 || ft_strchr(args, '$') == NULL)
			rm_quotes(args);
		else
		{
				rm_quotes(args);
				add_quotes_pair(args);
		}
	}
	printf("it stays: %s\n", args);
}