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
static int count_nodes{ 8 };
static int create_number_chanse{ 25 };
static int subscribe_chanse{ 20 };
static int unsubscribe_chanse{ 20 };
static int create_new_node_chanse{ 15 };

void manager();
void node_function(std::thread::id id);
bool new_node();
int random_chance();
bool event_happend(int chance);
void add_data(std::thread::id id_obj, std::thread::id id_data, int value);
