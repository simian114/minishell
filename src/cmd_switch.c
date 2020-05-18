/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 22:44:14 by gmoon             #+#    #+#             */
/*   Updated: 2020/05/19 05:43:24 by gmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_switch(char **cmd, t_list *envs)
{
	int ret;

	ret = 1;
	if (is_same(*cmd, "exit"))
		exit(0);
	else if (is_same(*cmd, "cd"))
		sh_cd(cmd, envs);
	else if (is_same(*cmd, "export") && *(cmd + 1))
		sh_export(cmd + 1, envs);
	else if (is_same(*cmd, "unset"))
		sh_unset(cmd + 1, envs);
	else
		ret = 0;
	return (ret);
}

void	fork_cmd_switch(char **cmd, t_list *envs, char **envp, int fd)
{
	if (is_same(*cmd, "echo"))
		sh_echo(cmd + 1, fd);
	else if (is_same(*cmd, "pwd"))
		sh_pwd(fd);
	else if (is_same(*cmd, "env"))
		sh_env(envs, fd);
	else if (is_same(*cmd, "export"))
		sh_env(envs, fd);
	else if (is_same(*cmd, "ls"))
		sh_ls(fd);
	else if (is_same(*cmd, "clear"))
		sh_clear(fd);
	else if (ft_strncmp(*cmd, "./", 2) == 0)
		sh_exec(cmd, envp);
	else
	{
		ft_putstr_fd("moong_shell: command not found: ", 1);
		ft_putendl_fd(cmd[0], 1);
		exit(1);
	}
}
