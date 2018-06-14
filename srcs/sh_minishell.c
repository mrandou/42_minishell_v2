/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:55:53 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/14 18:07:03 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sh_binary(char **tab, char **env)
{
	if (!access(tab[0], R_OK))
	{
		sh_fork(tab[0], &tab[1], env);
		return (1);
	}
	return (0);
}

void	sh_tabfree(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
		ft_strdel(tab + i++);
	free(tab);
}

void	sh_fork(char *cmd, char **tab, char **env)
{
	int		status;
	pid_t	cpid;

	status = 0;	
	if ((cpid = fork()) == -1)
		return ;
	if (cpid == 0)
		exit(execve(cmd, tab, env));
	if (cpid > 0)
		waitpid(cpid, &status, 0);
}
