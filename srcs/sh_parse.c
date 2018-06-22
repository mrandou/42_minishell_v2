/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:39:23 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/22 16:11:01 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sh_parse(char *line)
{
	char	**tab;

	if (!(tab = sh_split(line)) || !*tab)
	{
		ft_strdel(&line);
		return (NULL);
	}
	return (tab);
}

int		sh_command(char *cmd)
{
	int		command;
	char	*tmp;

	command = 0;
	tmp = ft_strlowcase(cmd);
	if (!ft_strcmp(tmp, "echo"))
		command = BLTN_ECHO;
	if (!command && !ft_strcmp(tmp, "cd"))
		command = BLTN_CD;
	if (!command && !ft_strcmp(tmp, "env"))
		command = BLTN_ENV;
	if (!command && !ft_strcmp(tmp, "setenv"))
		command = BLTN_SETENV;
	if (!command && !ft_strcmp(tmp, "unsetenv"))
		command = BLTN_UNSETENV;
	if (!command && !ft_strcmp(tmp, "exit"))
		command = BLTN_EXIT;
	return (command);
}

void	sh_specs(char **env, char **tab, int cmd)
{
	int		var;
	char	*current;
	int		i;

	var = 0;
	cmd = 0;
	i = 1;
	current = NULL;
	while (tab[i])
	{
		if (tab[i] && tab[i][0] == '~' && !tab[i][1])
		{
			if ((var = sh_env_var(env, "HOME")) == -1)
				ft_mprintf("s2\n", "env: variable HOME not set", NULL, NULL);
			if (var == -1 || (!(tab[i] = ft_strdup(env[var] + 5))))
				return ;
		}
		if (tab[1] && tab[1][0] == '-' && !tab[1][1])
		{
			var = sh_env_var(env, "OLDPWD");
			if (var == -1 || (!(tab[1] = ft_strdup(env[var] + 7))))
				if (!(tab[1] = sh_cd_get_path()))
					return ;
			ft_putendl(tab[1]);
		}
		i++;
	}
}
