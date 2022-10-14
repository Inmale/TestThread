#include "Object.h"

void thread_obj::print_data(const std::thread::id subID, const std::thread::id id, const nodeData* data)
{   
    if (data != nullptr)
    {
        std::cout << id << "-->" << subID << ": " << "S= " << data->data << "  " << id << "-->" << subID << ": " << "N= " << data->count << "\n";
    }
}

bool thread_obj::get_completed()
{
    return completed;
}

bool thread_obj::is_valid()
{
    return valid;
}

std::thread::id thread_obj::getID()
{
    return id;
}

nodeData& thread_obj::get_found_data(std::thread::id id)
{
    if (data.size() > 0)
    {
        for (size_t i = 0; i < data.size(); i++)
        {
            if (data[i].id == id)
            {
                nodeData& temp = data[i];
                return temp;
            }
        }
    }
}

void thread_obj::get_random_number()
{ 
     int data = rand() % 1000;
     for (auto& i : subscriptions)
     {
         add_data(i, id, data);
     }
}
////////////////////////////////////////////////////
bool thread_obj::subscribe(thread_obj& subscription)
{
    {
        subscription.subscriptions.emplace_back(*this);
        this->data.emplace_back(subscription.getID());
        return true;
    }
}

bool thread_obj::unsubscribe(thread_obj* subscription)
{
    if (subscription != nullptr)
    {
        subscription->subscriptions.push_back(*this);
        subscription->subscriptions.pop_back();
        return true;
    }
    else
    {
        return false;
    }
}