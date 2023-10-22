//
// Created by varsem on 22.10.23.
//
#include "function.h"

static int total = 0;
static pthread_mutex_t total_mutex = PTHREAD_MUTEX_INITIALIZER;

void *process_function(void* fn)
{
    char *filename = (char*) fn;

    int s = func(filename);

    pthread_mutex_lock(&total_mutex);
    total += s;
    pthread_mutex_unlock(&total_mutex);

    return 0;
}

int main(int ac, char *av[])
{
    int p = ac - 1;
    pthread_t *threads;

    if(!(threads = (pthread_t*) malloc (p * sizeof(pthread_t))))
    {
        cout << "Not enough memory." << endl;
        return -2;
    }

    for(int i = 0; i < p; i++)
    {
        if(pthread_create(threads + i, 0, process_function, (void*)av[i + 1]))
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

    free(threads);

    cout << total << endl;

    return 0;
}