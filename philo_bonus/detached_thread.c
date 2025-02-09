/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detached_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:53:56 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 17:54:06 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	handle_dead_with_eat_cap(t_philo_info *philos)
{
	sem_wait(philos->monitor_t);
	if ((philos->p->eat_cap != -1)
		&& (philos->meals_count < philos->p->eat_cap)
		&& ((current_time_in_ms() - philos->last_meal_taken)
			>= philos->p->time_to_die))
	{
		sem_post(philos->monitor_t);
		print_state_infos(philos->id, 5, philos);
		exit(EXIT_FAILURE);
		return (1);
	}
	sem_post(philos->monitor_t);
	return (0);
}

int	handle_dead_without_eat_cap(t_philo_info *philos)
{
	sem_wait(philos->monitor_t);
	if ((philos->p->eat_cap == -1) && ((current_time_in_ms()
				- philos->last_meal_taken) >= philos->p->time_to_die))
	{
		sem_post(philos->monitor_t);
		print_state_infos(philos->id, 5, philos);
		exit(EXIT_FAILURE);
		return (1);
	}
	sem_post(philos->monitor_t);
	return (0);
}

void	*monitor_dead_philo(void *philo)
{
	t_philo_info	*current_philo;

	while (1)
	{
		current_philo = (t_philo_info *)philo;
		if (handle_dead_with_eat_cap(current_philo))
			exit(EXIT_FAILURE);
		else if (handle_dead_without_eat_cap(current_philo))
			exit(EXIT_FAILURE);
	}
}

void	create_detached_threads(t_philo_info *current_philo)
{
	pthread_create(&current_philo->detached_thread_dead,
		NULL, monitor_dead_philo, current_philo);
	pthread_detach(current_philo->detached_thread_dead);
}
