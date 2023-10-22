//
// Created by varsem on 22.10.23.
//
#include <cstdio>
#include <iostream>

using namespace std;

int func(char *filename);
void *process_function(void* fn);

typedef struct _ARGS
{
    char *filename;
    int m;
    int p;

    int status;
} ARGS;
