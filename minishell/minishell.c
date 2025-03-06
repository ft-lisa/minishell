/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:29:21 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/06 11:35:25 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_list *pip)
{
	long long	exit_val;
	int			exit_code;
	char		**cmd;

	cmd = ft_split_exe1(pip->cmd);
	if (!cmd[1])
	{
		free_pip(pip);
		rl_clear_history();
		exit(0);
	}
	exit_val = ft_atoll(cmd[1]);
	exit_code = (int)(exit_val % 256);
	if (exit_code < 0)
		exit_code += 256;
	rl_clear_history();
	free_pip(pip);
	exit(exit_code);
}

int	execution(t_list *exe, int error)
{
	if (exe)
	{
		signal(SIGINT, new);
		exe->data->exit1 = error;
		error = exe1(exe, 1);
	}
	return (error);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**env;
	t_list	*exe;
	int		error;

	if (argc != 1)
		return (1);
	env = strdup_2d(envp);
	error = 0;
	
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handler);
		str = readline("minishell> ");
		if (!str)
			(printf("exit\n"), rl_clear_history(), exit(1));
		add_history(str);
		if (g_sig)
			error = 130;
		g_sig = 0;
		if (check_line(&str, &env, error) == 1)
			continue ;
		exe = creat_list(str, &env, argv, argc);

		error = execution(exe, error);
	}
}
