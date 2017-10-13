/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corosteg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:45:45 by corosteg          #+#    #+#             */
/*   Updated: 2017/10/12 21:25:36 by corosteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <dirent.h>
# define STOP		"\033[0m"
# define VERT		"\033[32m"
# define CYAN		"\033[36m"
# define RED		"\033[31m"
# define GRAS		"\033[1m"

typedef struct		s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

int					env_cmp(char *arg, t_env *env);
t_env				*copy_list(t_env *list, t_env *list2);
int					check_bbin(char **command2);
char				*check_sbin(char *co, t_env *e_path);
int					ft_echo(char **command, t_env *list);
t_env				*ft_cd_pars(char **command2, t_env *env, int i);
int					ft_env(char **command2, t_env *list);
void				ft_exit(char **command2, t_env *list);
t_env				*ft_setenv(char **command2, t_env *list);
t_env				*ft_unsetenv(char **command2, t_env *list);
t_env				*copy_env(char **env, t_env *list);
t_env				*check_e_path(t_env *list);
int					check_entry(char **command);
t_env				*core(char **command2, t_env *list);
int					check_ft_envfunct_action
						(char **command2, t_env *list, int a);
int					ft_strclen(char *str, char c);
t_env				*remv_var(t_env *rmv, t_env *list);
void				free_str(char **array);
void				free_e_path(t_env *list);
void				free_list(t_env *list);
t_env				*apply_bbin(char **command2, t_env *list);
t_env				*check_null(char **command2, pid_t father, t_env *list);
int					check_str(char *str);
t_env				*set_env(char *path, t_env *env, char *arg, int p);
char				*findhome(t_env *env);
char				*findoldpwd(t_env *env);
t_env				*main2(char **command2, char **command, t_env *list);
char				*get_name(void);
int					ft_get_arg(char **command2);
char				**alloc_tab(t_env *list);

#endif
