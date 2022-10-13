#pragma once

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

static  std::mutex m;
static bool finished{ false };
static int count_nodes{ 8 };
static int create_number_chanse{ 25 };
static int subscribe_chanse{ 20 };
static int unsubscribe_chanse{ 20 };
static int create_new_node_chanse{ 15 };