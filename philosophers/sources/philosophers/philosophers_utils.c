/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:06:33 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/16 15:33:11 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

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
