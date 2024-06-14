# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher
{
    int             philo_id;
    int             left_fork_id;
    int             right_fork_id;
    int             change;
    int             lah_irhmo;
    long            time;
    int             eat;
    long            time_to_die;
    long            time_before;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
}   t_philosoper;

int	ft_atoi(char *str);


# endif