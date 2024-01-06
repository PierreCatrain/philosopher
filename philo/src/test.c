/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:43:44 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/06 01:35:17 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
    int value;
    pthread_mutex_t mutex;
}   t_data;

long get_time(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    *count(void *arg)
{
    t_data *data;
    int i;
    
    i = 100000;
    data = (t_data *)arg;
    while (i > 0)
    {
        pthread_mutex_lock(&data->mutex);
        (data->value)++;
        pthread_mutex_unlock(&data->mutex);
        i--;
    }
    return (NULL);
}

int main(void)
{
    long    start_time;
    long    now;

    start_time = get_time();
    printf("%ld\n", start_time);
    usleep(1000000);
    now = get_time();
    printf("%ld\n", now);

    t_data *data;
    pthread_t t1;
    pthread_t t2;

    data = malloc(sizeof(t_data));
    if (data == NULL)
        exit(1);
    data->value = 0;
    pthread_mutex_init(&data->mutex, NULL);
    if (pthread_create(&t1, NULL, count, data) != 0)
    {
        pthread_mutex_destroy(&data->mutex);
        exit(0);
    }
    if (pthread_create(&t2, NULL, count, data) != 0)
    {
        pthread_mutex_destroy(&data->mutex);
        exit(0);
    }
    if (pthread_join(t1, NULL) != 0)
    {
        pthread_mutex_destroy(&data->mutex);
        exit(0);
    }
    if (pthread_join(t2, NULL) != 0)
    {
        pthread_mutex_destroy(&data->mutex);
        exit(0);
    }
    printf("%d", data->value);
}