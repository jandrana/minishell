/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:44:12 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/02 15:27:06 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
		i++;
	return (i);
}

bool	equal_str(char *s1, char *s2)
{
	int	len1;
	int	len2;

	if (!s1 || !s2)
		return (false);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	return ((len1 == len2) && (ft_strncmp(s1, s2, len1) == 0));
}

t_env	*find_last_env(t_env *lst)
{
	t_env	*current;

	current = lst;
	while (current && current->next)
		current = current->next;
	return (current);
}
