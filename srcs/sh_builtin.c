/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:22:23 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/14 16:32:38 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_builtin(int cmd, char **tab, char **env)
{
	if (cmd == IS_ECHO)
	{
		while (tab)
			ft_mprintf("ss", ++*tab, " ", NULL);
		if (!ft_strcmp(tab[1], "-n"))
			ft_putbn();
	}
}
