/*
 * event.cpp
 *
 * Created: 3/30/2020 11:39:28 AM
 *  Author: Asus
 */ 


#include "event.hpp"
#include <string.h>



namespace Event
{
	
	void DefaultCallbackHandler()
	{
		
	}
	
	
	Event::Event()
	{
		#ifdef CONFIG_DEBUG_EVENT
		id = CONFIG_DEBUG_EVENT_DEFAULT_ID;
		memset(name, 0, CONFIG_DEBUG_EVENT_NAME_LEGTH);
		#endif // CONFIG_DEBUG_EVENT	
		priority = CONFIG_EVENT_DEFAULT_PRIORITY;	
	}
	
	#ifdef CONFIG_DEBUG_EVENT
	Event::Event(uint16_t event_id, char * event_name)
	{
		id = event_id;
		memset(name, 0, CONFIG_DEBUG_EVENT_NAME_LEGTH);
		strncpy(name, event_name, CONFIG_DEBUG_EVENT_NAME_LEGTH);
		priority = CONFIG_EVENT_DEFAULT_PRIORITY;
	}
	
	#endif // CONFIG_DEBUG_EVENT
	
	
	uint8_t & Event::Priority()
	{
		return priority;
	}
	
	void Event::EventHandler()
	{
		
	}
	
	Event::~Event()
	{
		
	}
	
	
	EventManager::EventManager()
	{
		
	}
	
	
	
	
	InterruptHandler::InterruptHandler()
	{
		callback = DefaultCallbackHandler;
	}
	
	
	InterruptHandler::InterruptHandler(Callback func_ptr)
	{
		callback = func_ptr;
	}
	
	
	TimerHandler::TimerHandler()
	{
		callback = DefaultCallbackHandler;
	}
	
	TimerHandler::TimerHandler(Callback func_ptr)
	{
		callback = func_ptr;
	}
	
	
	EventManager EventManager::manager_instance;
	
	
	EventManager & EventManager::Instance()
	{
		return manager_instance;
	}
	
	
	
	
	bool EventManager::Trigger(unique_ptr<Event> event)
	{
		if (!event || event->Priority() >= CONFIG_EVENT_MAX_PRIORITY)
		{
			return false;
		}
		return event_buffer[event->Priority()].Push(move(event));
		
	}
	bool EventManager::Trigger(InterruptHandler handler)
	{
		return interrupt_bufer.Push(handler);
	}
	bool EventManager::Triggar(TimerHandler handler)
	{
		return timer_handler_buffer.Push(handler);
	}
	
	
	bool EventManager::Run()
	{
		while(1)
		{
			if (interrupt_bufer.Length() > 0)
			{
				InterruptHandler handle = interrupt_bufer.Pop();
				handle();
			}
			else if(timer_handler_buffer.Length() > 0)
			{
				TimerHandler handle = timer_handler_buffer.Pop();
				handle();
			}
			else
			{
				for (int i = 0; i < CONFIG_EVENT_MAX_PRIORITY; i++)
				{
					if (event_buffer[i].Length() > 0)
					{
						unique_ptr<Event> event = event_buffer[i].Pop();
						event->EventHandler();
						break;
					}
				}
			}
		}
		return true;
	}
}