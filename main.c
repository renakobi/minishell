#include <stdio.h>
#include <signal.h> 
#include <stdlib.h>
#include <readline/readline.h> 
#include <readline/history.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2 [i] && (i < n - 1) && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_signal_handler(int sig)
{
	printf("Caught signal %d\n", sig);
	// exit(sig);
	printf(">");
}

int	main(void)
{
	char	*a = "aaa";

	signal(SIGINT, ft_signal_handler);
	while (1)
	{
		a = readline(">");
		if (!a)
			break ;
		if (a && *a)
			add_history(a);
		if (ft_strncmp(a, "exit", 4) == 0)
		{
			free(a);
			break ;
		}
		printf("this is what you wrote %s\n", a);
		free(a);
	}
	rl_clear_history();
	return (0);
}
