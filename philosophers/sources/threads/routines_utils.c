/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:30:49 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 11:44:09 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	solver(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
		usleep(5 * 1000);
	pthread_mutex_lock(philosopher->lfork);
	secure_print(philosopher, "has taken a fork\n");
	pthread_mutex_lock(philosopher->rfork);
	secure_print(philosopher, "has taken a fork\n");
}

void	secure_print(t_philosopher *philosopher, char *str)
{
	if (!philosopher->is_finish && !philosopher->is_dead)
		printf("%d\t%d\t%s", philosopher->time, philosopher->id, str);
}
