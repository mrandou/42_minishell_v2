/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:22:23 by mrandou           #+#    #+#             */
/*   Updated: 2018/09/12 17:45:54 by mrandou          ###   ########.fr       */
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
		ft_tabdel(tab);
		ft_tabdel(env);
		exit(0);
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
