/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corosteg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:37:25 by corosteg          #+#    #+#             */
/*   Updated: 2017/10/12 21:56:39 by corosteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*copy_env(char **env, t_env *list)
{
	t_env		*tmp;
	int			i;

	i = 1;
	list = (t_env*)malloc(sizeof(t_env));
	list->var = ft_strdup(env[0]);
	list->next = NULL;
	tmp = list;
	while (env[i])
	{
		tmp->next = (t_env*)malloc(sizeof(t_env));
		tmp = tmp->next;
		tmp->var = ft_strdup(env[i]);
		tmp->next = NULL;
		i++;
	}
	return (list);
}

char		**alloc_tab(t_env *list)
{
	int			i;
	t_env		*tmp;
	char		**tab;

	if (list == NULL)
		return (NULL);
	i = 0;
	tmp = list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (i + 1))))
		return (0);
	tab[i] = NULL;
	i = 0;
	while (list)
	{
		tab[i] = ft_strdup(list->var);
		i++;
		list = list->next;
	}
	return (tab);
}

void		core2(t_env *list, pid_t father, char **command2, t_env *e_path)
{
	char	**tab;
	char	*c_path;

	c_path = NULL;
	tab = alloc_tab(list);
	c_path = check_sbin(command2[0], e_path);
	father = fork();
	if (father > 0)
		father = wait(NULL);
	if (!(father))
		if (execve(c_path, command2, tab) == -1)
		{
			ft_print("command not found: %s\n", command2[0]);
			exit(father);
		}
	free_str(tab);
	free(c_path);
}

t_env		*core(char **command2, t_env *list)
{
	pid_t	father;
	t_env	*e_path;

	e_path = NULL;
	father = 0;
	e_path = check_e_path(list);
	if (e_path == NULL)
		return (check_null(command2, father, list));
	if (check_bbin(command2))
		list = apply_bbin(command2, list);
	else
		core2(list, father, command2, e_path);
	free_list(e_path);
	return (list);
}

int			main(int ac, char **av, char **environnement)
{
	char	*command;
	char	**command2;
	char	*path;
	t_env	*list;

	if (environnement == NULL || environnement[0] == NULL)
	{
		ft_print("Error: Start \"minishell\" with valid environnement\n");
		return (0);
	}
	command = ft_strdup("\0");
	command2 = NULL;
	list = NULL;
	av = NULL;
	list = copy_env(environnement, list);
	ft_print(""GRAS""CYAN"---------- MINISHELL ----------\n"STOP"");
	while (1)
	{
		ft_print(""GRAS""VERT"=> "RED"%s "STOP"", (path = get_name()));
		free(path);
		if (check_entry(&command) && command[0] != '\0' && check_str(command))
			main2(command2, &command, list);
	}
	return (ac);
}
