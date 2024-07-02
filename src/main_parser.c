/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/01 22:49:45 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	g_signal;

void	signal_handler(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*read_input(void)
{
	char	*input;

	input = readline("\033[1;35mminishell ➜\033[0m ");
	return (input);
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	t_cmd	*parsed_input;
	char	*input;
	bool	stop;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	stop = false;
	while (!stop)
	{
		input = read_input();
		if (input && input[0] != '\0')
		{
			parsed_input = parser(input, shell);
			free(parsed_input);
			if (!ft_strncmp(input, "exit", 10))
			{
				free(input);
				stop = true;
			}
		}
	}
	free(input);
	free_shell(shell);
	return (0);
}
