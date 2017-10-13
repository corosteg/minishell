/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_funct2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corosteg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:04:00 by corosteg          #+#    #+#             */
/*   Updated: 2017/10/12 21:26:26 by corosteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_entry(char **command)
{
	int			ret;
	char		buf[2];

	ft_bzero(buf, 3);
	while ((ret = read(0, &buf, 1)) && ft_strcmp(buf, "\n"))
	{
		buf[ret] = '\0';
		if (buf[ret - 1] != '\t' && (buf[ret - 1] != ' ' || *command != NULL))
			*command = ft_strfreejoin(*command, buf, 1);
	}
	return (1);
}

void		exec_com(pid_t father, char **command2, t_env *list)
{
	char	**tab;

	tab = alloc_tab(list);
	father = fork();
	if (father > 0)
		father = wait(NULL);
	if (!(father))
		if (execve(command2[0], command2, tab) == -1)
		{
			ft_print("command not found: %s\n", command2[0]);
			exit(father);
		}
	if (tab)
		free(tab);
}

t_env		*check_null(char **command2, pid_t father, t_env *list)
{
	if (!(ft_strcmp(command2[0], "echo")))
	{
		ft_echo(command2, list);
		return (list);
	}
	else if (!(ft_strcmp(command2[0], "cd")))
		return (ft_cd_pars(command2, list, 0));
	else if (!(ft_strcmp(command2[0], "env")))
	{
		ft_env(command2, list);
		return (list);
	}
	else if (!(ft_strcmp(command2[0], "setenv")))
		return (ft_setenv(command2, list));
	else if (!(ft_strcmp(command2[0], "unsetenv")))
		return (ft_unsetenv(command2, list));
	else
		exec_com(father, command2, list);
	return (list);
}

int			check_bbin(char **command2)
{
	if (!(ft_strcmp(command2[0], "echo")))
		return (1);
	else if (!(ft_strcmp(command2[0], "cd")))
		return (1);
	else if (!(ft_strcmp(command2[0], "env")))
		return (1);
	else if (!(ft_strcmp(command2[0], "setenv")))
		return (1);
	else if (!(ft_strcmp(command2[0], "unsetenv")))
		return (1);
	else
		return (0);
}

t_env		*apply_bbin(char **command2, t_env *list)
{
	if (!(ft_strcmp(command2[0], "echo")))
		ft_echo(command2, list);
	else if (!(ft_strcmp(command2[0], "cd")))
		ft_cd_pars(command2, list, 1);
	else if (!(ft_strcmp(command2[0], "env")))
		ft_env(command2, list);
	else if (!(ft_strcmp(command2[0], "setenv")))
		list = ft_setenv(command2, list);
	else if (!(ft_strcmp(command2[0], "unsetenv")))
		list = ft_unsetenv(command2, list);
	else
	{
		free_list(list);
		return (0);
	}
	return (list);
}
