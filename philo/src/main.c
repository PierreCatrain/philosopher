/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:15:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/07 00:39:57 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    t_philo *philo;
    
    philo = NULL;
    if (check_args(argc, argv) == ERROR_ARGS)
        return (ERROR_ARGS);
    if (init_data(&data, &philo, argc, argv) == ERROR_INIT)
        return (ERROR_INIT);
    if (ft_philosopher(data, philo) == ERROR_PROGRAMME)
        return (ERROR_PROGRAMME);
    return (SUCCESS);
}