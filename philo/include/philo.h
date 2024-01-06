/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:15:37 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/06 02:12:37 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_C
# define PHILO_C

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_ATOI 3000000000
# define SUCCESS 0
# define ERROR_ARGS 1
# define ERROR_INIT 2
# define TIME_MIN 60
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define NOT_START 4

typedef struct s_philo
{
    int index;
    int nb_meal;
    long last_meal;
    int     state;
}   t_philo;

typedef struct s_data
{
    int nb_philo;
    int time_death;
    int time_eat;
    int time_sleep;
    int meal_goal;
    long start_time;
    t_philo *philo;
}   t_data;

int     check_args(int argc, char **argv);
int     init_data(t_data *data, int argc, char **argv);

long	ft_atoi(char *str);

#endif