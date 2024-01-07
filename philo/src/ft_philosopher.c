/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:34:31 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/07 01:01:00 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int     ft_is_dead(t_philo *philo)
{
    if (get_time() - philo->last_meal > philo->data.time_death)
    {
        philo->state = DEAD;
        return (DEAD);
    }
    return (NOT_DEAD);
}

void    ft_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    printf("%ld %d has taken a fork\n", get_time() - philo->data.start_time, philo->index + 1);
    pthread_mutex_lock(philo->right_fork);
    printf("%ld %d has taken a fork\n", get_time() - philo->data.start_time, philo->index + 1);
    philo->state = EATING;
    philo->last_meal = get_time();
    philo->nb_meal++;
    printf("%ld %d is eating\n", get_time() - philo->data.start_time, philo->index + 1);
    usleep(philo->data.time_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    ft_sleep(t_philo *philo)
{
    philo->state = SLEEPING;
    printf("%ld %d is sleeping\n", get_time() - philo->data.start_time, philo->index + 1);
    usleep(philo->data.time_sleep * 1000);
}

void    ft_think(t_philo *philo)
{
    philo->state = THINKING;
    printf("%ld %d is thinking\n", get_time() - philo->data.start_time, philo->index + 1);
}

void    *ft_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->index % 2 != 0)
        usleep(philo->data.time_eat * 1000);
    if (ft_is_dead(philo) == DEAD)
            return (NULL);
    while (philo->nb_meal < philo->data.meal_goal)
    {   
        ft_eat(philo);
        if (ft_is_dead(philo) == DEAD)
            return (NULL);
        ft_sleep(philo);
        if (ft_is_dead(philo) == DEAD)
            return (NULL);
        ft_think(philo);
        if (ft_is_dead(philo) == DEAD)
            return (NULL);
    }
    return (NULL);
}

int     ft_philosopher(t_data data, t_philo *philo)
{
    int index;

    index = 0;
    while (index < data.nb_philo)
    {
        if (pthread_create(&philo[index].philo_thread, NULL, \
        &ft_routine, &philo[index]) != 0)
            return (ERROR_PROGRAMME);
        index++;
    }
    index = 0;
    while (index < data.nb_philo)
    {
        if (pthread_join(philo[index].philo_thread, NULL) != 0)
            return (ERROR_PROGRAMME);
        index++;
    }
    return (SUCCESS);
}