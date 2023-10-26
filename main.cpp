//
// Created by varsem on 22.10.23.
//
#include "function.h"

int main(int ac, char *av[])
{
    int p = ac - 1;
    pthread_t *threads;

    Status *args;

    if(!(args = (Status*) malloc(p * sizeof(Status))))
    {
        cout << "Not enough memory.";
        free(args);
        return -3;
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
        free(threads);
        free(args);
        return -3;
    }

    for(int i = 0; i < p; i++)
    {
        if(pthread_create(threads + i, 0, process_function, args + i))
        {
            cout << "Cannot create thread " << i << endl;
            free(threads);
            free(args);
            return -4;
        }
    }

    for(int i = 0; i < p; i++)
    {
        if(pthread_join(threads[i], 0))
            cout << "Cannot wait thread " << i << endl;
    }

    bool status = true;
    int res = 0;
    for(int i = 0; i < p; i++)
    {
        if(args[i].status != io_status::success)
        {
            status = false;
            break;
        } else
            res += args[i].result;
    }

    free(threads);
    free(args);

    if(status)
        cout << "Количесво участков постоянсва: " << res << endl;

    return 0;
}