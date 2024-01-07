/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:23:36 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/06 17:33:51 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(char *str)
{
	long	resultat;
	int		i;
	int		signe;

	i = 0;
	resultat = 0;
	signe = 1;
	if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat *= 10;
		resultat += str[i] - '0';
		i++;
	}
	if (str[i] != '\0' || resultat > 2147483647 || resultat < 0)
		return (ERROR_ATOI);
	return (resultat * signe);
}

int only_int_positif(char **argv)
{
    int index;
    index = 1;
    while (argv[index])
    {
        if (ft_atoi(argv[index]) == ERROR_ATOI)
            return (ERROR_ARGS);
        index++;
    }
    return (SUCCESS);
}

int time_minimum(char **argv)
{
    int index;

    index = 2;
    while (index < 5)
    {
        if (ft_atoi(argv[index]) < TIME_MIN)
            return (ERROR_ARGS);
        index++;
    }
    return (SUCCESS);
}

int check_args(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("wrong input\n");
        printf("4 or 5 args are expected\n");
        return (ERROR_ARGS);
    }
    else if (only_int_positif(argv) == ERROR_ARGS)
    {
        printf("wrong input\n");
        printf("positf integer are expected\n");
        return (ERROR_ARGS);
    }
    else if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 1024)
    {
        printf("wrong input\n");
        printf("between 1 and 1024 philosophers are expected\n");
        return (ERROR_ARGS);
    }
    else if (time_minimum(argv) == ERROR_ARGS)
    {
        printf("wrong input\n");
        printf("time to eat, sleep and die should be more than %dms\n", TIME_MIN);
        return (ERROR_ARGS);
    }
    return (SUCCESS);
}