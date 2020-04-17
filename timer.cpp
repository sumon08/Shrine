/*
 * timer.cpp
 *
 * Created: 3/30/2020 11:32:15 PM
 *  Author: Asus
 */ 


#include "timer.hpp"
#include "avr_timer.hpp"


#include "event.hpp"
#include "memory.hpp"

namespace Event
{
	
	
	#define TIMER_COUNTER_MAX		0xFFFF
	#define TIMER_COUNTER_MID		0x8000
	
	
	
	void TimerTickHandler();
	void DefaultTimerHandler()
	{
		
	}
	
	
	struct TimerNode
	{
		uint16_t counter;
		TimerCallback func_ptr;
		TimerType type;
		TickType timer_tick;
		TimerStatus status;
		TimerNode * pNext;
	};
	
	
	class Timer : public ITimer
	{
		
		
		
		public:
		
		Timer()
		{
			node = new TimerNode();
			node->pNext = NULL;
			node->func_ptr = DefaultTimerHandler;
			node->status = TimerStatus::STOPPED;
		}
		
		~Timer()
		{
			if (node->status == TimerStatus::RUNNING)
			{
				Stop();
			}
			delete node;
		}
		
		
		
		
		const TimerType Type() const;
		void Type(const TimerType type);
		
		 
		void Callback(TimerCallback callback);
		bool Start();
		bool Stop();
		bool Reset();
		
		
		const TimerStatus Status() const; 
		void Status(const TimerStatus status);
		
		
		
		const TickType Period() const;
		void Period(const TickType & tick);
		
		
		public:
		TimerNode * node;
		
	};
	
	
	
	SharedPtr<ITimer> TimerInstantiate()
	{
		return SharedPtr<Timer>(new Timer());
	}
	
	class TimerManager 
	{
		public:
		TimerManager() 
		{
			pActive = NULL;
			pExpired = NULL;
			pNew = NULL;
			counter = 0;
		}
		
		
		~TimerManager() = default;
		
		public:
		uint16_t counter;
		
		TimerNode * pActive;
		TimerNode * pExpired;
		TimerNode * pNew;
		
	};
	
	
	
	static TimerManager manager;
	
	void InitializeTimer()
	{
		Hardware::TickTimer::Instance()->Initialise(TimerTickHandler);
	}
	
	const TimerStatus Timer::Status() const
	{
		return node->status;
	}
	
	void Timer::Status(const TimerStatus status)
	{
		node->status = status;
	}
	
	
	const TimerType Timer::Type() const
	{
		return node->type;
	}
	
	void Timer::Type(const TimerType type)
	{
		node->type = type;
	}
		
	const TickType Timer::Period() const
	{
		return node->timer_tick;
	}
	void Timer::Period(const TickType & tick)
	{
		node->timer_tick = tick;
	}
	
	
	void Timer::Callback( TimerCallback callback)
	{
		node->func_ptr = callback;
	}
	bool Timer::Start()
	{
		if( !node && node->status != TimerStatus::STOPPED)
			return false;
		
		node->pNext = manager.pNew;
		manager.pNew = node;
		node->status = TimerStatus::RUNNING;
		return true;
	}
	bool Timer::Stop()
	{
		TimerNode * pnode = manager.pActive;
		TimerNode * prev = NULL;
		while(1)
		{
			if(pnode == node)
			{
				if (prev == NULL)
				{
					manager.pActive = pnode->pNext;
				}
				else
				{
					prev->pNext = pnode->pNext;
				}
				node->status = TimerStatus::STOPPED;
				return true;
			}
		}
		return false;
		
	}
	bool Timer::Reset()
	{
		if ( !node || node->status != TimerStatus::RUNNING)
		{
			return false;
		}
		
		TimerNode * pnode = manager.pActive;
		TimerNode * prev = NULL;
		while(1)
		{
			if(pnode == node)
			{
				if (prev == NULL)
				{
					manager.pActive = pnode->pNext;
				}
				else
				{
					prev->pNext = pnode->pNext;
				}
				node->status = TimerStatus::RUNNING;
				node->pNext = manager.pNew;
				manager.pNew = node;
				return true;
			}
		}
		
		return true;
	}
	
	
	
	
	
	void TimerHandlerpvt()
	{
		TimerNode * node = manager.pActive;
		TimerNode * prev = NULL;
		while (node != NULL)
		{
			if (node->counter == manager.counter)
			{
				node->func_ptr();
				if (node->type == TimerType::REPETATIVE)
				{
					uint16_t diff = TIMER_COUNTER_MAX - manager.counter;
					if (diff < node->timer_tick.Tick())
					{
						node->counter = node->timer_tick.Tick() - diff;
					}
					else
					{
						node->counter = node->timer_tick.Tick();
					}
				}
				else
				{
					if(prev == NULL)
					{
						 manager.pActive = node->pNext;
					}
					else
					{
						prev->pNext = node->pNext;
					}
				}
				node = node->pNext;
			}
		}
		
		if (manager.pNew != NULL)
		{
			TimerNode * node;
			
			while(1)
			{
				node = manager.pNew;
				manager.pNew = node->pNext;
				node->pNext = manager.pActive;
				manager.pActive = node;
				uint16_t diff = TIMER_COUNTER_MAX - manager.counter;
				if (diff < node->timer_tick.Tick())
				{
					node->counter = node->timer_tick.Tick() - diff;
				}
				else
				{
					node->counter = node->timer_tick.Tick();
				}
				if (manager.pNew == NULL)
				{
					break;
				}
			}
		}
	}
	
	TimerHandler handler(TimerHandlerpvt);
	
	void TimerTickHandler()
	{
		manager.counter++;
		if (manager.counter == 0xFFFF)
		{
			manager.counter = 0;
		}
		SharedPtr<ISystem> system = System();
		system->Trigger(handler);
	}
}