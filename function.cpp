//
// Created by varsem on 22.10.23.
//
#include "function.h"
#define eps 1e-16

int func(char *filename)
{
    FILE *f;

    f = fopen(filename, "r");
    if(!f)
    {
        cout << "Can't open the file " << filename << endl;
        return -1;
    }

    double current, next;

    if(fscanf(f, "%lf", &current) == -1)
    {
        fclose(f);
        return 0;
    }

    int count = 0;
    bool flag = false;

    while(fscanf(f, "%lf", &next) == 1)
    {
        if(abs(current - next) >= eps)
        {
            current = next;
            flag = false;
        } else
        {
            if(!flag)
            {
                count++;
                flag = true;
            }
        }

    }

    if(fscanf(f, "%lf", &next) != EOF)
    {
        cout << "Wrong input data in " << filename << endl;
        fclose(f);
        return -2;
    }

    fclose(f);

//    cout << "COUNT " << count << endl;

    return count;
}

void *process_function(void* arg)
{
    Status *st = (Status*)arg;

    int s = func(st->filename);

    if(s == -1)
        st->status = io_status::error_open;
    else if(s == -2)
        st->status = io_status::error_read;
    else
    {
        st->result = s;
        st->status = io_status::success;
    }
    return 0;
}