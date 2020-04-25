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
	
	
	class EventManager
	{
		
		public:
		EventManager();
		~EventManager() = default;
		
		public:
		Fifo<UniquePtr<IEvent>> event_buffer[CONFIG_EVENT_MAX_PRIORITY];
		Fifo<TimerHandler> timer_handler_buffer;
		Fifo<InterruptHandler> interrupt_bufer;
	};
	
	EventManager manager_instance;
	
	IEvent::IEvent()
	{	
		priority = CONFIG_EVENT_DEFAULT_PRIORITY;
		event_type = EventType::SIMPLE;
	}
	
	const uint8_t IEvent::Priority() const
	{
		return priority;
	}
	
	void IEvent::Priority(const uint8_t priority)
	{
		this->priority = priority;
	}
	
	const EventType IEvent::Type() const
	{
		return event_type;
	}
	
	IEvent::~IEvent()
	{
		
	}
	
	
	void TimedEventTimeoutCallback()
	{
		
	}
	
	ITimedEvent::ITimedEvent() 
	{
		event_type = EventType::TIMED;
		event_timer.Period(TickType(1000));
		event_timer.Type(TimerType::REPETATIVE);
		event_timer.Callback(TimedEventTimeoutCallback);
	}
	
	ITimedEvent::~ITimedEvent()
	{
		
	}
	
	const TickType ITimedEvent::Period()  
	{
		return event_timer.Period();
	}
	
	void ITimedEvent::Period(const TickType & period)
	{
		event_timer.Period(period); 
	}
	
	void ITimedEvent::StartTimer()
	{
		event_timer.Start();
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
	
	
	
	bool System::Trigger(UniquePtr<IEvent> event)
	{
		if (!event || event->Priority() >= CONFIG_EVENT_MAX_PRIORITY)
		{
			return false;
		}
		return manager_instance.event_buffer[event->Priority()].Push(move(event));
		
	}
	bool System::Trigger(InterruptHandler handler)
	{
		return manager_instance.interrupt_bufer.Push(handler);
	}
	bool System::Trigger(TimerHandler handler)
	{
		return manager_instance.timer_handler_buffer.Push(handler);
	}
	
	System shrine;
	System & System::Instance()
	{
		return shrine;
	}
	
	bool System::Run()
	{
		
		// while(1)
		// {
			if (manager_instance.interrupt_bufer.Length() > 0)
			{
				InterruptHandler handle = manager_instance.interrupt_bufer.Pop();
				handle();
			}
			else if(manager_instance.timer_handler_buffer.Length() > 0)
			{
				TimerHandler handle = manager_instance.timer_handler_buffer.Pop();
				handle();
			}
			else
			{
				for (int i = 0; i < CONFIG_EVENT_MAX_PRIORITY; i++)
				{
					if (manager_instance.event_buffer[i].Length() > 0)
					{
						UniquePtr<IEvent> event = manager_instance.event_buffer[i].Pop();
						if (event)
						{
							event->Handler();
							if (event->Type() == EventType::TIMED)
							{
								ITimedEvent * e = static_cast<ITimedEvent *>( event.get());								
								e->StartTimer();
							}
						}
					}
				}
			}
		// }
		return true;
	}
	
	
}

