/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:52:06 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/10 16:36:36 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	stack_len(t_philo_info *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

t_philo_info	*last_node(t_philo_info *top)
{
	while (top->next)
	{
		top = top->next;
	}
	return (top);
}

t_philo_info	*new_node(t_philo_bonus *philo)
{
	t_philo_info	*new;
	static int		id;

	new = malloc(sizeof(t_philo_info));
	if (!new)
		return (NULL);
	id++;
	new->id = id;
	new->meals_count = 0;
	new->last_meal_taken = current_time_in_ms();
	new->p = philo;
	new->sem_name = merge_two_string("/monitor_t", ft_itoi(id));
	sem_unlink(new->sem_name);
	new->monitor_t = sem_open(new->sem_name, O_CREAT, 0644, 1);
	if (new->monitor_t == SEM_FAILED)
	{
		sem_unlink(new->sem_name);
		exit(1);
	}
	new->next = NULL;
	return (new);
}

void	push(t_philo_bonus *philo, t_philo_info **map)
{
	t_philo_info	*newnode;
	t_philo_info	*last;

	newnode = new_node(philo);
	if (!map || !(*map))
		*map = newnode;
	else
	{
		last = last_node(*map);
		last->next = newnode;
	}
}

void	free_linked_list(t_philo_info **head)
{
	t_philo_info	*current;

	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		free(current);
	}
}
