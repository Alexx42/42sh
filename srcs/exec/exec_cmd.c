/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 06:14:19 by tkobb             #+#    #+#             */
/*   Updated: 2018/12/03 18:17:38 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

char		*search_cmd(char *exec_name)
{
	char	exists;
	char	*exec_path;

	exists = 0;
	exec_path = path_search(exec_name, &exists);
	if (exec_path)
		return (exec_path);
	ft_dprintf(2, "%s: %s: %s\n", "42sh", exists ?
		"permission denied" : "command not found", exec_name);
	return (NULL);
}

static int	fork_and_exec(t_tree *tree, int use_current_process, char *path)
{
	pid_t		pid;
	extern char	**environ;
	int			return_status;

	if (!use_current_process)
		if ((pid = fork()) == -1)
			return (error("fork"));
	if (use_current_process || pid == 0)
	{
		if (tree->data->redirects && init_redirects(tree->data->redirects))
			return (1);
		execve(path, tree->data->argv, environ);
		return (error("execve"));
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &return_status, 0);
	signal(SIGINT, SIG_DFL);
	free(path);
	return (return_status);
}

int			exec_cmd(t_tree *tree, int use_current_process)
{
	char		*path;
	int			return_status;

	if (tree->data->assign && !tree->data->argv)
		store_assignments(tree->data->assign);
	if (!tree->data->argv)
		return (0);
	if (builtin(tree->data, &return_status) == 0)
		return (return_status);
	if ((path = search_cmd(tree->data->argv[0])) == NULL)
		return (127);
	return (fork_and_exec(tree, use_current_process, path));
}
