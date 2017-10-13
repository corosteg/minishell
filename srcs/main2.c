/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corosteg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 20:51:29 by corosteg          #+#    #+#             */
/*   Updated: 2017/10/12 21:06:58 by corosteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_name(void)
{
	char	path[1025];
	int		i;

	i = 0;
	getcwd(path, 1024);
	i = ft_strlen(path);
	while (i > 0 && path[i] != '/')
		i--;
	return (ft_strdup(&path[i + 1]));
}

t_env		*main2(char **command2, char **command, t_env *list)
{
	command2 = ft_strsplit(*command, ' ');
	free(*command);
	if (!(ft_strcmp(command2[0], "exit")))
		ft_exit(command2, list);
	list = core(command2, list);
	free_str(command2);
	*command = ft_strdup("\0");
	return (list);
}
