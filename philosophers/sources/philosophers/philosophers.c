/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:12:18 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/15 16:51:31 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	philosophers_setup(t_philosopher	**philosophers, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_init(philosophers[i]->rfork, NULL) != 0)
			return (-1);
		if (i != size - 1)
			philosophers[i + 1]->lfork = philosophers[i]->rfork;
		else
			philosophers[0]->lfork = philosophers[i]->rfork;
	}
	return (0);
}

t_philosopher	*new_philosopher(int id, char **argv)
{
	t_philosopher	*result;
	int				holder;

	result = malloc(sizeof(t_philosopher));
	if (result == NULL)
		return (NULL);
	result->rfork = malloc(sizeof(pthread_mutex_t));
	if (result->rfork == NULL)
		return (free(result), NULL);
	result->id = id;
	holder = ft_atoi(argv[2]);
	if (holder < 0)
		return (free(result->rfork), free(result), NULL);
	result->t_die = holder * 1000;
	holder = ft_atoi(argv[3]);
	if (holder < 0)
		return (free(result->rfork), free(result), NULL);
	result->t_eat = holder * 1000;
	holder = ft_atoi(argv[4]);
	if (holder < 0)
		return (free(result->rfork), free(result), NULL);
	result->t_sleep = holder * 1000;
	result->eaten = 0;
	result->is_dead = 0;
	return (result);
}

void	*p_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) arg;
	while (philosopher->is_dead == 0)
		continue ;
	return (NULL);
}

void	philosophers(int argc, char **argv)
{
	t_philosopher	**philosophers;
	int				number;
	int				i;

	(void) argc;
	i = -1;
	number = ft_atoi(argv[1]);
	if (number <= 0)
		return ((void) NULL);
	philosophers = malloc(sizeof(t_philosopher **) * number);
	if (philosophers == NULL)
		return ((void) NULL);
	while (++i < number)
	{
		philosophers[i] = new_philosopher(i + 1, argv);
		if (philosophers[i] == NULL)
			return (philosopher_free(philosophers, i), (void) NULL);
	}
	if (philosophers_setup(philosophers, number) != 0)
		return (free(philosophers), ft_putstr_fd("mutex: error.\n", 2));
	pthreading(philosophers, number + 1, &p_routine);
}
