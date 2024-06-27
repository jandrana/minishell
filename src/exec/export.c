/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:55:01 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 15:50:04 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if count_words == 1 I need to find the local env variable 
// and export it (export VAR)
static char	**extract_key_value(char *arg)
{
	char	**key_value;

	key_value = ft_split(arg, '=');
	if (!valid_key_value(key_value) || count_words(key_value) != 2)
		free_array_null(&key_value);
	return (key_value);
}

static void	process_export_args(t_shell *shell, char **args)
{
	char	**key_value;
	int		i;

	i = 1;
	while (args[i])
	{
		key_value = extract_key_value(args[i]);
		if (key_value)
			add_new_env(shell, key_value[0], key_value[1]);
		else
		{
			shell->exit_status = 1;
			ft_putstr_fd("-minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		free_array_null(&key_value);
		i++;
	}
}

static void	show_exported_variables(t_shell *shell)
{
	t_env	*env;

	env = shell->l_env;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

// I need to program export VAR behaviour as well (exporting local variables)
void	export(t_shell *shell, char **args)
{
	shell->exit_status = 0;
	if (found_flags(args))
	{
		shell->exit_status = 1;
		print_invalid_flag_error_msg("export", args[1][1],
			"export [name[=value] ...]");
	}
	else
	{
		if (count_words(args) == 1)
			show_exported_variables(shell);
		else
			process_export_args(shell, args);
	}
}
