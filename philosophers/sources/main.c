/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:07:44 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 15:08:35 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	check_arg(int argc, char **argv)
{
	if (ft_atol(argv[1]) <= 0)
		return (0);
	else if (ft_atol(argv[2]) <= 0)
		return (0);
	else if (ft_atol(argv[3]) <= 0)
		return (0);
	else if (ft_atol(argv[4]) <= 0)
		return (0);
	if (argc == 6)
	{
		if (ft_atol(argv[5]) <= 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_error("error: args\n"), 0);
	if (!check_arg(argc, argv))
		return (ft_error("error: args\n"), 0);
	philosophers(argc, argv);
	return (0);
}
