/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:34:38 by mrandou           #+#    #+#             */
/*   Updated: 2018/09/12 17:56:25 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H
# define __MINISHELL_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef PROMPT
#  define PROMPT "\033[1m\033[32m∴ > \033[0m"
# endif

typedef enum		e_bltn
{
	BLTN_ECHO = 1,
	BLTN_CD,
	BLTN_ENV,
	BLTN_SETENV,
	BLTN_UNSETENV,
	BLTN_EXIT
}					t_bltn;

void		sh_read(char **env, int style);
char		**sh_minishell(char **env, char *line, int style);
char		**sh_execution(char **env, char **tab, int style);

int			sh_binary(char **tab, char **env);
char		*sh_binary_path(char **paths, char *cmd);
void		sh_fork(char *cmd, char **tab, char **env);

char		**sh_parse(char *line);
int			sh_command(char *cmd);

char		*sh_line_expand(char *line, char **env);
char		*sh_expand_home(char *line, char **env, int i);
char		*sh_expand_old(char *line, char **env);
char		*sh_expand_var(char *line, char **env);

char		**sh_builtin(int cmd, char **tab, char **env, int style);
void		sh_echo(char **tab);

char		**sh_cd(char **env, char **tab);
int			sh_cd_2(char **env, char **tab);
void		sh_cd_change(char **env, char *path);
char		*sh_cd_get_path(void);

void		sh_env(char **env, char **tab);
int			sh_env_var(char **env, char *str);
char		**sh_env_cpy(char **env);
char		**sh_env_resize(char **env);
void		sh_env_replace(char **env, char *name, char *value);

char		**sh_env_setenv(char **env, char *name, char *value);
int			sh_env_setenv_append(char **env, char *name, char *value);
void		sh_env_unsetenv(char **env, char *name);

char		**sh_split(char *str);
char		**sh_split_fill(char **tab, char *str, int word);
char		*sh_split_quote(char *str);
int			sh_split_wordcount(char *str);
char		*sh_split_cut(char *src);

void		sh_putheader(int style);
void		sh_putender(int style);
int			sh_random(void);
void		sh_putprompt(char **env);

#endif
