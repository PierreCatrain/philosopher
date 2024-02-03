/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 04:19:56 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/03 21:39:59 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_protect_block_fork(t_data *data)
{
	if (get_time() - data->start_time >= 1)
	{
		usleep(data->time_death * 1000);
		printf("%ld 1 died\n", get_time() - data->start_time);
		return (SUCCESS);
	}
	return (1);
}

void	ft_free_and_destroy_set_data(t_all_philo all_philo)
{
	int	index;

	index = 0;
	while (index < all_philo.philo[0].data.nb_philo)
	{
		pthread_mutex_destroy(&all_philo.philo[index].mutex_status);
		index++;
	}
	free(all_philo.philo);
}

void	ft_free_and_destroy(t_data data, t_all_philo all_philo)
{
	int	index;

	index = 0;
	while (index < data.nb_philo)
	{
		pthread_mutex_destroy(&all_philo.philo[index].mutex_status);
		pthread_mutex_destroy(&data.fork[index]);
		index++;
	}
	free(data.fork);
	free(all_philo.philo);
}
