/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:33:15 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/16 20:07:53 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <path.h>
#include <libft.h>

static int	get_env_index(const char *name)
{
	extern char	**environ;
	int			i;
	char		*end;
	int			len;

	len = ft_strlen(name);
	i = 0;
	while (environ[i])
	{
		if ((end = ft_strrchr(environ[i], '=')) == NULL)
			;
		if (end - environ[i] != len)
			;
		else if (ft_strncmp(environ[i], name, end - environ[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int			ft_unsetenv(const char *name)
{
	extern char	**environ;
	int			i;
	int			found;

	found = 0;
	while ((i = get_env_index(name)) != -1)
	{
		found++;
		free(environ[i]);
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
		if (update_path_map((char*)name))
			return (-1);
	}
	return (found == 0);
}
