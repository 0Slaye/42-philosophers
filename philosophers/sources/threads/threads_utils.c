/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:33:23 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/16 19:21:57 by uwywijas         ###   ########.fr       */
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
		master->philosophers[i]->ctime = time;
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
	master->stime = time;
	master->n_eat = philosophers[0]->n_eat;
	return (master);
}

long long	global_time(struct timeval stime, struct timeval etime)
{
	return ((etime.tv_sec * 1000 + etime.tv_usec / 1000) \
	- (stime.tv_sec * 1000 + stime.tv_usec / 1000));
}

void	ft_usleep(int v)
{
	struct timeval	current_time;
	long long		time;
	long long		end_time;

	gettimeofday(&current_time, NULL);
	end_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000 + v;
	time = 0;
	while (time < end_time)
	{
		gettimeofday(&current_time, NULL);
		time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	}
}
