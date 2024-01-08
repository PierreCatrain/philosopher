/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:15:37 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/08 00:37:32 by picatrai         ###   ########.fr       */
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
# define ERROR_SET 2
# define ERROR_PROGRAMME 3
# define TIME_MIN 60
# define NOT_FULL 0
# define FULL 1
# define NOT_ALL_ALIVE 0
# define ALL_ALIVE 1
# define DEAD 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define NOT_START 4
# define NOT_DEAD 5

typedef struct s_data
{
    int nb_philo;
    int time_death;
    int time_eat;
    int time_sleep;
    int meal_goal;
    long start_time;
    pthread_t   all_full_thread;
    pthread_t   all_alive_thread;
    pthread_mutex_t *fork;

}   t_data;

typedef struct s_philo
{
    int index;
    int nb_meal;
    long last_meal;
    int     status;
    int     is_full;
    int     all_full;
    int     all_alive;
    t_data  data;
    pthread_t   philo_thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_philo;

typedef struct s_all_philo
{
    t_philo *philo;
}   t_all_philo;


int     check_args(int argc, char **argv);
int     set_data(t_data *data, t_all_philo *all_philo, int argc, char **argv);
int     ft_philosopher(t_data *data, t_all_philo *all_philo);
void    *ft_routine(void *arg);
void    *ft_routine_all_full(void *arg);
void    *ft_routine_all_alive(void *arg);

long	ft_atoi(char *str);
long    get_time(void);

#endif