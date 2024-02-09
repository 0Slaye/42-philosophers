/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:12:18 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/09 17:28:33 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	show_philosophers(t_philosopher *philosophers, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		printf("~~~~~ [%d] ~~~~~\n", philosophers[i].id);
		printf("Die : %d\n", philosophers[i].die);
		printf("Eat : %d\n", philosophers[i].eat);
		printf("Sleep : %d\n", philosophers[i].sleep);
		printf("~~~~~~~~~~~~~~~~\n");
	}
}

t_philosopher	new_philosopher(int id, char **argv)
{
	t_philosopher	result;
	int				holder;

	result.id = id;
	holder = ft_atoi(argv[2]);
	if (holder < 0)
		return (result.id = -1, result);
	result.die = holder;
	holder = ft_atoi(argv[3]);
	if (holder < 0)
		return (result.id = -1, result);
	result.eat = holder;
	holder = ft_atoi(argv[4]);
	if (holder < 0)
		return (result.id = -1, result);
	result.sleep = holder;
	return (result);
}

void	*routine(void *arg)
{
	(void) arg;
	printf("Working\n");
	return (NULL);
}

void	threading(t_philosopher *philosophers, int number)
{
	pthread_t	*threads;
	int			i;

	i = -1;
	threads = malloc(sizeof(pthread_t) * number);
	if (threads == NULL)
		return ((void) NULL);
	while (++i < number)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) == -1)
			return (free(philosophers), ft_putstr_fd("pthread: error.\n", 2));
	}
	i = -1;
	while (++i < number)
	{
		if (pthread_join(threads[i], NULL) == -1)
			return (free(philosophers), ft_putstr_fd("pthread: error.\n", 2));
	}
}

void	philosophers(int argc, char **argv)
{
	t_philosopher	*philosophers;
	int				number;
	int				i;

	(void) argc;
	i = -1;
	number = ft_atoi(argv[1]);
	if (number <= 0)
		return ((void) NULL);
	philosophers = malloc(sizeof(t_philosopher) * number);
	if (philosophers == NULL)
		return ((void) NULL);
	while (++i < number)
	{
		philosophers[i] = new_philosopher(i + 1, argv);
		if (philosophers[i].id == -1)
			return (free(philosophers), (void) NULL);
	}
	threading(philosophers, number);
	free(philosophers);
}
