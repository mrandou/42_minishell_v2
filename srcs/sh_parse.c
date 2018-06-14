/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:39:23 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/14 17:00:21 by mrandou          ###   ########.fr       */
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
	int	command;

	command = 0;
	ft_striter(cmd, (void *)ft_tolower);
	if (!ft_strcmp(cmd, "echo"))
		command = IS_ECHO;
	if (!command && !ft_strcmp(cmd, "cd"))
		command = IS_CD;
	if (!command && !ft_strcmp(cmd, "env"))
		command = IS_ENV;
	if (!command && !ft_strcmp(cmd, "setenv"))
		command = IS_SETENV;
	if (!command && !ft_strcmp(cmd, "unsetenv"))
		command = IS_UNSETENV;
	if (!command && !ft_strcmp(cmd, "exit"))
		command = IS_EXIT;
	return (command);
}
