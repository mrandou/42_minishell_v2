/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:12:48 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/14 14:27:46 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sh_env_cpy(char **env)
{
	char	**cpy;
	int		size;

	size = 0;
	while (env[size])
		size++;
	if (!(cpy = malloc(sizeof(char **) * (size + 1)))))
		return (NULL);
	size = 0
	while (env[size])
	{
		if (!(cpy[size] = ft_strdup(env[size])))
		{
			sh_tabfree(cpy);
			return (NULL);
		}
		size++;
	}
	cpy[size] = 0;
	return (cpy);
}
