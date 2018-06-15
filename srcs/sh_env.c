/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:12:48 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/15 16:43:25 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_env(char **env, char **tab)
{
	char	**tmp_env;

	tmp_env = NULL;
	if (env && !tab[1])
		ft_puttab(env);
}

void	sh_env_unsetenv(char **env, char *name)
{
	int i;
	int n;

	i = 0;
	n = 0;
	if (!name)
		return ;
	while (env[i])
	{
		if ((n = sh_env_var(env, name)) != -1)
		{
			while (env[n + 1])
			{
				env[n] = env[n + 1];
				n++;
			}
			env[n] = NULL;
			return ;
		}
		i++;
	}
	ft_mprintf("ss2\n", "unsetenv: invalid name: ", name, NULL);
}

int		sh_env_var(char **env, char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (!*env || !env || !str)
		return (-1);
	while (env[i])
	{
		while (str[k] == env[i][j])
		{
			k++;
			j++;
			if (!str[k] && env[i][j] == '=')
				return (i);
		}
		i++;
		k = 0;
		j = 0;
	}
	return (-1);
}

char	**sh_env_cpy(char **env)
{
	char	**cpy;
	int		size;

	size = 0;
	while (env[size])
		size++;
	if (!(cpy = malloc(sizeof(char **) * (size + 1))))
		return (NULL);
	size = 0;
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
