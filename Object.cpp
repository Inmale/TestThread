#include "Object.h"

void thread_obj::print_data(const size_t subID, const size_t id, nodeData& data)
{   
     std::cout << id << "-->" << subID << ": " << "S= " << data.data << "  " << id << "-->" << subID << ": " << "N= " << data.count << "\n";
}

bool thread_obj::get_completed()
{
    return completed;
}

bool thread_obj::is_valid()
{
    return valid;
}

size_t thread_obj::getID()
{
    return id;
}

nodeData& thread_obj::get_found_data(size_t id)
{
    if (data.size() > 0)
    {
        const auto pred([&](nodeData& i) {return i.id == id; });
        const auto temp(std::find_if(std::begin(data), std::end(data), pred));
        return *temp;
    }
}

void thread_obj::get_random_number()
{ 
     int data = rand() % 1000;
     for (auto& i : subscriptions)
     {
         add_data(i, id, data);
         print_data(i, id, get_data_object(i, id));
     }
}

bool thread_obj::subscribe(thread_obj& subscription)
{
        add_sub_data(subscription, *this);
        return true;
}

void thread_obj::unsubscribe(thread_obj& subscription)
{
    size_t id;
    if (data.size() > 0)
    {
        const auto _end(std::end(data));
        id = _end->id;
        data.erase(_end);
        remove_subscriber(this->getID(),id);
    }
}