#pragma once

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <memory>
#include <algorithm>

static  std::mutex m;
static bool finished{ false };
static int count_nodes{ 10 };
static int create_number_chanse{ 25 };
static int subscribe_chanse{ 20 };
static int unsubscribe_chanse{ 10 };

void manager();
size_t get_new_free_id();
void node_function(size_t id);
void add_data(size_t id_obj, size_t id_data, int value);
int random_chance();
bool event_happend(int chance);
