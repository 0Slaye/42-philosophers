/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:31:13 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/15 19:21:06 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	is_pdead(t_philosopher **philosophers, int size, int time)
{
	int	is_true;
	int	i;

	is_true = 0;
	i = -1;
	while (++i < size)
	{
		if (philosophers[i]->is_dead == 1)
		{
			is_true = 1;
			printf("%d\t%d\tdied\n", time, philosophers[i]->id);
			break;
		}
	}
	i = -1;
	while (is_true && ++i < size)
		philosophers[i]->is_dead = 1;
	return (is_true);
}

void	*m_routine(void *arg)
{
	struct timeval	start_time;
	struct timeval	end_time;
	t_master		*master;
	long long		updated_time;
	int				i;

	master = arg;
	updated_time = master->init_time;
	while (!is_pdead(master->philosophers, master->size, updated_time / 1000))
	{
		i = -1;
		gettimeofday(&start_time, NULL);
		printf("%lld\n", updated_time);
		while (++i < master->size)
		{
			if (master->philosophers[i]->eaten == 1)
			{
				if (updated_time >= master->t_die)
				{
					master->philosophers[i]->is_dead = 1;
					break;
				}
			}
		}
		gettimeofday(&end_time, NULL);
		updated_time += (end_time.tv_sec * 1000 + end_time.tv_usec / 1000) - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	}
	return (NULL);
}

pthread_t	*pcreator(t_philosopher **philosophers, int size, void *p_routine)
{
	struct timeval	t_time;
	pthread_t		*threads;
	t_master		*master;
	int				i;

	gettimeofday(&t_time, NULL);
	master = malloc(sizeof(t_master));
	if (master == NULL)
		return (NULL);
	master->philosophers = philosophers;
	master->size = size - 1;
	master->t_die = philosophers[0]->t_die;
	master->init_time = (t_time.tv_sec * 1000) + (t_time.tv_usec / 1000);
	threads = malloc(sizeof(pthread_t) * size);
	if (threads == NULL)
		return (free(master), NULL);
	i = -1;
	while (++i < size)
	{
		if (i == 0 && pthread_create(&threads[i], NULL, m_routine, master) != 0)
			return (free(master), free(threads), philosopher_free(philosophers, size - 1), NULL);
		if (i != 0 && pthread_create(&threads[i], NULL, p_routine, philosophers[i - 1]) != 0)
			return (free(master), free(threads), philosopher_free(philosophers, size - 1), NULL);
	}
	return (threads);
}

int	pjoiner(pthread_t *threads, t_philosopher **philosophers, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (philosopher_free(philosophers, size - 1), -1);
	}
	return (0);
}

void	pthreading(t_philosopher **philosophers, int size, void *p_routine)
{
	pthread_t	*threads;

	threads = pcreator(philosophers, size, p_routine);
	if (threads == NULL)
		return (ft_putstr_fd("pthread: error.\n", 2));
	if (pjoiner(threads, philosophers, size) != 0)
		return (ft_putstr_fd("pthread: error.\n", 2));
	philosopher_free(philosophers, size - 1);
	free(threads);
}
