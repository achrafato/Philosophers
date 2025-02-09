/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:29:48 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/10 16:49:40 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_state_infos(int ph_id, int i, t_philo_info *current)
{
	struct timeval	current_time;
	long			current_date;

	sem_wait((current->p->write_p));
	gettimeofday(&current_time, NULL);
	current_date = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	if (i == 1)
		printf("%ld %d is thinking\n",
			current_date - current->p->start_date, ph_id);
	else if (i == 2)
		printf("%ld %d has taken a fork\n",
			current_date - current->p->start_date, ph_id);
	else if (i == 3)
		printf("%ld %d is eating\n",
			current_date - current->p->start_date, ph_id);
	else if (i == 4)
		printf("%ld %d is sleeping\n",
			current_date - current->p->start_date, ph_id);
	else if (i == 5)
	{
		printf("%ld %d is died\n",
			current_date - current->p->start_date, ph_id);
		return ;
	}
	sem_post((current->p->write_p));
}

void	free_all(t_philo_bonus *args, t_philo_info *head)
{
	int				i;
	t_philo_info	*current;

	i = 0;
	while (head)
	{
		current = head;
		free(head->sem_name);
		head = head->next;
		free(current);
	}
	if (args->pids)
		free(args->pids);
	free(args);
}

int	main(int argc, char **argv)
{
	t_philo_bonus	*args;
	t_philo_info	*head;
	int				i;

	if (!(5 <= argc && argc <= 6))
		return (0);
	i = 0;
	head = NULL;
	args = malloc(sizeof(t_philo_bonus));
	if (!args)
		return (1);
	if (!check_input(argc, argv, args))
		return (free(args), 1);
	init_philos_data(&head, args);
	init_chop_stciks_and_write_semap(args, head);
	args->start_date = current_time_in_ms();
	init_philos_processes(args, head);
	unlink_and_close_semaphores(args, head);
	free_all(args, head);
}
