/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:34:55 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 16:35:42 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taking_forks(t_philo_info *philo, int phil)
{
	pthread_mutex_lock(&philo->p->chop_sticks[phil - 1]);
	print_timestamp(phil, 2, philo->p);
	if (philo->p->philo_len == 1)
	{
		custom_sleep(philo->p->time_to_die);
		return (1);
	}
	pthread_mutex_lock(&philo->p->chop_sticks[(phil)
		% philo->p->philo_len]);
	print_timestamp(phil, 2, philo->p);
	return (0);
}

void	start_eating(t_philo_info *philo, int phil)
{
	print_timestamp(phil, 3, philo->p);
	pthread_mutex_lock(&(philo->p->monitor_t));
	philo->last_meal_taken = current_time_in_ms();
	philo->meals_count += 1;
	pthread_mutex_unlock(&(philo->p->monitor_t));
	custom_sleep(philo->p->time_to_eat);
}

void	release_forks(t_philo_info *philo, int phil)
{
	pthread_mutex_unlock(&philo->p->chop_sticks[phil - 1]);
	pthread_mutex_unlock(&philo->p->chop_sticks[(phil)
		% philo->p->philo_len]);
}

int	check_eat_cap(t_philo_info *philo)
{
	if (philo->p->eat_cap != -1
		&& (philo->meals_count >= philo->p->eat_cap))
	{
		pthread_mutex_lock(&(philo->p->monitor_t));
		philo->inf_loop = 0;
		pthread_mutex_unlock(&(philo->p->monitor_t));
		return (1);
	}
	return (0);
}

void	*dining_simulation(void *ph)
{
	t_philo_info	*philo;
	int				phil;

	philo = (t_philo_info *)ph;
	phil = philo->id;
	while (1)
	{
		pthread_mutex_lock(&(philo->p->monitor_t));
		if (!philo->inf_loop || philo->p->finish)
		{
			pthread_mutex_unlock(&(philo->p->monitor_t));
			break ;
		}
		pthread_mutex_unlock(&(philo->p->monitor_t));
		print_timestamp(phil, 1, philo->p);
		if (taking_forks(philo, phil))
			break ;
		start_eating(philo, phil);
		release_forks(philo, phil);
		if (check_eat_cap(philo))
			break ;
		print_timestamp(phil, 4, philo->p);
		custom_sleep(philo->p->time_to_sleep);
	}
	return (NULL);
}
