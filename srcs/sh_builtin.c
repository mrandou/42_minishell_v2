/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:22:23 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/21 17:30:40 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sh_builtin(int cmd, char **tab, char **env, int style)
{
	char	**cpy;

	cpy = NULL;
	if (cmd == BLTN_EXIT)
	{
		sh_putender(style);
		sh_tabfree(tab);
		sh_tabfree(env);
		exit (0);
	}
	if (cmd == BLTN_ECHO)
		sh_echo(tab);
	if (cmd == BLTN_ENV)
		sh_env(env, tab);
	if (cmd == BLTN_UNSETENV)
		sh_env_unsetenv(env, tab[1]);
	if (cmd == BLTN_SETENV)
		if (!(cpy = sh_env_setenv(env, tab[1], tab[2])))
			return (NULL);
	if (cmd == BLTN_CD)
		if (!(cpy = sh_cd(env, tab)))
			return (NULL);
	return (cpy);
}

void	sh_echo(char **tab)
{
	int	i;
	int	noendl;

	i = 1;
	noendl = 0;
	if (!tab || !tab[1])
	{
		ft_putbn();
		return ;
	}
	if (!ft_strcmp(tab[1], "-n"))
		noendl = 1;
	i += noendl;
	while (tab[i])
	{
		ft_putstr(tab[i++]);
		if (tab[i])
			ft_putchar(' ');
	}
	if (!noendl)
		ft_putbn();
}

char	**sh_cd(char **env, char **tab)
{
	if (tab[2] && tab[1])
	{
		ft_mprintf("ss2\n", "cd: string not in pwd: ", tab[1], NULL);
		return (NULL);
	}
	if (!access(tab[1], R_OK))
	{
		if (sh_env_var(env, "OLDPWD") == -1)
			if (!(env = sh_env_setenv(env, "OLDPWD", " ")))
				return (NULL);
		if (sh_env_var(env, "PWD") == -1)
			if (!(env = sh_env_setenv(env, "PWD", " ")))
				return (NULL);
		sh_cd_access(env, tab[1]);
	}
	else
	{
		ft_mprintf("ss2\n", "cd: no such file or directory: ", tab[1], NULL);
		return (NULL);
	}
	return (env);
}

void	sh_cd_access(char **env, char *path)
{
	char	*tmp;
	char	*current;
	int		absolu;

	if (!(current = sh_cd_get_path()))
		return ;
	sh_env_replace(env, "OLDPWD", current);
	absolu = chdir(path);
	if (!(tmp = ft_strmjoin(current, "/", path)))
			return ;
	if (absolu)
	{
		if (chdir(tmp))
		{
			ft_strdbldel(&tmp, &current);		
			return ;
		}
	}
	if (!(current = sh_cd_get_path()))
	{
		ft_strdbldel(&tmp, &current);		
		return ;
	}
	sh_env_replace(env, "PWD", current);
	ft_strdbldel(&tmp, &current);
}

char	*sh_cd_get_path(void)
{
	char	*buf;

	buf = NULL;
	if (!(buf = ft_strnew(100)))
		return (NULL);
	if (!(getcwd(buf, 100)))
		return (NULL);
	return (buf);
}
