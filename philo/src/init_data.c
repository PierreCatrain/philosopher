/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 01:13:24 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/06 02:12:16 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

long get_time(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int    init_data_philo(t_data *data)
{
    int index;
    
    index = 0;
    data->philo = malloc(data->nb_philo * sizeof(t_philo));
    if (data->philo == NULL)
        return (ERROR_INIT);
    while (index < data->nb_philo)
    {
        data->philo[index].index = index + 1;
        data->philo[index].nb_meal = 0;
        data->philo[index].last_meal = 0;
        data->philo[index].state = NOT_START;
        index++;
    }
    return (SUCCESS);
}

int init_data(t_data *data, int argc, char **argv)
{
    data->nb_philo = ft_atoi(argv[1]);
    data->time_death = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    data->meal_goal = -1;
    if (argc == 6)
        data->meal_goal = ft_atoi(argv[5]);
    data->start_time = get_time();
    if (init_data_philo(&data) == ERROR_INIT)
        return (ERROR_INIT);
    return (SUCCESS);
}