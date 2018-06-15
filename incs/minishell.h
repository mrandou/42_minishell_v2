/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:34:38 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/15 16:38:33 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H
# define __MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# ifndef PROMPT
#  define PROMPT "\n\033[1m\033[32m∴ > \033[0m"
# endif

#define		BLTN_ECHO			1
#define		BLTN_CD				2
#define		BLTN_ENV			3
#define		BLTN_SETENV			4
#define		BLTN_UNSETENV		5
#define		BLTN_EXIT			6

/*///////////////////////////////MINISHELL////////////////////////////////////*/

void		sh_read(char **env, int style);
void		sh_minishell(char **env, char *line, int style);

/*//////////////////////////////SH_MINISHELL//////////////////////////////////*/

int			sh_binary(char **tab, char **env);
char		*sh_binary_path(char **paths, char *cmd);
void		sh_tabfree(char **tab);
void		sh_fork(char *cmd, char **tab, char **env);


/*////////////////////////////////SH_PARSE////////////////////////////////////*/

char		**sh_parse(char *line);
int			sh_command(char *cmd);

/*////////////////////////////////SH_BUILTIN//////////////////////////////////*/

void		sh_builtin(int cmd, char **tab, char **env, int style);
void		sh_echo(char **tab);

/*//////////////////////////////////ENV///////////////////////////////////////*/

void		sh_env(char **env, char **tab);
void		sh_env_unsetenv(char **env, char *name);
int			sh_env_var(char **env, char *str);
char		**sh_env_cpy(char **env);

/*////////////////////////////////SH_SPLIT////////////////////////////////////*/

char		**sh_split(char *str);
char		**sh_split_fill(char **tab, char *str, int word);
char		*sh_split_quote(char *str);
int			sh_split_wordcount(char *str);
char		*sh_split_cut(char *src);

/*////////////////////////////////SH_STYLE////////////////////////////////////*/

void		sh_putheader(int style);
void		sh_putender(int style);
int			sh_random(void);

#endif
