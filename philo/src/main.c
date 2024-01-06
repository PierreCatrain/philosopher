/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:15:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/06 02:09:58 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    
    if (check_args(argc, argv) == ERROR_ARGS)
        return (ERROR_ARGS);
    if (init_data(&data, argc, argv) == ERROR_INIT)
        return (ERROR_INIT);
}