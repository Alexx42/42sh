/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 06:14:19 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/21 11:17:01 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <ft_printf.h>
#include <libft.h>
#include <unistd.h>
#include <ft_sh.h>

char	*search_cmd(char *exec_name)
{
	char	exists;
	char	*exec_path;

	exists = 0;

	exec_path = path_search(exec_name, &exists);
	if (exec_path)
		return (exec_path);
	ft_dprintf(2, "%s: %s: %s\n", "42sh", exists ? "permission denied" : "command not found", exec_name); // move to errors.c?
	return (NULL);
}

int		exec_cmd(t_tree *tree, int use_current_process)
{
	extern char	**environ;
	char		*path;
	int			return_status;
	pid_t		pid;

	expand(tree->data);
	if (tree->data->assign && !tree->data->argv)
		store_assignments(tree->data->assign);
	if (tree->data->redirects)
		init_redirects(tree->data->redirects);
	if (builtin(tree->data->argv, &return_status) == 0) // if we execute builtin, stop
		return (return_status);
	if (!use_current_process)
		if ((pid = fork()) == -1)
			return (1);
	if (use_current_process || pid == 0)
	{
		if ((path = search_cmd(tree->data->argv[0])) == NULL)
			_exit(127);
		execve(path, tree->data->argv, environ);
	}
	waitpid(pid, &return_status, 0);
	return (return_status);
}
