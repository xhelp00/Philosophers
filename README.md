# Philosophers
I never thought philosophy would be so deadly
## New concepts
- Threads
- Mutexes
- Data races
- Posix semaphores
## Allowed args
- number_of_philosophers 
- time_to_die 
- time_to_eat 
- time_to_sleep 
- [number_of_times_each_philosopher_must_eat]
## Allowed externals
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

## Study
great playlist about Threads https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
-pthread needs to be added as link option to cc
-pthread_join function is kind of "wait" for threads

## LL
- executable files compiled on Linux are failing to run on Mac (zsh: exec format error:)
