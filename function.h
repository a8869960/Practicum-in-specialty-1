//
// Created by varsem on 22.10.23.
//
#include <cstdio>
#include <iostream>

using namespace std;

int func(char *filename);
void *process_function(void* fn);

enum class io_status
{
    success,
    error_open,
    error_read,
    none
};

class Status
{
public:
    char *filename = nullptr;
    int m = 0;
    int p = 0;

    int result = 0;
    io_status status = io_status::none;
};
