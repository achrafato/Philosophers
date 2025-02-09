/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:50:59 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 19:41:44 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_number_validity(char *num)
{
	int	i;
	int	signe;

	signe = 1;
	i = 0;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			return (0);
		i++;
	}
	if (!num[i])
		return (0);
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(int argc, char **argv, t_philo_bonus *philo)
{
	int	a;

	a = 1;
	(1) && (philo->eat_cap = -1, philo->finish = 0);
	while (a < argc)
	{
		if (!check_number_validity(argv[a]))
			return (write(2, "invalid input\n", 14), 0);
		if (a == 1)
			philo->philo_len = ft_atoi(argv[a]);
		else if (a == 2)
			philo->time_to_die = ft_atoi(argv[a]);
		else if (a == 3)
			philo->time_to_eat = ft_atoi(argv[a]);
		else if (a == 4)
		{
			philo->time_to_sleep = ft_atoi(argv[a]);
		}
		else if (a == 5)
			philo->eat_cap = ft_atoi(argv[a]);
		if (ft_atoi(argv[a]) == 2147483648 || ft_atoi(argv[a]) == 0)
			return (0);
		a++;
	}
	return (1);
}
