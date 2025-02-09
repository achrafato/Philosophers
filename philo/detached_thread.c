/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detached_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:38:10 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 16:38:59 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_dead_with_eat_cap(t_philo_info *philos)
{
	if ((philos->p->eat_cap != -1)
		&& (philos->meals_count < philos->p->eat_cap)
		&& ((current_time_in_ms() - philos->last_meal_taken)
			>= philos->p->time_to_die))
	{
		philos->p->finish = 1;
		pthread_mutex_unlock(&(philos->p->monitor_t));
		print_timestamp(philos->id, 5, philos->p);
		return (1);
	}
	return (0);
}

int	handle_dead_without_eat_cap(t_philo_info *philos)
{
	if ((philos->p->eat_cap == -1) && ((current_time_in_ms()
				- philos->last_meal_taken) >= philos->p->time_to_die))
	{
		philos->p->finish = 1;
		pthread_mutex_unlock(&(philos->p->monitor_t));
		print_timestamp(philos->id, 5, philos->p);
		return (1);
	}
	return (0);
}

void	*monitor_philos_dead(void *philo)
{
	t_philo_info	*philos;
	int				i;

	philos = (t_philo_info *)philo;
	while (1)
	{
		i = 0;
		philos = (t_philo_info *)philo;
		while (philos)
		{
			pthread_mutex_lock(&(philos->p->monitor_t));
			if (handle_dead_with_eat_cap(philos))
				return (NULL);
			else if (handle_dead_without_eat_cap(philos))
				return (NULL);
			pthread_mutex_unlock(&(philos->p->monitor_t));
			philos = philos->next;
		}
	}
}

void	create_detached_threads(t_philo *philo, t_philo_info *head)
{
	pthread_create(&philo->thread_detached_dead,
		NULL, monitor_philos_dead, head);
	pthread_detach(philo->thread_detached_dead);
}
