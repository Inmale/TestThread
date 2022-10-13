﻿// TestThread.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Object.h"

using namespace std;
using namespace chrono_literals;

mutex mut;
condition_variable cv;
vector<thread> nodes;
vector<thread_obj> objects;

void manager(size_t length)
{
	while (!finished)
	{
		//delay
		this_thread::sleep_for(100ms);
		//delete object if completed
		for (auto& i : objects)
		{
			if (i.get_completed())
			{
				lock_guard<mutex> lm{ mut };
				objects.push_back(i);
				objects.pop_back();
			}
		}
		if (objects.size() < 2)
		{
			finished = true;
		}
	}
}

void node_function(size_t id)
{
	thread_obj object = thread_obj(id);
	objects.emplace_back(object);

	while (!object.get_completed())
	{
		cout << object.getID() << "\n";
		this_thread::sleep_for(1000ms);
	}
}

int random_chance()
{
	return int(rand() % 100 + 1);
}

bool event_happend(int chance)
{
	if (random_chance() < chance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

thread_obj& get_random_object()
{
	size_t i = (rand() % (objects.size()));
	return objects[i];
}

int main()
{
	thread nodes_manager(manager, nodes.size());

	for (int i = 0; i < count_nodes; i++)
	{
		nodes.emplace_back(node_function, i);
	}
	//Run
	nodes_manager.join();
	for (auto& i : nodes)
	{
		i.join();
	}
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
