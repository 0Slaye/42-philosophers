/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:06:33 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/13 17:23:25 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	ft_usleep(int value)
{
	struct timeval	current_time;
	int				end_time;

	gettimeofday(&current_time, NULL);
	end_time = current_time.tv_usec + value;
	while (current_time.tv_usec < end_time)
		gettimeofday(&current_time, NULL);
}

void	philosopher_free(t_philosopher **philosophers, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		free(philosophers[i]->rfork);
		free(philosophers[i]);
	}
	free(philosophers);
}
