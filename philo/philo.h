/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:05:40 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 20:28:36 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# include <errno.h>

typedef struct philo_info
{
	int					id;
	int					meals_count;
	int					inf_loop;
	long				last_meal_taken;
	struct philo_info	*next;
	struct philo_arg	*p;
}						t_philo_info;

typedef struct philo_arg
{
	int						philo_len;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	int						eat_cap;
	int						is_dead;
	int						full;
	int						finish;

	long					start_date;
	pthread_t				*philo_threads;
	pthread_t				thread_detached_dead;
	pthread_t				thread_detached_end;
	pthread_mutex_t			*chop_sticks;
	pthread_mutex_t			write_p;
	pthread_mutex_t			monitor_t;

}							t_philo;

//philo.c
long	current_time_in_ms(void);
void	print_timestamp(int philo_id, int i, t_philo *philo);
int		custom_sleep(long milliseconds);

//ft_atoi.c
int		ft_isdigit(int c);
long	ft_atoi(const char *str);

//struct_utils.c
int		push(t_philo *philo, t_philo_info **map);

//init.c
void	init_chop_sticks(t_philo *philo);
int		init_philos_data(t_philo_info **head, t_philo *philo);
void	init_philos_threads(t_philo *philo, t_philo_info *head);

//simulation.c
void	*dining_simulation(void *ph);

//detached_thread.c
void	create_detached_threads(t_philo *philo, t_philo_info *head);

//parsing.c
int		check_input(int argc, char **argv, t_philo *philo);

#endif