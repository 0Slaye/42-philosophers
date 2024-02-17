/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:30:16 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/17 17:22:11 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	philosophers(int argc, char **argv)
{
	t_philosopher	**philosophers;
	int				i;

	(void) argc;
	i = -1;
	philosophers = malloc(sizeof(t_philosopher **) * (ft_atol(argv[1]) + 1));
	if (philosophers == NULL)
		return ((void) NULL);
	while (++i < ft_atol(argv[1]))
	{
		philosophers[i] = create_philosopher(i + 1, argv);
		if (philosophers[i] == NULL)
			return (free_philosophers(philosophers, i), (void) NULL);
	}
	philosophers[ft_atol(argv[1])] = NULL;
	if (f_add_forks(philosophers) != 0)
		return (ft_error("mutex: error\n"));
	start_threads(philosophers);
	free_philosophers(philosophers, i);
}
