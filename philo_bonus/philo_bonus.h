/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:30:00 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/10 16:46:49 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>
# include <signal.h>

typedef struct philo_info
{
	int					id;
	int					meals_count;
	long				last_meal_taken;
	pthread_t			detached_thread_dead;
	sem_t				*monitor_t;
	char				*sem_name;
	struct philo_info	*next;
	struct philo_arg	*p;
}	t_philo_info;

typedef struct philo_arg
{
	int						philo_len;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						eat_cap;
	int						finish;

	pthread_t				detached_thread_dead;
	long					start_date;
	pid_t					*pids;
	sem_t					*write_p;
	sem_t					*forks;
}	t_philo_bonus;

long	current_time_in_ms(void);

//philo_bonus.c
void	print_state_infos(int ph_id, int i, t_philo_info *current);
int		custom_sleep(long milliseconds);
void	free_all(t_philo_bonus *args, t_philo_info *head);

//detached_thread.c
void	create_detached_threads(t_philo_info *current_philo);

//ft_atoi.c
int		ft_isdigit(int c);
long	ft_atoi(const char *str);

//init.c
void	init_philos_processes(t_philo_bonus *args, t_philo_info *head);
void	init_philos_data(t_philo_info **head, t_philo_bonus *args);
void	init_chop_stciks_and_write_semap(t_philo_bonus	*arg, t_philo_info *h);

//parsing.c
int		check_input(int argc, char **argv, t_philo_bonus *philo);

//simulation.c
void	simulate_dining(t_philo_info *current_philo);
void	unlink_and_close_semaphores(t_philo_bonus *args, t_philo_info *head);

//struct_utils.c
void	push(t_philo_bonus *philo, t_philo_info **map);

//
char	*merge_two_string(char *str1, char *str2);
int		str_len(char *str);
char	*ft_itoi(int nbr);

#endif