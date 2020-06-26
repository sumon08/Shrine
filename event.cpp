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
	
	
	
	template <typename T>
	struct EventIndexer
	{
		static EventIndex event_index;
	};
	
	template<typename T>
	EventIndex EventIndexer<T>::event_index = 0xFFFF;
	


	
	class EventManager
	{
		
		public:
		EventManager();
		~EventManager() = default;
		
		public:
		Fifo<UniquePtr<IEvent>> event_buffer[CONFIG_EVENT_MAX_PRIORITY];
		Fifo<TimerHandler> timer_handler_buffer;
		Fifo<InterruptHandler> interrupt_bufer;
		
		List<UniquePtr<IDispatcher>> dispatcher_list[CONFIG_MAX_NUMBER_OF_EVENT];
	};
	
	EventManager manager_instance;
	
	IEvent::IEvent(EventIndex idx)
	{	
		priority = CONFIG_EVENT_DEFAULT_PRIORITY;
		event_index = idx;
	}
	
	const uint8_t IEvent::Priority() const
	{
		return priority;
	}
	
	void IEvent::Priority(const uint8_t priority)
	{
		this->priority = priority;
	}
	

	DispatcherId IEvent::Dispatcher(UniquePtr<IDispatcher> dispatcher)
	{
		DispatcherId ret = reinterpret_cast<DispatcherId>(dispatcher.get());
		manager_instance.dispatcher_list[event_index].PushBack(move(dispatcher)); 
		return ret;
	}

	void IEvent::Remove(DispatcherId id)
	{
		auto pred = [id](const UniquePtr<IDispatcher> & obj)->bool 
		{
			if(reinterpret_cast<DispatcherId>(obj.get()) == id)
				return true;
				
			return false;
		};
		manager_instance.dispatcher_list[event_index].RemoveIf(pred);
	}

	IEvent::~IEvent()
	{
		
	}
	
	
	
	ITimedEvent::ITimedEvent(EventIndex idx) : IEvent(idx) 
	{
		timer_node.timer_tick = TickType(1000);
		timer_node.status = TimerStatus::STOPPED;
		timer_node.type = TimerType::EVENT;
		timer_node.pNext = NULL;
		
	}
	
	ITimedEvent::~ITimedEvent()
	{
		
	}
	
	const TickType ITimedEvent::Period()  
	{
		return timer_node.timer_tick;
	}
	
	void ITimedEvent::Period(const TickType & period)
	{
		timer_node.timer_tick = period;
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
	
	template<typename T>
	bool Shrine::System::Register()
	{
		return true;
	}

	
	System shrine;
	System & System::Instance()
	{
		return shrine;
	}
	
	bool System::Run()
	{
		
		while(1)
		{
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
							for (size_t i =0; i < manager_instance.dispatcher_list[event->event_index].Size(); i++)
							{
								auto & item = manager_instance.dispatcher_list[event->event_index][i];
								if(item)
									item->Dispatch(event.get());
							}
						}
					}
				}
			}
		}
		return true;
	}
	
	
}

