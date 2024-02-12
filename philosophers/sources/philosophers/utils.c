/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:06:33 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/12 16:17:09 by uwywijas         ###   ########.fr       */
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
