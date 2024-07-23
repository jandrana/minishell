/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:07:39 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/23 13:42:15 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_and_execute(t_shell *shell, char *file, char **args)
{
	pid_t	pid;
	int		status;

	pid = safe_fork();
	if (pid == 0)
	{
		execve(file, args, shell->env);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else
			shell->exit_status = 128 + WTERMSIG(status);
	}
}

static char	*generate_full_path(char *path, char *arg)
{
	char	*path_slash;
	char	*full_path;

	path_slash = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_slash, arg);
	free(path_slash);
	return (full_path);
}

static void	find_executable_in_path(t_shell *shell, char **args, char **paths)
{
	char	*full_path;
	int		i;
	int		stop;

	stop = 0;
	i = 0;
	while (paths && paths[i] && stop == 0)
	{
		full_path = generate_full_path(paths[i++], args[0]);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			fork_and_execute(shell, full_path, args);
			stop = 1;
		}
		else if (access(full_path, F_OK) == 0)
		{
			ft_permission_denied(shell, full_path);
			stop = 2;
		}
		free(full_path);
	}
	free_array(&paths);
	if (stop == 0)
		ft_command_not_found_error(shell, args[0]);
}

static void	directly_executable(t_shell *shell, char **args)
{
	if (is_directory(shell, args[0]))
		ft_is_a_directory_error(shell, args[0]);
	else if (access(args[0], F_OK) == 0 && access(args[0], X_OK) == 0)
		fork_and_execute(shell, args[0], args);
	else if (access(args[0], F_OK) == 0)
		ft_permission_denied(shell, args[0]);
	else
		ft_command_not_found_error(shell, args[0]);
}

void	execute_bin(t_shell *shell, char **args)
{
	char	*path_env;
	char	**paths;

	shell->exit_status = 0;
	update_envp(shell);
	if (args[0][0] == '.' || args[0][0] == '/')
		directly_executable(shell, args);
	else
	{
		path_env = get_value(shell, "PATH");
		if (path_env)
		{
			paths = ft_split(path_env, ':');
			free(path_env);
			find_executable_in_path(shell, args, paths);
		}
		else
			ft_minishell_error(shell, "-minishell: PATH not set");
	}
}
