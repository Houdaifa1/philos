# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher
{
    int             philo_id;
    int             left_fork_id;
    int             right_fork_id;
    int             change;
    long            time_sec;
    long            time_usec;
    long             last_eat;
    int             dead;
    int             num_of_philos;
    long            time_to_die;
    long            time_to_sleep;
    long            time_to_eat;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_philosoper;

int	ft_atoi(char *str);


# endif
