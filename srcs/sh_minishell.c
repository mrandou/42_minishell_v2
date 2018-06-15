/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:55:53 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/15 16:12:11 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sh_binary(char **tab, char **env)
{
	char	**paths;
	char	*pth;
	int		pos;

	if (!access(tab[0], R_OK))
	{
		sh_fork(tab[0], tab, env);
		return (1);
	}
	if ((pos = sh_env_var(env, "PATH")) == -1)
		return (0);
	if (!(paths = ft_strsplit((env[pos] + 5), ':')))
		return (0);
	if (!(pth = sh_binary_path(paths, tab[0])))
		return (0);
	sh_fork(pth, tab, env);
	return (1);
}

char	*sh_binary_path(char **paths, char *cmd)
{
	char	*tmp;
	int		i;

	if (!paths || !cmd || !*paths)
		return (NULL);
	tmp = NULL;
	i = 0;
	while (paths[i])
	{
		if (!(tmp = ft_strmjoin(paths[i], "/", cmd)))
			return (NULL);
		if (!access(tmp, R_OK))
			return (tmp);
		i++;
		ft_strdel(&tmp);
	}
	return (NULL);
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
