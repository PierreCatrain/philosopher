/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:34:31 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/08 23:21:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_routine_only_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n", get_time() - philo->data.start_time, \
			philo->index + 1);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->data.time_death * 1000);
	ft_change_status(philo, DEAD);
	printf("%ld %d died\n", get_time() - philo->data.start_time, \
			philo->index + 1);
	return (NULL);
}

int	only_one(t_all_philo *all_philo)
{
	if (pthread_create(&all_philo->philo[0].philo_thread, NULL, \
		&ft_routine_only_one, &all_philo->philo[0]) != 0)
		return (ERROR_PROGRAMME);
	if (pthread_join(all_philo->philo[0].philo_thread, NULL) != 0)
		return (ERROR_PROGRAMME);
	return (SUCCESS);
}

int	ft_creat_thread(t_data *data, t_all_philo *all_philo)
{
	int	index;

	index = 0;
	while (index < data->nb_philo)
	{
		if (pthread_create(&all_philo->philo[index].philo_thread, NULL, \
			&ft_routine, &all_philo->philo[index]) != 0)
			return (ERROR_PROGRAMME);
		index++;
	}
	if (pthread_create(&data->all_full_thread, NULL, \
		&ft_routine_all_full, all_philo) != 0)
		return (ERROR_PROGRAMME);
	if (pthread_create(&data->all_alive_thread, NULL, \
		&ft_routine_all_alive, all_philo) != 0)
		return (ERROR_PROGRAMME);
	return (SUCCESS);
}

int	ft_join_thread(t_data *data, t_all_philo *all_philo)
{
	int	index;

	index = 0;
	if (pthread_join(data->all_full_thread, NULL) != 0)
		return (ERROR_PROGRAMME);
	if (pthread_join(data->all_alive_thread, NULL) != 0)
		return (ERROR_PROGRAMME);
	while (index < data->nb_philo)
	{
		if (pthread_join(all_philo->philo[index].philo_thread, NULL) != 0)
			return (ERROR_PROGRAMME);
		index++;
	}
	return (SUCCESS);
}

int	ft_thread(t_data *data, t_all_philo *all_philo)
{
	if (data->nb_philo == 1)
		return (only_one(all_philo));
	if (ft_creat_thread(data, all_philo) == ERROR_PROGRAMME)
		return (ERROR_PROGRAMME);
	if (ft_join_thread(data, all_philo) == ERROR_PROGRAMME)
		return (ERROR_PROGRAMME);
	return (SUCCESS);
}
