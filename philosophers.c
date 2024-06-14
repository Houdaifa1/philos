#include "philosophers.h"

void *test_thread(void *philo)
{
    t_philosoper *philos = (t_philosoper *)philo;
    int i = 0;

    if (philos->philo_id % 2 == philos->change)
    {
        pthread_mutex_lock(&philos->right_fork);
        printf("%ld  philosopher %d  has taking a fork \n", philos->time, philos->philo_id);
        pthread_mutex_lock(&philos->left_fork);
        printf("%ld  philosopher %d  is eating now \n", philos->time, philos->philo_id);
        philos->eat = 1;
        i = 1;
        pthread_mutex_unlock(&philos->right_fork);
        pthread_mutex_unlock(&philos->left_fork);
        if (i == 1)
                usleep(200000);
    }
    else
    {
        printf("%ld  philosopher %d  is sleeping now \n", philos->time, philos->philo_id);
        if (philos->time_to_die < 200000 + 120000)
            philos->lah_irhmo = 1;
        else
            usleep(100000);
    }
    return (NULL);
}

int ft_create_threads(int num)
{
    pthread_t thread[num];
    t_philosoper philosophers[num];
    pthread_mutex_t forks[num];
    struct timeval start;
    struct timeval current;
    struct timeval now;

    gettimeofday(&start, NULL);
    int i;
    i = 0;
    int change = 0;
    while (1)
    {
        if (i == num)
        {
            i = 0;
            while (i < num)
            {
                if (pthread_join(thread[i], NULL) != 0)
                    return (1);
                i++;
            }
            i = 0;
            change++;
        }
        philosophers[i].philo_id = i + 1;
        if ((i + 1) == num)
            philosophers[i].left_fork = forks[0];
        else
            philosophers[i].left_fork = forks[i + 1];
        philosophers[i].right_fork = forks[i];
        philosophers[i].change = change % 2;
        gettimeofday(&current, NULL);
        long seconds = current.tv_sec - start.tv_sec;
        long micro = current.tv_usec - start.tv_usec;
        philosophers[i].time_before = seconds * 1000 + (micro / 1000);
        philosophers[i].time = seconds * 1000 + (micro / 1000);
        philosophers[i].time_to_die = 310 * 1000;
        philosophers[i].lah_irhmo = 0;
        pthread_mutex_init(&philosophers[i].left_fork, NULL);
        pthread_mutex_init(&philosophers[i].right_fork, NULL);
        philosophers[i].eat = 0;
        if (pthread_create(&thread[i], NULL, test_thread, &philosophers[i]) != 0)
            return (1);
        usleep(100);
        if (philosophers[i].lah_irhmo == 1)
        {
            usleep(philosophers[i].time_to_die);
            gettimeofday(&now, NULL);
            printf("%ld  philosopher %d  is dead \n", ((now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec) / 1000), philosophers[i].philo_id);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < num)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    return (0);
}

int main(int arc, char **arv)
{
    if (arc == 2)
    {
        if (ft_atoi(arv[1]) == -1)
            return (1);
        if (ft_create_threads(ft_atoi(arv[1])) == 1)
            return (1);
    }
}
