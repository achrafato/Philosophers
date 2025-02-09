/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:49:13 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/10 16:48:59 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	waiting_childs(t_philo_bonus *args)
{
	int	i;
	int	status;

	i = 0;
	while (i < args->philo_len)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			i = 0;
			while (i < args->philo_len)
			{
				kill(args->pids[i], SIGTERM);
				i++;
			}
			break ;
		}
		i++;
	}
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

void	init_philos_processes(t_philo_bonus *args, t_philo_info *head)
{
	int				i;
	pid_t			pid;
	t_philo_info	*current_philo;

	i = 0;
	args->pids = malloc(sizeof(pid_t) * args->philo_len);
	if (!args->pids)
		(free_all(args, head), exit(EXIT_FAILURE));
	while (i < args->philo_len)
	{
		pid = fork();
		if (pid < 0)
			(free_all(args, head), exit(EXIT_FAILURE));
		else if (pid == 0)
		{
			current_philo = return_philo_by_index(i, head);
			(simulate_dining(current_philo), exit(EXIT_SUCCESS));
		}
		else
			args->pids[i] = pid;
		usleep(50);
		i++;
	}
	i = 0;
	waiting_childs(args);
}

void	init_philos_data(t_philo_info **head, t_philo_bonus *args)
{
	int	c;

	args->start_date = current_time_in_ms();
	c = 0;
	while (c < args->philo_len)
	{
		push(args, head);
		c++;
	}
}

void	init_chop_stciks_and_write_semap(t_philo_bonus	*args, t_philo_info *h)
{
	sem_unlink("/write_lock");
	args->write_p = sem_open("/write_lock", O_CREAT, 0644, 1);
	if (args->write_p == SEM_FAILED)
	{
		sem_unlink("/write_lock");
		sem_close(args->write_p);
		printf("here 1\n");
		free_all(args, h);
		exit(1);
	}
	sem_unlink("/chop_stick");
	args->forks = sem_open("/chop_stick",
			O_CREAT, 0644, args->philo_len);
	if (args->forks == SEM_FAILED)
	{
		sem_unlink("/chop_stick");
		printf("here 2\n");
		free_all(args, h);
		exit(1);
	}
}
