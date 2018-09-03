/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:12:56 by mrandou           #+#    #+#             */
/*   Updated: 2018/09/03 16:11:20 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_line_expand(char *line, char **env)
{
	int	i;
	int	var;

	i = 0;
	var = 0;
	if (!(line = sh_expand_simple(line, env)))
		return (NULL);
	while (line[i])
	{
		if (line[i] == '~' && (!ft_isprint(line[i - 1]) || line[i - 1] == ' '))
			if (!(line = sh_expand_home(line, env, i)))
				return (NULL);
		if (line[i] == '-' && (!ft_isprint(line[i - 1]) || line[i - 1] == ' ')
		&& (line[i + 1] == ' ' || !line[i + 1] || line[i + 1] == '\t'))
			if (!(line = sh_expand_old(line, env)))
				return (NULL);
		if (line[i] == '$')
			if (!(line = sh_expand_var(line, env)))
				return (NULL);
		i++;
	}
	return (line);
}

char	*sh_expand_simple(char *line, char **env)
{
	int		k;
	char	*tmp;

	tmp = NULL;
	k = 0;
	while (!ft_isprint(line[k]) && line[k] != ' ')
		k++;
	if (line[k] == 'c' && line[k + 1] == 'd')
	{
		k += 2;
		while (line[k] && (!ft_isprint(line[k]) && line[k] != ' '))
			k++;
		if (!line[k])
		{
			if ((k = sh_env_var(env, "HOME")) == -1)
				ft_mprintf("s2\n", "env: variable HOME not set", NULL, NULL);
			if (k == -1 || !(tmp = ft_strmjoin(line, " ", (env[k] + 5))))
				return (line);
			ft_strdel(&line);
			return (tmp);
		}
	}
	return (line);
}

char	*sh_expand_home(char *line, char **env, int i)
{
	int	var;

	var = 0;
	if (ft_isprint(line[i + 1]) && line[i + 1] != ' ' && line[i + 1] != '/')
	{
		ft_putendl_fd("minishell: no such user or named directory", 2);
		ft_strdel(&line);
		return (NULL);
	}
	if ((var = sh_env_var(env, "HOME")) == -1)
		ft_mprintf("s2\n", "env: variable HOME not set", NULL, NULL);
	if (var == -1 || (!(line = sh_replace(line, "~", env[var] + 5))))
	{
		ft_strdel(&line);
		return (NULL);
	}
	return (line);
}

char	*sh_expand_old(char *line, char **env)
{
	int	var;

	var = 0;
	if ((var = sh_env_var(env, "OLDPWD")) == -1)
		ft_putendl_fd("env: variable OLDPWD not set", 2);
	if (var == -1 || (!(line = sh_replace(line, "-", env[var] + 7))))
	{
		if (var == -1 && line)
			ft_strdel(&line);
		return (NULL);
	}
	ft_putendl(env[var] + 7);
	return (line);
}

char	*sh_expand_var(char *line, char **env)
{
	char	*tmp;
	int		i;
	int		k;

	i = (ft_strpfo(line, '$') - 1);
	k = i;
	while (ft_isprint(line[k]) && line[k] != ' ' && line[k] != '/')
		k++;
	if (!(tmp = ft_strrec(line, i, k)))
		return (NULL);
	if ((i = sh_env_var(env, tmp + 1)) == -1)
	{
		if (!(line = sh_replace(line, tmp, "\0")))
			return (NULL);
		ft_strdel(&tmp);
		return (line);
	}
	if (!(line = sh_replace(line, tmp, (env[i] + ft_strlen(tmp)))))
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	ft_strdel(&tmp);
	return (line);
}
