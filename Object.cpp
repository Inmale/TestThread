#include "Object.h"

bool thread_obj::get_completed()
{
    return completed;
}

int thread_obj::random_chance()
{
    return int(rand() % 100 + 1);
}

int thread_obj::get_random_number()
{
    return rand();
}
