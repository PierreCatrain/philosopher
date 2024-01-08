/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_all_full.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:02:20 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/07 23:02:34 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *ft_routine_all_full(void *arg)
{
    t_all_philo *all_philo;
    int     index;
    
    all_philo = (t_all_philo *)arg;
    index = 0;
    while (index < all_philo->philo[0].data.nb_philo && all_philo->philo[0].all_alive == ALL_ALIVE)
    {
        if (all_philo->philo[index].is_full == FULL)
            index++;
        else 
            index = 0;
    }
    index = 0;
    while (index < all_philo->philo[0].data.nb_philo)
    {
        all_philo->philo[index].all_full = FULL;
        index++;
    }
    return (NULL);
}