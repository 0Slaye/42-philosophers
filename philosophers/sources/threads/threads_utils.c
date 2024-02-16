/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:33:23 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/16 15:41:44 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	setup_leaten(t_master *master, long long time)
{
	int	i;

	i = -1;
	while (++i < master->size)
		master->philosophers[i]->l_eaten = time;
}

void	update_death(t_master *master, long long time)
{
	int	i;

	i = -1;
	while (++i < master->size)
	{
		if (master->philosophers[i]->eaten == 0)
		{
			if (time >= master->philosophers[i]->l_eaten + master->t_die)
			{
				master->philosophers[i]->is_dead = 1;
				return ((void) NULL);
			}
		}
	}
}

t_master	*master_setup(t_philosopher **philosophers, int size)
{
	t_master		*master;
	struct timeval	time;

	gettimeofday(&time, NULL);
	master = malloc(sizeof(t_master));
	if (master == NULL)
		return (NULL);
	master->philosophers = philosophers;
	master->size = size - 1;
	master->t_die = philosophers[0]->t_die / 1000;
	master->stime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (master);
}

long long	global_time(struct timeval stime, struct timeval etime)
{
	return ((etime.tv_sec * 1000 + etime.tv_usec / 1000) - (stime.tv_sec * 1000 + stime.tv_usec / 1000));
}

void	ft_usleep(int value)
{
	struct timeval	current_time;
	int				end_time;

	gettimeofday(&current_time, NULL);
	end_time = current_time.tv_usec + value;
	while (current_time.tv_usec < end_time)
		gettimeofday(&current_time, NULL);
}
