/*
 * timer.cpp
 *
 * Created: 3/30/2020 11:32:15 PM
 *  Author: Asus
 */ 


#include "timer.hpp"
#include "avr_timer.hpp"


#include "event.hpp"

namespace Event
{
	void DefaultTimerHandler()
	{
		
	}
	
	
	
	class TimerBase : public ITimer
	{
		
		
		struct TimerNode
		{
			uint16_t upper_count;
			uint16_t lower_count;
			TimerBase * pNext;
		};
		
		public:
		
		TimerBase()
		{
			node.pNext = NULL;
			func_ptr = DefaultTimerHandler;
		}
		
		
		
		
		ITimer * Clone();
		TimerType & Type();
		void Callback(TimerCallback callback);
		bool Start();
		bool Stop();
		bool Reset();
		void Release();
		
		public:
		uint8_t count;
		TimerCallback func_ptr;
		TimerType type;
		TickType timer_tick;
		TimerNode node;
		
	};
	
	
	TimerType & TimerBase::Type()
	{
		return type;
	}
	void TimerBase::Callback( TimerCallback callback)
	{
		func_ptr = callback;
	}
	bool TimerBase::Start()
	{
		return true;
	}
	bool TimerBase::Stop()
	{
		return true;
		
	}
	bool TimerBase::Reset()
	{
		return true;
	}
	
	ITimer *  TimerBase::Clone()
	{
		count++;
		return  (ITimer *)this;
	}
	
	
	void TimerBase::Release()
	{
		count--;
	}
	
	
	void TimerTickHandler();
	
	
	
	
	
	class TimerManagerPrivate : public TimerManager
	{
		public:
		TimerManagerPrivate() : tick_timer(Hardware::TickTimer::Instance())
		{
			tick_timer->Initialise(TimerTickHandler);
		}
		
		
		~TimerManagerPrivate() = default;
		ITimer * Create();
		
		public:
		Hardware::TickTimer * tick_timer;
		uint16_t upper_counter;
		uint16_t lower_counter;
		
		TimerBase * pActive;
		TimerBase * pExpired;
		
	};
	
	
	ITimer * TimerManagerPrivate::Create()
	{
		TimerBase * tb = new TimerBase();
		return (ITimer *)tb;
	}
	
	
	static TimerManagerPrivate manager;
	
	TimerManager * TimerManager::Instance()
	{
		return & manager;
	}
	
	TimerManager::TimerManager()
	{
		
	}
	
	
	bool TimerManager::Initialise()
	{
		return true;
	}
	
	void TimerHandlerpvt()
	{
		if (manager.pExpired != NULL)
		{
			TimerBase * tb = manager.pExpired;
			while(tb != NULL)
			{
				tb->func_ptr();
				if(tb->type == TimerType::REPETATIVE)
				{
					tb->Start();
				}
			}
		}
	}
	
	void TimerTickHandler()
	{
		manager.lower_counter++;
		if (manager.lower_counter == 0xFFFF)
		{
			manager.lower_counter = 0;
			manager.upper_counter++;
		}
		
		if (manager.pActive !=NULL)
		{
			TimerBase * tb = manager.pActive;
			while(tb != NULL)
			{
				if (tb->node.upper_count == manager.upper_counter && tb->node.lower_count == manager.lower_counter)
				{
					TimerBase * ttb = tb;
					ttb->node.pNext = manager.pExpired;
					manager.pExpired = ttb;
					tb = tb->node.pNext;
				}
				else
				{
					break;
				}
			}
			
			if (manager.pExpired != NULL)
			{
				TimerHandler handler;
				handler.callback = TimerHandlerpvt;
				EventManager &evm = EventManager::Instance();
				evm.Triggar(handler);
			}
		}
	}
}