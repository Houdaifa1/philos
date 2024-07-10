#include "philosophers.h"

void *test_thread(void *philo)
{
    t_philosoper *philos = (t_philosoper *)philo;
    struct timeval now;
    long time_now;
    pthread_mutex_t   lock;

    int i = 0;
    int change = 0;
    philos->last_eat = 0;  
    philos->dead = 0;   
    pthread_mutex_init(&lock, NULL);
    while (1)
    {                               
        if (philos->philo_id % 2 == (change % 2))
        {
            pthread_mutex_lock(philos->right_fork);
            gettimeofday(&now, NULL);
            time_now = (now.tv_sec - philos->time_sec) * 1000 + (now.tv_usec - philos->time_usec) / 1000;
            printf("%ld  philosopher %d  has taking a fork \n", time_now, philos->philo_id);
            pthread_mutex_lock(philos->left_fork);
            gettimeofday(&now, NULL);
            time_now = (now.tv_sec - philos->time_sec) * 1000 + (now.tv_usec - philos->time_usec) / 1000;
            printf("%ld  philosopher %d  is eating now \n", time_now, philos->philo_id);
            philos->last_eat = time_now;
            usleep(philos->time_to_eat);
            pthread_mutex_unlock(philos->right_fork);
            pthread_mutex_unlock(philos->left_fork);
        }
        else
        {
            gettimeofday(&now, NULL);
            time_now = (now.tv_sec - philos->time_sec) * 1000 + (now.tv_usec - philos->time_usec) / 1000;
            printf("%ld  philosopher %d  is sleeping now \n", time_now, philos->philo_id);
            usleep(philos->time_to_sleep);
            gettimeofday(&now, NULL);
                        time_now = (now.tv_sec - philos->time_sec) * 1000 + (now.tv_usec - philos->time_usec) / 1000;
            printf("%ld  philosopher %d  is thinking now \n", time_now, philos->philo_id);
        }
        change++;
    }
    return (NULL);
}

int ft_create_threads(int num, int time_to_die, int time_to_eat, int time_to_sleep)
{
    pthread_t thread[num];
    t_philosoper philosophers[num];
    struct timeval start;
    struct timeval current;
    struct timeval now;
    pthread_mutex_t *forks;


    forks = malloc(sizeof(pthread_mutex_t) * num);
    gettimeofday(&start, NULL);
    int i;
    i = 0;
    while (i < num)
    {
        philosophers[i].philo_id = i + 1;
        if ((i + 1) == num)
            philosophers[i].left_fork = &forks[0];
        else
            philosophers[i].left_fork = &forks[i + 1];
        philosophers[i].right_fork = &forks[i];
        philosophers[i].time_sec = start.tv_sec;
        philosophers[i].num_of_philos = num;
        philosophers[i].time_usec = start.tv_usec;
        philosophers[i].time_to_die = time_to_die * 1000;
        philosophers[i].time_to_sleep = time_to_sleep * 1000;
        philosophers[i].time_to_eat = time_to_eat * 1000;
        pthread_mutex_init(philosophers[i].left_fork, NULL);
        pthread_mutex_init(philosophers[i].right_fork, NULL);
        if (pthread_create(&thread[i], NULL, test_thread, &philosophers[i]) != 0)
            return (1);
        if (philosophers[i].dead == '1')
            return(1);
       // usleep(100);

        i++;
    }
    i = 0;
    while (i < num)
    {
        if (pthread_join(thread[i], NULL) != 0)
            return (1);
        i++;
    }
    while (i < num)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    return (0);
}

int main(int arc, char **arv)
{
    if (arc == 5)
    {
        if (ft_atoi(arv[1]) == -1)
            return (1);
        if (ft_create_threads(ft_atoi(arv[1]), ft_atoi(arv[2]), ft_atoi(arv[3]), ft_atoi(arv[4])) == 1)
            return (1);
    }
}

