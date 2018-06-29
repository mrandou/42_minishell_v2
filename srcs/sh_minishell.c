/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:55:53 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/29 17:00:11 by mrandou          ###   ########.fr       */
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
		sh_tabfree(paths);	
		return (0);
	}
	sh_tabfree(paths);
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

char	*sh_replace(char *str, char *old, char *new)
{
	char	*tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!str || !old || !new)
		return (NULL);
	if (!(tmp = ft_strnew(ft_strlen(str) - ft_strlen(old) + ft_strlen(new))))
		return (NULL);
	while (str[k] && ft_strstr(&str[k + 1], old))
		tmp[i++] = str[k++];
	if (!(new = ft_strjoin(tmp, new)))
		return (NULL);
	ft_strdel(&tmp);
	if (str[k])
		if (!(tmp = ft_strjoin(new, ft_strstr(str, old) + ft_strlen(old))))
			return (NULL);
	ft_strdbldel(&str, &new);
	return (tmp);
}
