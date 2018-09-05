/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_style.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:29:17 by mrandou           #+#    #+#             */
/*   Updated: 2018/09/05 17:52:16 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_putheader(int style)
{
	if (!style)
	{
		ft_putendl("MINISHELL BASIC VERSION");
		ft_putbn();
		return ;
	}
	ft_putstr("\033[38;5;");
	ft_putnbr(sh_random());
	ft_putstr("m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗"
	"     ██╗     \n████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║ "
	"    ██║     \n██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║ "
	"    ██║     \n██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║ "
	"    ██║     \n██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗██"
	"█████╗███████╗\n╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝"
	"╚══════╝╚══════╝\n              "
	"                                                     \033[0m\n\n");
}

void	sh_putender(int style)
{
	int	random;

	if (style != 1)
		return ;
	random = sh_random();
	if (random == -1)
		return ;
	ft_putbn();
	ft_mprintf("ss\n", "\n", "⤜⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤"
	"⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤🍎⏤⏤⏤⏤⏤►\n", NULL);
	ft_putstr("\033[38;5;");
	ft_putnbr(random);
	ft_putstr("m                              .-.            \n              "
		"                : :            \n"
		",-.,-.,-..--.  .--.  ,-.,-. .-' : .--."
		" .-..-.\n: ,. ,. :: ..'' .; ; : ,. :' .; :' .; :: :; :\n:_;:_;:_;:_;  "
		"`.__,_;:_;:_;`.__.'`.__.'`.__.'\n                                   "
		"          \033[0m\n");
}

int		sh_random(void)
{
	int		fd;
	int		nb;
	char	*buf;

	if (!(buf = ft_strdup("4")))
		return (-1);
	if ((fd = open("/dev/random", O_RDONLY)) == -1)
		return (-1);
	if ((read(fd, buf, 1)) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	nb = buf[0];
	ft_strdel(&buf);
	nb = nb % 220;
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

void	sh_putprompt(char **env)
{
	int	pwd;
	int	home;
	int	size;

	ft_putbn();
	size = 0;
	home = sh_env_var(env, "HOME");
	pwd = sh_env_var(env, "PWD");
	if (home != -1)
		size = ft_strlen(env[home] + 5);
	if (home != -1 && pwd != -1 && !ft_strncmp(env[home] + 5,
	env[pwd] + 4, size))
		ft_mprintf("sss", "\033[1m\033[32m~", env[pwd] + 4 + size, " ");
	else if (pwd != -1)
		ft_mprintf("sss", "\033[1m\033[32m", env[pwd] + 4, " ");
	ft_putstr(PROMPT);
}
