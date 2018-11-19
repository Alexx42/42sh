/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:01:02 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 10:44:38 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <env.h>

static void	replace(char **dst, char *s)
{
	if (s == NULL)
		return ;
	free(*dst);
	*dst = s;
}

static char	*ft_strreplace(char *s, char *start, size_t r_len, char *by)
{
	size_t	s_len;
	size_t	e_len;
	size_t	by_len;
	size_t	n_len;
	char	*n;

	s_len = start - s;
	e_len = ft_strlen(s) - r_len - s_len;
	by_len = ft_strlen(by);
	n_len = s_len + by_len + e_len;
	MCK(n = (char*)malloc(sizeof(char) * (n_len + 1)), NULL);
	n[n_len] = '\0';
	ft_strncpy(n, s, s_len);
	ft_strcpy(n + s_len, by);
	ft_strcpy(n + s_len + by_len, start + r_len);
	return (n);
}

static char	*expand_tilde(char *str)
{
	char	*home_str;

	home_str = ft_getenv("HOME"); // use local variable? store HOME var?
	return (ft_strreplace(str, str, 1, home_str));
}

static char	*expand_var(char *str)
{
	char	*start;
	char	*next;
	char	*value;
	size_t	len;

	if ((start = ft_strchr(str, '$')) == NULL)
		return (NULL);
	next = ft_strchr(start, '$');
	len = next ? next - start : ft_strlen(str);
	if ((value = ft_getenv(str)) == NULL
	|| (value = get_local_var(str)) == NULL)
	)
		return (NULL);
	return (ft_strreplace(str, start, len, value));
}

int			expand(char **argv)
{
	size_t	i;
	char	*expanded;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '~')
			replace(argv + i, expand_tilde(argv[i]));
		while ((expanded = expand_var(argv[i])))
			replace(argv + i, expanded);
		i++;
	}
	return (0);
}