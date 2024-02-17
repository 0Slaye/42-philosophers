/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:46:01 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/17 17:04:42 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	init_master(t_master *master, t_philosopher **philosophers)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	master->philosophers = philosophers;
	master->start_time = start_time;
}

int	master_thread(pthread_t *threads, int size, t_master *master)
{
	if (pthread_create(&threads[size], NULL, mroutine, master) != 0)
		return (-1);
	return (0);
}
