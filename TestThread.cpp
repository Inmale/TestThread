// TestThread.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include "Object.h"

using namespace std;
using namespace chrono_literals;

mutex mut;
condition_variable cv;
static bool finished{false};
static int count_nodes{8};
vector<thread> nodes;
vector<thread_obj> objects;

void manager(size_t length)
{
	while (finished)
	{
		this_thread::sleep_for(100ms);
		for (auto& i : objects)
		{
			if (i.get_completed())
			{
				lock_guard<mutex> lm{ mut };
				objects.push_back(i);
				objects.pop_back();
			}
		}
		if (objects.size() == 0)
		{
			finished = true;
		}
	}
};

void node_function(int create_number = 25, int sub_event = 20, int unsub_event = 15, int create_node = 15, int nothing = 25)
{
	thread_obj object = thread_obj();

	while (!object.get_completed())
	{

	}
}

int main()
{
	thread nodes_manager(manager, nodes.size());

	for (int i = 0; i < count_nodes; i++)
	{
		nodes.emplace_back();
	}
	//Run
	nodes_manager.join();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
