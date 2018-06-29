/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:12:48 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/29 17:06:27 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*BAD FREE*/

void	sh_env(char **env, char **tab)
{
	char	**tmp_env;
	int		i;
	int		oc;

	i = 1;
	oc = 0;
	tmp_env = NULL;
	if (env && !tab[1])
	{
		ft_puttab(env);
		return ;
	}
	if (!(tmp_env = sh_env_cpy(env)))
		return ;
	while (tab[i] && ft_strchr(tab[i], '='))
	{
		oc = ft_strpfo(tab[i], '=');
		tab[i][oc - 1] = '\0';
		if (!(tmp_env = sh_env_setenv(tmp_env, tab[i], tab[i] + oc)))
			return ;
		i++;
	}
	if (!(tmp_env = sh_execution(tmp_env, &tab[i], -1)))
		return ;
	sh_tabfree(tmp_env);
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

char	**sh_env_resize(char **env)
{
	int		i;
	char 	**cpy; 

	i = 0;
	while (env[i])
		i++;
	if (!(cpy = malloc(sizeof(char **) * (i + 2))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!(cpy[i] = ft_strdup(env[i])))
		{
			sh_tabfree(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i + 1] = 0;	
	sh_tabfree(env);
	return (cpy);
}

void	sh_env_replace(char **env, char *name, char *value)
{
	int		pos;
	char	*new;

	new = NULL;
	if (!name || !value)
		return ;
	pos = sh_env_var(env, name);
	if (pos != -1)
	{
		if (!(new = ft_strmjoin(name, "=", value)))
			return ;
		ft_strdel(&env[pos]);
		env[pos] = ft_strdup(new);
		ft_strdel(&new);
	}
}
