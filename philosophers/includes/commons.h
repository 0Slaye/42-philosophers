/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:07:00 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/16 18:07:07 by uwywijas         ###   ########.fr       */
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
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_eaten;
	int				eaten;
	long long		l_eaten;
	int				is_dead;
	int				ctime;
	int				n_eat;
	int				n_eaten;
}	t_philosopher;

typedef struct s_master
{
	t_philosopher	**philosophers;
	long long		stime;
	int				size;
	int				t_die;
	int				n_eat;
}	t_master;

void		philosophers(int argc, char **argv);
void		philosopher_free(t_philosopher **philosophers, int size);
int			is_pdead(t_philosopher **philosophers, int size, int time);
int			take_fork(t_philosopher *philosopher, int select);
int			p_eat_sleep(t_philosopher *philosopher);

void		pthreading(t_philosopher **philosophers, int size, void *p_routine);
long long	global_time(struct timeval time1, struct timeval time2);
t_master	*master_setup(t_philosopher **philosophers, int size);
void		update_death(t_master *master, long long time);
void		setup_leaten(t_master *master, long long time);

void		ft_usleep(int value);
void		ft_putstr_fd(char *str, int fd);
long		ft_atol(const char *str);
int			check_arg(char **argv, int argc);

#endif