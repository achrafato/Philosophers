/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:52:06 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 18:39:02 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo_info	*new_node(t_philo *philo)
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
	new->inf_loop = 1;
	new->p = philo;
	new->next = NULL;
	return (new);
}

int	push(t_philo *philo, t_philo_info **map)
{
	t_philo_info	*newnode;
	t_philo_info	*last;

	newnode = new_node(philo);
	if (!newnode)
		return (0);
	if (!map || !(*map))
		*map = newnode;
	else
	{
		last = last_node(*map);
		last->next = newnode;
	}
	return (1);
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
