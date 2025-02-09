/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:42:31 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/10 17:48:31 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time_in_ms(void)
{
	struct timeval	current_time;
	long			current_date;

	gettimeofday(&current_time, NULL);
	current_date = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (current_date);
}

int	custom_sleep(long milliseconds)
{
	long	start;

	start = current_time_in_ms();
	while ((current_time_in_ms() - start) < milliseconds)
		;
	return (0);
}

void	print_timestamp(int philo_id, int i, t_philo *philo)
{
	pthread_mutex_lock(&(philo->monitor_t));
	if (!philo->finish || (i == 5))
	{
		pthread_mutex_lock(&(philo->write_p));
		if (i == 1)
			printf("%ld %d is thinking\n",
				current_time_in_ms() - philo->start_date, philo_id);
		else if (i == 2)
			printf("%ld %d has taken a fork\n",
				current_time_in_ms() - philo->start_date, philo_id);
		else if (i == 3)
			printf("%ld %d is eating\n",
				current_time_in_ms() - philo->start_date, philo_id);
		else if (i == 4)
			printf("%ld %d is sleeping\n",
				current_time_in_ms() - philo->start_date, philo_id);
		else if (i == 5)
			printf("%ld %d died\n",
				current_time_in_ms() - philo->start_date, philo_id);
		pthread_mutex_unlock(&(philo->write_p));
	}
	pthread_mutex_unlock(&(philo->monitor_t));
}

void	free_all(t_philo *philo, t_philo_info *head)
{
	int				i;
	t_philo_info	*current;

	i = 0;
	while (i < philo->philo_len)
		pthread_mutex_destroy(&philo->chop_sticks[i++]);
	free(philo->philo_threads);
	free(philo->chop_sticks);
	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}
	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_philo_info	*head;

	if (!(5 <= argc && argc <= 6))
		return (1);
	head = NULL;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	if (!check_input(argc, argv, philo))
		return (free(philo), 1);
	init_chop_sticks(philo);
	if (!init_philos_data(&head, philo))
		return (free_all(philo, head), 1);
	create_detached_threads(philo, head);
	init_philos_threads(philo, head);
	free_all(philo, head);
}
