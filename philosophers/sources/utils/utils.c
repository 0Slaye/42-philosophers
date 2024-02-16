/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:01:00 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/16 18:08:16 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	check_arg(char **argv, int argc)
{
	printf("%ld\n", ft_atol(argv[1]));
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
