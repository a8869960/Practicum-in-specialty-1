//
// Created by varsem on 22.10.23.
//
#include "function.h"

static int total = 0;
static pthread_mutex_t total_mutex = PTHREAD_MUTEX_INITIALIZER;

void *process_function(void* arg)
{
    ARGS *pargs = (ARGS*)arg;
    pargs->status = 0;

    int s = func(pargs->filename);

    if(s < 0)
        pargs->status = s;
    else
    {
        pthread_mutex_lock(&total_mutex);
        total += s;
        pthread_mutex_unlock(&total_mutex);
    }
    return 0;
}

int main(int ac, char *av[])
{
    int p = ac - 1;
    pthread_t *threads;

    ARGS *args;

    if(!(args = (ARGS*) malloc(p * sizeof(ARGS))))
    {
        cout << "Not enough memory.";
        return -1;
    }

    //Заполняем аргументы для задач
    for(int i = 0; i < p; i++)
    {
        args[i].filename = av[i + 1];
        args[i].m = i;
        args[i].p = p;
    }

    if(!(threads = (pthread_t*) malloc (p * sizeof(pthread_t))))
    {
        cout << "Not enough memory." << endl;
        return -2;
    }

    for(int i = 0; i < p; i++)
    {
        if(pthread_create(threads + i, 0, process_function, args + i))
        {
            cout << "Cannot create thread " << i << endl;
            return -2;
        }
    }

    for(int i = 0; i < p; i++)
    {
        if(pthread_join(threads[i], 0))
            cout << "Cannot wait thread " << i << endl;
    }

    bool status = true;
    for(int i = 0; i < p; i++)
    {
        if(args[i].status < 0)
            status = false;
    }

    free(threads);
    free(args);

    if(status)
        cout << "Количесво участков постоянсва: " << total << endl;

    return 0;
}