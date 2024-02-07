/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:07:44 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/07 17:31:42 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	philosophers(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	return ;
}

int main(int argc, char **argv)
{
	if (argc < 5)
		return (0);
	philosophers(argc, argv);
	return (0);
}
