/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:29:21 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 11:00:40 by lismarti         ###   ########.fr       */
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
		signal(SIGQUIT, SIG_DFL);
		exe->data->exit1 = error;
		error = exe1(exe, 1);
	}
	return (error);
}

void	init_env(char ***env, char **envp)
{
	*env = strdup_2d(envp);
	if (*env == NULL)
		exit(1);
}

void	handle_exit(char **env)
{
	printf("exit\n");
	rl_clear_history();
	cleanexit(env);
	exit(1);
}

void	shell_loop(char **env, char **argv, int check)
{
	char	*str;
	t_list	*exe;
	int		error;

	error = 0;
	
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		str = readline("minishell> ");
		if (!str)
			handle_exit(env);
		if (g_sig == 2)
			error = 130;
		g_sig = 0;
		check = check_line(&str, &env, error);
		if (check != 0)
		{
			if (check == 2)
				error = 2;
			continue ;
		}
		exe = create_list(str, &env, argv);
		error = execution(exe, error);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	if (argc != 1)
		return (1);
	init_env(&env, envp);
	shell_loop(env, argv, 0);
	return (0);
}
