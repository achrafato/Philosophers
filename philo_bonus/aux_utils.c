/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:00:43 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 18:01:13 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_itoi(int nbr)
{
	int		len;
	char	*str;
	int		n;

	n = nbr;
	len = 0;
	if (nbr == 0)
		len = 1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*merge_two_string(char *str1, char *str2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*str;

	i = -1;
	j = 0;
	len1 = str_len(str1);
	len2 = str_len(str2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	while (str1[++i])
		str[i] = str1[i];
	while (str2[j])
		str[i++] = str2[j++];
	str[i] = '\0';
	free(str2);
	return (str);
}
