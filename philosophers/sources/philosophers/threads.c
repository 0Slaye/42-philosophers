/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:31:13 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/13 16:39:42 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	pthreading(t_philosopher **philosophers, int size, void *p_routine)
{
	pthread_t	*threads;
	int			i;

	i = -1;
	threads = malloc(sizeof(pthread_t) * size);
	if (threads == NULL)
		return ((void) NULL);
	while (++i < size)
	{
		if (pthread_create(&threads[i], NULL, p_routine, philosophers[i]) != 0)
			return (philosopher_free(philosophers, size), ft_putstr_fd("pthread: error.\n", 2));
	}
	i = -1;
	while (++i < size)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (philosopher_free(philosophers, size), ft_putstr_fd("pthread: error.\n", 2));
	}
	philosopher_free(philosophers, size);
	free(threads);
}
