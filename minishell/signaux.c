/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:43:27 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/05 14:50:05 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig = 0;

void	handler(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = signal;
}

void	new(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	g_sig = signal;
	return ;
}

void	her(int signal)
{
	write(1, "\n", 1);
	close(0);
	g_sig = signal;
	return ;
}

void	parent_her(int signal)
{
	g_sig = signal;
	return ;
}

void	parent_quit(int signal)
{
	write(1, "Quit (core dumped)\n", 20);
	rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
}
