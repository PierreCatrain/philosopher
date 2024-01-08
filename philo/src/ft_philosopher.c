/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:34:31 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/08 01:52:11 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int     ft_philosopher(t_data *data, t_all_philo *all_philo)
{
    int index;

    index = 0;
    if (data->nb_philo == 1)
    {
        pthread_mutex_lock(all_philo->philo[0].right_fork);
        printf("%ld %d has taken a fork\n", get_time() - data->start_time, all_philo->philo[0].index + 1);
        pthread_mutex_unlock(all_philo->philo[0].right_fork);
        usleep(data->time_death * 1000);
        printf("%ld %d died\n", get_time() - data->start_time, all_philo->philo[0].index + 1);
        return (SUCCESS);
    }
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
    index = 0;
    while (index < data->nb_philo)
    {
        if (pthread_join(all_philo->philo[index].philo_thread, NULL) != 0)
            return (ERROR_PROGRAMME);
        index++;
    }
    if (pthread_join(data->all_full_thread, NULL) != 0)
            return (ERROR_PROGRAMME);
    if (pthread_join(data->all_alive_thread, NULL) != 0)
            return (ERROR_PROGRAMME);
    return (SUCCESS);
}