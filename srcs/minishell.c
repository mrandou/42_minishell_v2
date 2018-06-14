/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:45:26 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/14 16:34:21 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_read(char **env)
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
		ft_putstr(PROMPT);
		gnl = get_next_line(STDIN_FILENO, &line);
		if (gnl)
			sh_minishell(env_cpy, line);
	}
}

void	sh_minishell(char **env, char *line)
{
	char	**tab;
	int		cmd;

	cmd = 0;
	if (!(tab = sh_parse(line)))
		return;
	cmd = sh_command(tab[0]);
	if (cmd)
		sh_buitlin(cmd, tab, env);
	else
		cmd = sh_binary(tab, env);
	sh_tabfree(tab);
	if (cmd)
		ft_mprintf("ss2\n", "minishell: command not found: ", tab[0], NULL);
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

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	sh_putheader(void);
	sh_read(env);
	return (0);
}
