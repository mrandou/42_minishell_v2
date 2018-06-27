/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:45:26 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/27 17:53:42 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_read(char **env, int style)
{
	int		gnl;
	char	*line;
	char	**env_cpy;

	gnl = 0;
	line = NULL;
	if (!(env_cpy = sh_env_cpy(env)))
		return ;
	while (42)
	{
		if (style)
			ft_putstr(PROMPT);
		else
			ft_putstr("$> ");
		gnl = get_next_line(STDIN_FILENO, &line);
		if (gnl)
			if (!(env_cpy = sh_minishell(env_cpy, line, style)))
				return ;
	}
}

char	**sh_minishell(char **env, char *line, int style)
{
	char	**tab;
	char	**cpy;

	cpy = NULL;
	if (!(tab = sh_parse(line)))
		return (env);
	ft_strdel(&line);
	if ((cpy = sh_execution(env, tab, style)))
	{
		//sh_tabfree(tab);
		return (cpy);
	}
	sh_tabfree(tab);
	return (env);
}

char	**sh_execution(char **env, char **tab, int style)
{
	int		cmd;
	char	**cpy;
	
	cpy = NULL;	
	cmd = sh_command(tab[0]);
	if (cmd == BLTN_CD && style == -1)
		return (NULL);
	if (cmd == BLTN_EXIT && style == -1)
		cmd = 0;
	sh_specs(env, tab, cmd);
	if (cmd)
	{
		if ((cpy = sh_builtin(cmd, tab, env, style)))
			return (cpy);
	}
	else
		cmd = sh_binary(tab, env);
	if (!cmd)
		ft_mprintf("ss2\n", "minishell: command not found: ", tab[0], NULL);
	return (cpy);
}

int		main(int argc, char **argv, char **env)
{
	int style;

	style = 1;
	if (argv[1] && !ft_strcmp(argv[1], "-basic"))
		style = 0;
	sh_putheader(style);
	sh_read(env, style);
	return (argc);
}
