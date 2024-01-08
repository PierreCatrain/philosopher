/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 01:13:24 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/07 23:45:06 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long get_time(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int    set_data_philo(t_data *data, t_all_philo *all_philo)
{
    int index;
    
    index = 0;
    all_philo->philo = malloc(data->nb_philo * sizeof(t_philo));
    if (all_philo->philo == NULL)
        return (ERROR_SET);
    while (index < data->nb_philo)
    {
        all_philo->philo[index].index = index;
        all_philo->philo[index].nb_meal = 0;
        all_philo->philo[index].last_meal = get_time();
        all_philo->philo[index].status = NOT_START;
        all_philo->philo[index].is_full = NOT_FULL;
        all_philo->philo[index].all_full = NOT_FULL;
        all_philo->philo[index].all_alive = ALL_ALIVE;
        all_philo->philo[index].data = *data;
        index++;
    }
    return (SUCCESS);
}

int set_data_fork(t_data *data, t_all_philo *all_philo)
{
    int index;

    index = -1;
    data->fork = malloc(data->nb_philo * sizeof(pthread_mutex_t));
    if (data->fork == NULL)
        return (ERROR_SET); // free les philos
    while (++index < data->nb_philo)
    {
        if (pthread_mutex_init(&data->fork[index], NULL) != 0)
            return (ERROR_SET); // free les philos et destroy les fork deja init
    }
    index = 0;
    if (data->nb_philo > 1)
        all_philo->philo[0].left_fork = &data->fork[data->nb_philo - 1];
    all_philo->philo[0].right_fork = &data->fork[0];
    while (++index < data->nb_philo)
    {
        all_philo->philo[index].left_fork = &data->fork[index - 1];
        all_philo->philo[index].right_fork = &data->fork[index];
    }
    return (SUCCESS);
}

int set_data(t_data *data, t_all_philo *all_philo, int argc, char **argv)
{
    data->nb_philo = ft_atoi(argv[1]);
    data->time_death = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    data->meal_goal = -1;
    if (argc == 6)
        data->meal_goal = ft_atoi(argv[5]);
    data->start_time = get_time();
    if (set_data_philo(data, all_philo) == ERROR_SET)
        return (ERROR_SET);
    if (set_data_fork(data, all_philo) == ERROR_SET)
        return (ERROR_SET);
    return (SUCCESS);
}