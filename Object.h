#pragma once
#include <random>

class thread_obj
{
bool completed{ false };

public:
	int v1 = rand();
	thread_obj() {};

	bool get_completed();

	int random_chance();

	int get_random_number();
};