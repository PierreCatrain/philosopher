/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_all_alive.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 23:30:35 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/07 23:50:30 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *ft_routine_all_alive(void *arg)
{
    t_all_philo *all_philo;
    int index;

    all_philo = (t_all_philo *)arg;
    index = 0;
    while (all_philo->philo[0].all_full == NOT_FULL)
    {
        if (all_philo->philo[index].status == DEAD)
            break ;
        else
            index++;
        if (index == all_philo->philo[0].data.nb_philo)
            index = 0;
    }
    index = 0;
    while (index < all_philo->philo[0].data.nb_philo)
    {
        all_philo->philo[index].all_alive = NOT_ALL_ALIVE;
        index++;
    }
    return (NULL);
}