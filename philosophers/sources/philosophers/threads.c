/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:31:13 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/15 15:30:52 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

pthread_t	*pcreator(t_philosopher **philosophers, int size, void *p_routine)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * size);
	if (threads == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		if (pthread_create(&threads[i], NULL, p_routine, philosophers[i]) != 0)
			return (free(threads), philosopher_free(philosophers, size), NULL);
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
			return (philosopher_free(philosophers, size), -1);
	}
	return (0);
}

void	mthreading(t_philosopher **philosophers, int size)
{
	(void) philosophers;
	(void) size;
	return ;
}

void	pthreading(t_philosopher **philosophers, int size, void *p_routine)
{
	pthread_t	*threads;

	threads = pcreator(philosophers, size, p_routine);
	if (threads == NULL)
		return (ft_putstr_fd("pthread: error.\n", 2));
	if (pjoiner(threads, philosophers, size) != 0)
		return (ft_putstr_fd("pthread: error.\n", 2));
	philosopher_free(philosophers, size);
	free(threads);
}
