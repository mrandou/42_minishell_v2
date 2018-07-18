/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:36:58 by mrandou           #+#    #+#             */
/*   Updated: 2018/07/18 14:35:52 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sh_split(char *str)
{
	char	**tab;
	int		word;

	if (!(word = sh_split_wordcount(str)))
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	if (!(tab = sh_split_fill(tab, str, word)))
		return (NULL);
	return (tab);
}

char	**sh_split_fill(char **tab, char *str, int word)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (t < word)
	{
		while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n'))
			i++;
		if (str[i] == '"' && ft_strchr(&str[i + 1], '"'))
		{
			if (!(tab[t] = sh_split_quote(&str[i])))
				return (NULL);
			i = i + ft_strlen(tab[t]) + 1;
		}
		else if ((str[i] != ' ') && (str[i] != '\t') && (str[i] != '\n'))
			if (!(tab[t] = sh_split_cut(&str[i])))
				return (NULL);
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		t++;
	}
	tab[t] = NULL;
	return (tab);
}

char	*sh_split_quote(char *str)
{
	int		size;
	int		i;
	char	*rslt;

	size = 1;
	i = 0;
	++str;
	while (str[size] != '"' && str[size])
		size++;
	if (!(rslt = ft_strnew(size)))
		return (NULL);
	while (i < size)
		rslt[i++] = *str++;
	rslt[i] = '\0';
	return (rslt);
}

int		sh_split_wordcount(char *s)
{
	int	i;
	int	j;
	int	quote;
	int	p;
	int	word;

	word = 0;
	quote = 0;
	i = 0;
	p = 0;
	j = 1;
	if ((s[0] != ' ' && s[0] != '\t' && s[0] != '\n' && s[0]))
		word++;
	while (s[i])
	{
		if (s[i] == '"')
			quote++;
		p = quote % 2;
		if ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i] && !p)
			if (s[j] != ' ' && s[j] != '\t' && s[j] != '\n' && s[j])
				word++;
		i++;
		j = i + 1;
	}
	return (word);
}

char	*sh_split_cut(char *src)
{
	int		s;
	int		i;
	char	*sw;

	i = 0;
	s = 0;
	while (src[s] && src[s] != ' ' && src[s] != '\t' && src[s] != '\n')
		s++;
	if (!(sw = ft_strnew(s)))
		return (NULL);
	while (i < s)
		sw[i++] = *src++;
	sw[i] = '\0';
	return (sw);
}
