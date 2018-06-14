/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:34:38 by mrandou           #+#    #+#             */
/*   Updated: 2018/06/14 16:32:43 by mrandou          ###   ########.fr       */
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

#define		IS_ECHO			1
#define		IS_CD			2
#define		IS_ENV			3
#define		IS_SETENV		4
#define		IS_UNSETENV		5
#define		IS_EXIT			-1

/*///////////////////////////////MINISHELL////////////////////////////////////*/

void		sh_read(char **env);
void		sh_minishell(char **env, char *line);

/*////////////////////////////////SH_PARSE////////////////////////////////////*/

char		**sh_parse(char *line);
int			sh_command(char *cmd);

/*////////////////////////////////SH_BUILTIN//////////////////////////////////*/

void		sh_builtin(int cmd, char **tab, char **env);

/*//////////////////////////////////ENV///////////////////////////////////////*/

char		**sh_env_cpy(char **env);

/*////////////////////////////////SH_SPLIT////////////////////////////////////*/

char		**sh_split(char *str);
char		**sh_split_fill(char **tab, int word);
char		*sh_split_quote(char *str);
int			sh_split_wordcount(char *str);
char		*sh_split_cut(char *src);

/*////////////////////////////////SH_STYLE////////////////////////////////////*/

void		sh_putheader(void);
void		sh_putender(void);
int			sh_random(void);

#endif
