/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:59:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/08 02:46:09 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void     ft_change_status(t_philo *philo, int status)
{
    pthread_mutex_lock(&philo->mutex_status);
    philo->status = status;
    pthread_mutex_unlock(&philo->mutex_status);
}

int     ft_is_dead(t_philo *philo)
{
    return (philo->status);
}

int    ft_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
    {
        pthread_mutex_unlock(philo->left_fork);
        return (DEAD);
    }
    printf("%ld %d has taken a fork\n", get_time() - philo->data.start_time, philo->index + 1);
    pthread_mutex_lock(philo->right_fork);
    if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return (DEAD);
    }
    printf("%ld %d has taken a fork\n", get_time() - philo->data.start_time, philo->index + 1);
    ft_change_status(philo, EATING);
    if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return (DEAD);
    }
    printf("%ld %d is eating\n", get_time() - philo->data.start_time, philo->index + 1);
    philo->last_meal = get_time();
    usleep(philo->data.time_eat * 1000);
    philo->nb_meal++;
    if (philo->nb_meal >= philo->data.meal_goal && philo->data.meal_goal >= 0)
        philo->is_full = FULL;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (NOT_DEAD);
}

void    ft_sleep(t_philo *philo)
{
    ft_change_status(philo, SLEEPING);
    if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
        return ;
    printf("%ld %d is sleeping\n", get_time() - philo->data.start_time, philo->index + 1);
    usleep(philo->data.time_sleep * 1000);
}

void    ft_think(t_philo *philo)
{
    ft_change_status(philo, THINKING);
    if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
        return ;
    printf("%ld %d is thinking\n", get_time() - philo->data.start_time, philo->index + 1);
}

void    *ft_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->index % 2 != 0)
        usleep(philo->data.time_eat * 1000);
    if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
            return (NULL);
    while (philo->status != DEAD && philo->all_full == NOT_FULL && philo->all_alive == ALL_ALIVE)
    {
        if (ft_eat(philo) == DEAD)
            return (NULL);
        if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
            return (NULL);
        ft_sleep(philo);
        if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
            return (NULL);
        ft_think(philo);
        if (philo->status == DEAD || philo->all_full == FULL || philo->all_alive == NOT_ALL_ALIVE)
            return (NULL);
    }
    return (NULL);
}