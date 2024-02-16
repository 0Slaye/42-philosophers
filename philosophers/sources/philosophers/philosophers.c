/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:12:18 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/16 16:33:47 by uwywijas         ###   ########.fr       */
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

t_philosopher	*new_philosopher(int id, char **argv, int argc)
{
	t_philosopher	*result;

	// TODO: check for argv before
	result = malloc(sizeof(t_philosopher));
	if (result == NULL)
		return (NULL);
	result->rfork = malloc(sizeof(pthread_mutex_t));
	if (result->rfork == NULL)
		return (free(result), NULL);
	result->id = id;
	result->t_die = ft_atoi(argv[2]) * 1000;
	result->t_eat = ft_atoi(argv[3]) * 1000;
	result->t_sleep = ft_atoi(argv[4]) * 1000;
	result->eaten = 0;
	result->is_dead = 0;
	result->l_eaten = 0;
	result->ctime = 0;
	result->n_eaten = 0;
	if (argc == 6)
		result->n_eat = ft_atoi(argv[5]);
	else
		result->n_eat = -1;
	return (result);
}

void	*p_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) arg;
	while (philosopher->is_dead == 0)
	{
		if (!take_fork(philosopher, philosopher->id % 2))
			break ;
		philosopher->eaten = 1;
		p_eat_sleep(philosopher);
		philosopher->l_eaten += philosopher->ctime;
		philosopher->eaten = 0;
		philosopher->n_eaten += 1;
		if (philosopher->is_dead)
			break ;
		//printf("\t%d\tis thinking\n", philosopher->id);
	}
	return (NULL);
}

void	philosophers(int argc, char **argv)
{
	t_philosopher	**philosophers;
	int				number;
	int				i;

	i = -1;
	number = ft_atoi(argv[1]);
	if (number <= 0)
		return ((void) NULL);
	philosophers = malloc(sizeof(t_philosopher **) * number);
	if (philosophers == NULL)
		return ((void) NULL);
	while (++i < number)
	{
		philosophers[i] = new_philosopher(i + 1, argv, argc);
		if (philosophers[i] == NULL)
			return (philosopher_free(philosophers, i), (void) NULL);
	}
	if (philosophers_setup(philosophers, number) != 0)
		return (free(philosophers), ft_putstr_fd("mutex: error.\n", 2));
	pthreading(philosophers, number + 1, &p_routine);
}
