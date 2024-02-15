/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:07:00 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/15 15:44:17 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H
# define COMMONS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	int				id;
	int				die;
	int				eat;
	int				sleep;
	int				eaten;
	int				is_dead;
}	t_philosopher;

typedef struct s_master
{
	t_philosopher **philosophers;
	int				size;
	int				init_time;
}	t_master;

void	philosophers(int argc, char **argv);
void	philosopher_free(t_philosopher **philosophers, int size);

void	pthreading(t_philosopher **philosophers, int size, void *p_routine);

void	ft_usleep(int value);
void	ft_putstr_fd(char *str, int fd);
int		ft_atoi(const char *str);

#endif