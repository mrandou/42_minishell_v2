/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:22:23 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/14 17:40:16 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_builtin(int cmd, char **tab, char **env, int style)
{
	(void)env;
	if (cmd == IS_EXIT)
	{
		sh_putender(style);
		sh_tabfree(tab);
		sh_tabfree(env);
		exit (0);
	}
	if (cmd == IS_ECHO)
		sh_echo(tab);
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
