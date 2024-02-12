/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:12:18 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/12 19:03:00 by uwywijas         ###   ########.fr       */
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
	result->rfork = malloc(sizeof(pthread_mutex_t));
	if (result == NULL)
		return (NULL);
	result->id = id;
	holder = ft_atoi(argv[2]);
	if (holder < 0)
		return (NULL);
	result->die = holder;
	holder = ft_atoi(argv[3]);
	if (holder < 0)
		return (NULL);
	result->eat = holder;
	holder = ft_atoi(argv[4]);
	if (holder < 0)
		return (NULL);
	result->sleep = holder;
	return (result);
}

void	*routine(void *arg)
{
	t_philosopher	*philosopher;
	philosopher = (t_philosopher *) arg;
	pthread_mutex_lock(philosopher->lfork);
	printf("%d has taken a fork\n", philosopher->id);
	pthread_mutex_lock(philosopher->rfork);
	printf("%d has taken a fork\n", philosopher->id);
	printf("%d is eating\n", philosopher->id);
	usleep(philosopher->eat * 1000);
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_unlock(philosopher->rfork);
	printf("%d is sleeping\n", philosopher->id);
	usleep(philosopher->sleep * 1000);
	printf("%d is thinking\n", philosopher->id);
	return (NULL);
}

void	threading(t_philosopher **philosophers, int number)
{
	pthread_t	*threads;
	int			i;

	i = -1;
	threads = malloc(sizeof(pthread_t) * number);
	if (threads == NULL)
		return ((void) NULL);
	while (++i < number)
	{
		if (pthread_create(&threads[i], NULL, &routine, philosophers[i]) != 0)
			return (free(philosophers), ft_putstr_fd("pthread: error.\n", 2));
	}
	i = -1;
	while (++i < number)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (free(philosophers), ft_putstr_fd("pthread: error.\n", 2));
	}
	free(threads);
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
			return (free(philosophers), (void) NULL);
	}
	if (philosophers_setup(philosophers, number) != 0)
		return (free(philosophers), ft_putstr_fd("mutex: error.\n", 2));
	threading(philosophers, number);
	free(philosophers);
}
