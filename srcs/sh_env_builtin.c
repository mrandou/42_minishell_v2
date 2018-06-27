/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:38:02 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/27 14:37:43 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sh_env_setenv(char **env, char *name, char *value)
{
	char	**cpy_env;
	int		var;

	var = 0;
	if (!name || !value)
	{	
		ft_mprintf("ss2\n", "setenv: invalid name or value",
		 "\nusage: setenv NAME VALUE", NULL);
		return (NULL);
	}
	if ((var = sh_env_var(env, name)) != -1)
	{
		if (!(env[var] = ft_strmjoin(env[var], ":", value)))
			return (NULL);
		return (env);
	}
	var = 0;
	while (env[var])
		var++;
	if (!(cpy_env = sh_env_resize(env)))
		return (NULL);
	if (!(cpy_env[var] = ft_strmjoin(name, "=", value)))
		return (NULL);
	return (cpy_env);
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
			ft_strdel(&env[n]);
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
