/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_all_alive.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 23:30:35 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/08 23:20:55 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_change_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->mutex_status);
	philo->status = status;
	pthread_mutex_unlock(&philo->mutex_status);
}

void	*ft_routine_all_alive(void *arg)
{
	t_all_philo	*all_philo;
	int			index;

	all_philo = (t_all_philo *)arg;
	index = 0;
	while (all_philo->philo[0].all_full == NOT_FULL)
	{
		if (get_time() - all_philo->philo[index].last_meal > \
				all_philo->philo[index].data.time_death)
			break ;
		else
			index++;
		if (index == all_philo->philo[0].data.nb_philo)
			index = 0;
	}
	if (all_philo->philo[0].all_full == NOT_FULL)
		printf("%ld %d died\n", get_time() - \
				all_philo->philo[index].data.start_time, \
				all_philo->philo[index].index + 1);
	index = -1;
	while (++index < all_philo->philo[0].data.nb_philo)
		ft_change_status(&all_philo->philo[index], DEAD);
	return (NULL);
}
