/*
 * event.cpp
 *
 * Created: 3/30/2020 11:39:28 AM
 *  Author: Asus
 */ 


#include "event.hpp"
#include <string.h>



namespace Shrine
{
	
	void DefaultCallbackHandler()
	{
		
	}
	
	
	class EventManager : public ISystem
	{
		
		public:
		EventManager();
		~EventManager() = default;
		
		bool Trigger(UniquePtr<IEvent> event);
		bool Trigger(InterruptHandler handler);
		bool Trigger(TimerHandler handler);
		bool Run();
		
		SharedPtr<ITimer> CreateTimer();
		
		private:
		Fifo<UniquePtr<IEvent>> event_buffer[CONFIG_EVENT_MAX_PRIORITY];
		Fifo<TimerHandler> timer_handler_buffer;
		Fifo<InterruptHandler> interrupt_bufer;
		
		
		
		
	};
	
	
	
	IEvent::IEvent()
	{	
		priority = CONFIG_EVENT_DEFAULT_PRIORITY;	
	}
	
	const uint8_t IEvent::Priority() const
	{
		return priority;
	}
	
	void IEvent::Priority(const uint8_t priority)
	{
		this->priority = priority;
	}
	
	
	
	IEvent::~IEvent()
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
	
	
	SharedPtr<ITimer> EventManager::CreateTimer()
	{
		return TimerInstantiate();
	}
	
	
	bool EventManager::Trigger(UniquePtr<IEvent> event)
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
	bool EventManager::Trigger(TimerHandler handler)
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
						UniquePtr<IEvent> event = event_buffer[i].Pop();
						if (event)
						{
							event->Handler();
						}
					}
				}
			}
		}
		return true;
	}
	
	SharedPtr<EventManager> manager_instance;
	SharedPtr<ISystem> System()
	{
		if (!manager_instance)
		{
			manager_instance = SharedPtr<EventManager>(new EventManager());
		}
		return manager_instance;
	}
	
	
	//SharedPtr<ITimer> begin(SharedPtr<ISystem> & s)
	//{
		//return s->CreateTimer();
	//}
}

