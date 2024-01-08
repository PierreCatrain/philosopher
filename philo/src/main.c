/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:15:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/08 04:28:41 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    t_all_philo all_philo;
    
    if (check_args(argc, argv) == ERROR_ARGS)
        return (ERROR_ARGS);
    if (set_data(&data, &all_philo, argc, argv) == ERROR_SET)
        return (ERROR_SET);
    if (ft_thread(&data, &all_philo) == ERROR_PROGRAMME)
        return (ft_free_and_destroy(data, all_philo), ERROR_PROGRAMME);
    return (ft_free_and_destroy(data, all_philo), SUCCESS);
}