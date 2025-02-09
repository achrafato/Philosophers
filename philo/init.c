/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:30:30 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/10 17:48:11 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_chop_sticks(t_philo *philo)
{
	int	c;

	c = 0;
	philo->chop_sticks = malloc(sizeof(pthread_mutex_t) * (philo->philo_len));
	if (!philo->chop_sticks)
		return ;
	while (c < philo->philo_len)
	{
		pthread_mutex_init(&philo->chop_sticks[c], NULL);
		c++;
	}
	pthread_mutex_init(&(philo->write_p), NULL);
	pthread_mutex_init(&(philo->monitor_t), NULL);
}

int	init_philos_data(t_philo_info **head, t_philo *philo)
{
	int	c;

	philo->start_date = current_time_in_ms();
	c = 0;
	while (c < philo->philo_len)
	{
		if (!push(philo, head))
			return (0);
		c++;
	}
	return (1);
}

t_philo_info	*return_philo_by_index(int c, t_philo_info *top)
{
	int	i;

	i = 0;
	while (i < c && top)
	{
		i++;
		top = top->next;
	}
	return (top);
}

void	init_philos_threads(t_philo *philo, t_philo_info *head)
{
	int				c;
	t_philo_info	*current_philo;

	c = 0;
	philo->philo_threads = malloc(sizeof(pthread_t) * philo->philo_len);
	if (!philo->philo_threads)
		return ;
	while (c < philo->philo_len)
	{
		current_philo = return_philo_by_index(c, head);
		pthread_create(&philo->philo_threads[c], NULL,
			dining_simulation, current_philo);
		c++;
		usleep(50);
	}
	c = 0;
	while (c < philo->philo_len)
		pthread_join(philo->philo_threads[c++], NULL);
}
