/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:06:33 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/16 16:34:01 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	p_eat_sleep(t_philosopher *philosopher)
{
	if (philosopher->is_dead)
		return (0);
	printf("\t%d\tis eating\n", philosopher->id);
	usleep(philosopher->t_eat);
	philosopher->n_eat += 1;
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_unlock(philosopher->rfork);
	if (philosopher->is_dead)
		return (0);
	printf("\t%d\tis sleeping\n", philosopher->id);
	usleep(philosopher->t_sleep);
	return (1);
}

int	take_fork(t_philosopher *philosopher, int select)
{
	if (select == 0)
	{
		pthread_mutex_lock(philosopher->lfork);
		if (philosopher->is_dead)
			return (0);
		printf("\t%d\thas taken a fork\n", philosopher->id);
		pthread_mutex_lock(philosopher->rfork);
		if (philosopher->is_dead)
			return (0);
		printf("\t%d\thas taken a fork\n", philosopher->id);
	}
	else
	{
		pthread_mutex_lock(philosopher->rfork);
		if (philosopher->is_dead)
			return (0);
		printf("\t%d\thas taken a fork\n", philosopher->id);
		pthread_mutex_lock(philosopher->lfork);
		if (philosopher->is_dead)
			return (0);
		printf("\t%d\thas taken a fork\n", philosopher->id);
	}
	return (1);
}

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
			break ;
		}
	}
	i = -1;
	while (is_true && ++i < size)
		philosophers[i]->is_dead = 1;
	return (is_true);
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
