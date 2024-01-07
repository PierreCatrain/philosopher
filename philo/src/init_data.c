/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 01:13:24 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/07 00:37:24 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long get_time(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int    init_data_philo(t_data *data, t_philo **philo)
{
    int index;
    
    index = 0;
    *philo = malloc(data->nb_philo * sizeof(t_philo));
    if (*philo == NULL) // peut etre que philo
        return (ERROR_INIT);
    while (index < data->nb_philo)
    {
        (*philo)[index].index = index;
        (*philo)[index].nb_meal = 0;
        (*philo)[index].last_meal = get_time();
        (*philo)[index].state = NOT_START;
        (*philo)[index].data = *data;
        index++;
    }
    return (SUCCESS);
}

int init_data_fork(t_data *data, t_philo **philo)
{
    int index;
    t_philo *tmp;

    tmp = *philo;
    index = -1;
    data->fork = malloc(data->nb_philo * sizeof(pthread_mutex_t));
    if (data->fork == NULL)
        return (ERROR_INIT); // free les philos
    while (++index < data->nb_philo)
    {
        if (pthread_mutex_init(&data->fork[index], NULL) != 0)
            return (ERROR_INIT); // free les philos et les fork deja init
    }
    index = 0;
    if (data->nb_philo > 1)
        tmp[0].left_fork = &data->fork[data->nb_philo - 1];
    tmp[0].right_fork = &data->fork[0];
    while (++index < data->nb_philo)
    {
        tmp[index].left_fork = &data->fork[index - 1];
        tmp[index].right_fork = &data->fork[index];
    }
    return (SUCCESS);
}

int init_data(t_data *data, t_philo **philo, int argc, char **argv)
{
    data->nb_philo = ft_atoi(argv[1]);
    data->time_death = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    data->meal_goal = -1;
    if (argc == 6)
        data->meal_goal = ft_atoi(argv[5]);
    data->start_time = get_time();
    //pthread_mutex_init(&data->mut_print, NULL);
    if (init_data_philo(data, philo) == ERROR_INIT)
        return (ERROR_INIT);
    if (init_data_fork(data, philo) == ERROR_INIT)
        return (ERROR_INIT);
    return (SUCCESS);
}