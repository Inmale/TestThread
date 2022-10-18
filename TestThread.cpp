// TestThread.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Object.h"

using namespace std;
using namespace chrono_literals;

mutex q_mut;

condition_variable cv;
vector<thread> nodes;
vector<thread_obj> objects;

void manager()
{
	int con{ 0 };
	while (!finished)
	{
		//delay
		this_thread::sleep_for(1000ms);

		//delete object if completed
		con = 0;
		for (auto& ob : objects)
		{
			if (ob.get_completed())
			{
				con++;
			}
		}
		if (con > count_nodes - 2)
		{
			finished = true;
		}
	}
	cout << "Simulation completed\n";
}

size_t get_new_free_id()
{
	if (objects.size() > 0)
	{
		for (size_t id = 0; id < 100; id++)
		{
			bool finded = false;
			for (auto& i : objects)
			{
				if (i.getID() == id)
				{
					finded = true;
					break;
				}
			}
			if(!finded)
			{
				return id;
			}
		}
	
	}
	else
	{
		return 0;
	}
}

void run(thread_obj& ob)
{
	bool run{true};
	unique_lock<mutex> lock{ q_mut };
	cv.wait(lock, [&]() {return run; });
	if (event_happend(create_number_chanse))
	{
		ob.get_random_number();
	}
	if (event_happend(subscribe_chanse))
	{
		ob.subscribe(get_random_object());
	}
	if (event_happend(unsubscribe_chanse))
	{
		ob.unsubscribe();
	}
	run = false;
}

void node_function(size_t id)
{
	thread_obj& object = get_id_object(id);
	while (!object.get_completed())
	{
		run(object);
		this_thread::sleep_for(500ms);
		if (object.data.size() == 0)
		{
			object.completed_obj();
			break;
		}
	}
}

void add_data(size_t id_obj, size_t id_data, int value)
{
	nodeData& data (get_data_object(id_obj, id_data));					
	{
		data.data += value;
		data.count++;
	}
}


thread_obj& get_random_object()
{
	if(objects.size() != 0)
	{
		size_t i = (rand() % (objects.size()));
		thread_obj& temp = objects[i];
		return temp;
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

thread_obj& get_sub_object(size_t id)
{
	if (objects.size() > 1)
	{
		thread_obj& temp = get_random_object();
		
		if (temp.is_valid())
		{
			if (temp.getID() != id)
			{
				return temp;
			}
			else
			{
				return get_sub_object(id);
			}
		}
		
	}
}
thread_obj& get_id_object(size_t id)
{
	const auto pred([&](thread_obj& i) {return i.getID() == id; });
	const auto found_obj(find_if(begin(objects), end(objects), pred));
	if (found_obj == objects.end())
	{
		create_object(id);
	}
	return *found_obj;
}

nodeData& get_data_object(size_t id_ob, size_t id_data)
{
	const auto pred_data([&](nodeData& j) {return j.id == id_data; });
	auto& temp (get_id_object(id_ob));
	const auto found_data(find_if(begin(temp.data), end(temp.data), pred_data));
	return *found_data;
}

void create_object(size_t id)
{
	objects.emplace_back(id);
}

void remove_subscriber(size_t id_subscriber, size_t id_subscription)
{
	thread_obj& temp(get_id_object(id_subscription));

	const auto pred([&](size_t& id) {return id == id_subscriber; });
	const auto found_obj(remove_if(begin(temp.subscriptions), end(temp.subscriptions), pred));
	temp.subscriptions.erase(found_obj, end(temp.subscriptions));
}

void remove_object(size_t id)
{
	lock_guard<mutex> mt{ q_mut };
	auto pred([&](thread_obj& i) {return i.getID() == id; });
	const auto new_end(remove_if(begin(objects), end(objects), pred));
	objects.erase(new_end, objects.end());
}

void add_sub_data(thread_obj& subscription, thread_obj& subscriber)
{
	auto pred([&](size_t& id) {return id == subscriber.getID(); });
	auto found_id(find_if(begin(subscription.subscriptions), end(subscription.subscriptions), pred));
	if (found_id == end(subscription.subscriptions))
	{
		subscription.subscriptions.emplace_back(subscriber.getID());
		subscriber.data.emplace_back(subscription.getID());
	}
}

int main()
{
	int nods, data, sub, unsub;
	cout << "Enter count nodes(2...99):\n";
	cin >> nods;
	if (nods < 100 || nods > 1)
	{
		count_nodes = nods;
	}
	cout << "Enter chanse to create data(1...99):\n";
	cin >> data;
	if (data < 100 || data > 0)
	{
		create_number_chanse = data;
	}
	cout << "Enter chanse to subscribe(1...99):\n";
	cin >> sub;
	if (sub < 100 || sub > 0)
	{
		subscribe_chanse = sub;
	}
	cout << "Enter chanse to unsubscribe(1...99):\n";
	cin >> unsub;
	if (unsub < 100 || unsub > 0)
	{
		unsubscribe_chanse = unsub;
	}
	thread nodes_manager(manager);

	for (size_t i = 0; i < count_nodes; i++)
	{
		objects.emplace_back(i);
		nodes.emplace_back(node_function, i);
	}
	for (auto& i : objects)
	{
		i.subscribe(get_random_object());
	}
	//Run
	for (auto& i : nodes)
	{
		i.detach();
	}
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
