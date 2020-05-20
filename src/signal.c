/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 02:19:55 by gmoon             #+#    #+#             */
/*   Updated: 2020/05/20 11:14:22 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sigint_handle(void)
{
	ft_putstr_fd("\e[2D\e[0K", 1);
	ft_putendl_fd("", 1);
	print_commandline();
}

void		sigquit_handle(void)
{
	ft_putstr_fd("\e[2D\e[0K", 1);
}
