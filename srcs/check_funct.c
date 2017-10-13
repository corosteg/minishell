/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corosteg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 18:54:19 by corosteg          #+#    #+#             */
/*   Updated: 2017/10/11 21:16:38 by corosteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*create_e_path(char *str)
{
	char	**tab;
	t_env	*list;
	t_env	*retu;
	int		i;

	i = 0;
	tab = ft_strsplit(str, ':');
	list = (t_env*)malloc(sizeof(t_env));
	retu = list;
	retu->var = ft_strdup(tab[0]);
	retu->next = NULL;
	while (tab[i])
	{
		list->next = (t_env*)malloc(sizeof(t_env));
		list = list->next;
		list->var = ft_strdup(tab[i]);
		list->next = NULL;
		i++;
	}
	free(str);
	free_str(tab);
	return (retu);
}

t_env		*check_e_path(t_env *list)
{
	t_env	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	while (tmp)
	{
		if ((!(ft_strncmp(tmp->var, "PATH=", 4))) && tmp->var[5] != '\0')
			return (create_e_path(ft_strdup(&tmp->var[5])));
		tmp = tmp->next;
	}
	return (NULL);
}

int			check_ft_envfunct_action(char **command2, t_env *list, int a)
{
	a = 0;
	if (!(ft_strncmp(command2[1], list->var, (ft_strclen(list->var, '=') + 1)))
			&& command2[2] != NULL)
		return (1);
	if (!(ft_strncmp(command2[1], list->var, (ft_strclen(list->var, '=') + 1)))
			&& command2[2] == NULL)
		return (2);
	return (0);
}

char		*check_sbin(char *co, t_env *e_path)
{
	DIR				*rep;
	char			*tmp;
	t_env			*tpm;
	struct dirent	*ent;

	tpm = e_path;
	if (tpm)
		while (tpm)
		{
			if ((rep = opendir(tpm->var)))
			{
				while ((ent = readdir(rep)))
				{
					if (!(ft_strcmp(ent->d_name, co)))
					{
						closedir(rep);
						tmp = ft_strfreejoin(tpm->var, "/", 0);
						return (co = ft_strfreejoin(tmp, co, 1));
					}
				}
				closedir(rep);
			}
			tpm = tpm->next;
		}
	return (ft_strdup(co));
}

int			check_str(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (1);
}
