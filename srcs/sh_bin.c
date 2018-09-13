/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:55:53 by mrandou           #+#    #+#             */
/*   Updated: 2018/09/13 16:54:14 by mrandou          ###   ########.fr       */
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
	{
		ft_tabdel(paths);
		return (0);
	}
	ft_tabdel(paths);
	sh_fork(pth, tab, env);
	ft_strdel(&pth);
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

void	sh_fork(char *cmd, char **tab, char **env)
{
	int			status;
	pid_t		cpid;
	struct stat	infos;

	status = 0;
	if (!lstat(cmd, &infos) && !(infos.st_mode & S_IXUSR))
	{
		ft_mprintf("ss2\n", cmd, ": Access forbidden", NULL);
		return ;
	}
	if ((cpid = fork()) == -1)
		return ;
	if (cpid == 0)
		exit(execve(cmd, tab, env));
	if (cpid > 0)
		waitpid(cpid, &status, 0);
}
