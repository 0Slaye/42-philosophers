/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:06:33 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/13 16:06:09 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

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
