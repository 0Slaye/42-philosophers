/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:31:13 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/16 16:05:08 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	*mroutine(void *arg)
{
	t_master		*master;
	struct timeval	start_time;
	struct timeval	end_time;
	long long		time;

	master = arg;
	time = master->stime;
	setup_leaten(master, time);
	gettimeofday(&end_time, NULL);
	while (!is_pdead(master->philosophers, master->size, time - master->stime))
	{
		gettimeofday(&start_time, NULL);
		usleep(1000);
		update_death(master, time);
		gettimeofday(&end_time, NULL);
		time += global_time(start_time, end_time);
	}
	free(master);
	return (NULL);
}

pthread_t	*pcreator(t_philosopher **philosophers, int size, void *proutine)
{
	pthread_t		*threads;
	t_master		*master;
	int				i;

	master = master_setup(philosophers, size);
	if (master == NULL)
		return (ft_putstr_fd("malloc: error.\n", 2), NULL);
	threads = malloc(sizeof(pthread_t) * size);
	if (threads == NULL)
		return (ft_putstr_fd("malloc: error.\n", 2), free(master), NULL);
	i = -1;
	while (++i < size)
	{
		if (i == 0 && pthread_create(&threads[i], NULL, mroutine, master) != 0)
			return (free(master), free(threads), \
		philosopher_free(philosophers, size - 1), NULL);
		if (i != 0 && pthread_create(&threads[i], NULL, proutine, philosophers[i - 1]) != 0)
			return (free(master), free(threads), \
		philosopher_free(philosophers, size - 1), NULL);
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
