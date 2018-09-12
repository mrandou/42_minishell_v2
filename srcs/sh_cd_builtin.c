/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 17:45:39 by mrandou           #+#    #+#             */
/*   Updated: 2018/09/12 17:55:26 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sh_cd(char **env, char **tab)
{
	if (tab[1] && tab[2])
	{
		ft_mprintf("ss2\n", "cd: string not in pwd: ", tab[1], NULL);
		return (NULL);
	}
	if (tab[1] && !access(tab[1], R_OK))
	{
		if (sh_env_var(env, "OLDPWD") == -1)
			if (!(env = sh_env_setenv(env, "OLDPWD", " ")))
				return (NULL);
		if (sh_env_var(env, "PWD") == -1)
			if (!(env = sh_env_setenv(env, "PWD", " ")))
				return (NULL);
		sh_cd_change(env, tab[1]);
	}
	else if (sh_cd_2(env, tab))
		return (NULL);
	return (env);
}

int		sh_cd_2(char **env, char **tab)
{
	int	k;

	k = 0;
	if (!tab[1])
	{
		if ((k = sh_env_var(env, "HOME")) == -1)
			ft_mprintf("s2\n", "env: variable HOME not set", NULL, NULL);
		if (k != -1)
			sh_cd_change(env, env[k] + 5);
	}
	else
	{
		ft_mprintf("ss2\n", "cd: no such file or directory: ", tab[1], NULL);
		return (-1);
	}
	return (0);
}

void	sh_cd_change(char **env, char *path)
{
	char	*tmp;
	char	*current;
	int		var;

	var = sh_env_var(env, "PWD");
	if (!(current = sh_cd_get_path()))
		if (var == -1 || !(current = ft_strdup(env[var])))
			return ;
	sh_env_replace(env, "OLDPWD", current);
	if (!(tmp = ft_strmjoin(current, "/", path)))
	{
		ft_strdel(&current);
		return ;
	}
	if (chdir(path) && chdir(tmp))
	{
		ft_strdbldel(&tmp, &current);
		return ;
	}
	ft_strdbldel(&tmp, &current);
	if (!(current = sh_cd_get_path()))
		if (var == -1 || !(current = ft_strdup(env[var])))
			return ;
	sh_env_replace(env, "PWD", current);
	ft_strdel(&current);
}

char	*sh_cd_get_path(void)
{
	char	*buf;

	buf = NULL;
	if (!(buf = ft_strnew(100)))
		return (NULL);
	if (!(getcwd(buf, 100)))
	{
		ft_strdel(&buf);
		return (NULL);
	}
	return (buf);
}
