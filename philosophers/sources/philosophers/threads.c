/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:31:13 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/15 15:47:02 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	*m_routine(void *arg)
{
	t_master	*master;
	master = arg;
	printf("Master enabled, starting simulation at : %d\n", master->init_time);
	return (NULL);
}

pthread_t	*pcreator(t_philosopher **philosophers, int size, void *p_routine)
{
	pthread_t		*threads;
	struct timeval	init_time;
	t_master		master;
	int				i;

	gettimeofday(&init_time, NULL);
	master.philosophers = philosophers;
	master.size = size - 1;
	master.init_time = init_time.tv_usec;
	threads = malloc(sizeof(pthread_t) * size);
	if (threads == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		if (i == 0 && pthread_create(&threads[i], NULL, m_routine, &master) != 0)
			return (free(threads), philosopher_free(philosophers, size - 1), NULL);
		if (i != 0 && pthread_create(&threads[i], NULL, p_routine, philosophers[i - 1]) != 0)
			return (free(threads), philosopher_free(philosophers, size - 1), NULL);
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
