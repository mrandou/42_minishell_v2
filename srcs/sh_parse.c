/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:39:23 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/21 17:48:12 by mrandou          ###   ########.fr       */
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
