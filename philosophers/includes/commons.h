/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:07:00 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/09 17:17:57 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H
# define COMMONS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int	id;
	int	die;
	int	eat;
	int	sleep;
	int	eaten;
}	t_philosopher;

void	philosophers(int argc, char **argv);
void	show_philosophers(t_philosopher *philosophers, int size);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);

#endif