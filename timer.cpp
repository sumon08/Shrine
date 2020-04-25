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

namespace Shrine
{
	
	
	#define TIMER_COUNTER_MAX		0xFFFF
	
	
	
	void TimerTickHandler();
	void DefaultTimerHandler()
	{
		
	}
	
	//
	//struct TimerNode
	//{
		//uint16_t counter;
		//TimerCallback func_ptr;
		//TimerType type;
		//TickType timer_tick;
		//TimerStatus status;
		//TimerNode * pNext;
	//};
	
	
	class TimerManager 
	{
		public:
		TimerManager() 
		{
			pActive = NULL;
			counter = 0;
		}		
		~TimerManager() = default;
		
		
		public:
		uint16_t counter;		
		TimerNode * pActive;
		
	};
	
	
	
	static TimerManager manager;
	
	void InitializeTimer()
	{
		Hardware::TickTimer::Instance()->Initialise(TimerTickHandler);
	}
	
	Timer::Timer()
	{
		node.pNext = NULL;
		node.func_ptr = DefaultTimerHandler;
		node.status = TimerStatus::STOPPED;
		node.type = TimerType::ONE_SHOT;
	}
	
	
	bool TimerNode::Start()
	{
		if(status != TimerStatus::STOPPED)
		return false;
		
		pNext = manager.pActive;
		manager.pActive = this;
		
		uint16_t diff = TIMER_COUNTER_MAX - manager.counter;
		
		if(diff > timer_tick.Tick())
		{
			counter = manager.counter + timer_tick.Tick();
		}
		else
		{
			counter = timer_tick.Tick() - diff;
		}
		
		status = TimerStatus::RUNNING;
		return true;
	}
	
	bool TimerNode::Stop()
	{
		TimerNode * pnode = manager.pActive;
		TimerNode * prev = NULL;
		while(1)
		{
			if(pnode == this)
			{
				if (prev == NULL)
				{
					manager.pActive = pnode->pNext;
				}
				else
				{
					prev->pNext = pnode->pNext;
				}
				status = TimerStatus::STOPPED;
				return true;
			}
		}
		return false;
	}
	
	bool TimerNode::Reset()
	{
		if (Stop())
		{
			return Start();
		}
		return false;
	}
	
	
	
	Timer::~Timer()
	{
		if (node.status == TimerStatus::RUNNING)
		{
			Stop();
		}
	}
	
	
	
	
	const TimerStatus Timer::Status() const
	{
		return node.status;
	}
	
	void Timer::Status(const TimerStatus status)
	{
		node.status = status;
	}
	
	
	const TimerType Timer::Type() const
	{
		return node.type;
	}
	
	void Timer::Type(const TimerType type)
	{
		node.type = type;
	}
		
	const TickType Timer::Period() const
	{
		return node.timer_tick;
	}
	void Timer::Period(const TickType & tick)
	{
		node.timer_tick = tick;
	}
	
	
	void Timer::Callback( TimerCallback callback)
	{
		node.func_ptr = callback;
	}
	bool Timer::Start()
	{
		return node.Start();
	}
	bool Timer::Stop()
	{
		return node.Stop();
		
	}
	bool Timer::Reset()
	{
		return node.Reset();
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
				if (node->type != TimerType::ONE_SHOT)
				{
					uint16_t diff = TIMER_COUNTER_MAX - manager.counter;
					if (diff < node->timer_tick.Tick())
					{
						node->counter = node->timer_tick.Tick() - diff;
					}
					else
					{
						node->counter = node->timer_tick.Tick() + manager.counter;
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
					node->status = TimerStatus::STOPPED;
				}
			}
			prev = node;
			node = node->pNext;
		}
	}
	
	TimerHandler handler(TimerHandlerpvt);
	
	void TimerTickHandler()
	{
		manager.counter++;
		System system = System::Instance();
		system.Trigger(handler);
	}
}