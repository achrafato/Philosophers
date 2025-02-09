/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:52:11 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 20:50:10 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	taking_forks(t_philo_info *current_philo, int phil)
{
	sem_wait(current_philo->p->forks);
	print_state_infos(phil, 2, current_philo);
	if (current_philo->p->philo_len == 1)
		sem_wait(current_philo->p->forks);
	sem_wait(current_philo->p->forks);
	print_state_infos(phil, 2, current_philo);
}

void	start_eating(t_philo_info *current_philo, int phil)
{
	sem_wait(current_philo->monitor_t);
	current_philo->last_meal_taken = current_time_in_ms();
	sem_post(current_philo->monitor_t);
	print_state_infos(phil, 3, current_philo);
	custom_sleep(current_philo->p->time_to_eat);
	sem_wait(current_philo->monitor_t);
	current_philo->meals_count++;
	sem_post(current_philo->monitor_t);
}

void	release_forks(t_philo_info *current_philo)
{
	sem_post(current_philo->p->forks);
	sem_post(current_philo->p->forks);
}

void	simulate_dining(t_philo_info *current_philo)
{
	int	phil;

	phil = current_philo->id;
	create_detached_threads(current_philo);
	while (1)
	{
		print_state_infos(phil, 1, current_philo);
		taking_forks(current_philo, phil);
		start_eating(current_philo, phil);
		release_forks(current_philo);
		if (current_philo->p->eat_cap != -1
			&& (current_philo->meals_count >= current_philo->p->eat_cap))
		{
			break ;
		}
		print_state_infos(phil, 4, current_philo);
		custom_sleep(current_philo->p->time_to_sleep);
	}
}

void	unlink_and_close_semaphores(t_philo_bonus *args, t_philo_info *head)
{
	int				i;
	t_philo_info	*current;

	i = 0;
	(void)head;
	current = head;
	while (current)
	{
		sem_close(current->monitor_t);
		sem_unlink(current->sem_name);
		current = current->next;
	}
	sem_close(args->write_p);
	sem_unlink("/write_lock");
	sem_close(args->forks);
	sem_unlink("/chop_stick");
}
