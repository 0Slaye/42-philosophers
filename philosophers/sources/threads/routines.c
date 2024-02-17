/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:23:06 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/17 18:17:06 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	*mroutine(void *arg)
{
	t_master		*master;
	struct timeval 	pdated_time;
	long long		time;
	int				is_done;
	int				i;

	master = arg;
	is_done = 0;
	time = 0;
	while (!is_done)
	{
		i = -1;
		while (master->philosophers[++i])
		{
			master->philosophers[i]->time = time;
			if (master->philosophers[i]->last_eat + master->philosophers[i]->time_die < time)
			{
				master->philosophers[i]->is_dead = 1;
				is_done = 1;
				break;
			}
		}
		gettimeofday(&pdated_time, NULL);
		time = (pdated_time.tv_sec * 1000 + pdated_time.tv_usec / 1000) - (master->start_time.tv_sec * 1000 + master->start_time.tv_usec / 1000);
	}
	set_finish(master->philosophers);
	return (NULL);
}

void	*proutine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = arg;
	while (!philosopher->is_dead && !philosopher->is_finish)
		;
	if (philosopher->is_dead)
		printf("%d\t%d\tdie\n", philosopher->time, philosopher->id);
	return (NULL);
}
