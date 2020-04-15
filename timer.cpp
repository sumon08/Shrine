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
		SharedPtr<TimerNode> pNext; // need to be a weal_ptr here. Must need to careful with self reference.
	};
	
	
	class Timer : public ITimer
	{
		
		
		
		public:
		
		Timer()
		{
			node->pNext = NULL;
			node->func_ptr = DefaultTimerHandler;
		}
		
		
		
		
		TimerType & Type();
		void Callback(TimerCallback callback);
		bool Start();
		bool Stop();
		bool Reset();
		TimerStatus & Status();
		
		public:
		SharedPtr<TimerNode> node;
		
	};
	
	
	
	
	
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
		uint16_t counter;
		
		SharedPtr<TimerNode> pActive;
		SharedPtr<TimerNode> pExpired;
		SharedPtr<TimerNode> pStopped;
		
	};
	
	static TimerManagerPrivate manager;
	
	TimerStatus & Timer::Status()
	{
		return node->status;
	}
	
	
	TimerType & Timer::Type()
	{
		return node->type;
	}
	void Timer::Callback( TimerCallback callback)
	{
		node->func_ptr = callback;
	}
	bool Timer::Start()
	{
		bool ret = false;
		if(node->status != TimerStatus::STOPPED)
			return false;
			
		if (!manager.pActive)
		{
			manager.counter = 0;
			manager.pActive = node;
			node->status = TimerStatus::RUNNING;
			return true;
		}
		
		if(manager.counter == 0)
		{
			SharedPtr<TimerNode> pnode = manager.pActive;
			SharedPtr<TimerNode> prev_node;
			while(1)
			{
				if (node->counter < pnode->counter)
				{
					node->pNext = pnode;
					if(!prev_node)
					{
						manager.pActive = node;
					}
					else
					{
						prev_node->pNext = node;
					}
					return true;
				}
				else
				{
					prev_node = pnode;
					pnode= pnode->pNext;
				}
			}
		}
		
		SharedPtr<TimerNode> segment = manager.pActive;
		while(1)
		{
			if(segment->counter < manager.counter)
				break;
			else
				segment = segment->pNext;
		}

		uint16_t diff = TIMER_COUNTER_MAX - manager.counter;
		if(diff > node->timer_tick.Tick())
		{
			node->counter = manager.counter + node->timer_tick.Tick();
			SharedPtr<TimerNode> pnode = manager.pActive;
			SharedPtr<TimerNode> prev;
			while(pnode)
			{
				if(node->counter < node->counter)
				{
					node->pNext = manager.pActive;
					manager.pActive = node;
				}
				else
				{
					if(pnode->counter < manager.counter)
					{
						if(prev)
						{
							node->pNext = pnode;
							prev->pNext = node;
							break;
						}
					}
				}
				prev = pnode;
				pnode = node->pNext;
			}
		}
		else
		{
			node->counter = node->timer_tick.Tick() - diff;
		}
		return ret;
	}
	bool Timer::Stop()
	{
		return true;
		
	}
	bool Timer::Reset()
	{
		return true;
	}
	
	
	
	

	
	
	
	
	
	
	ITimer * TimerManagerPrivate::Create()
	{
		Timer * tb = new Timer();
		return (ITimer *)tb;
	}
	
	
	
	
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
		if (manager.pExpired)
		{
			SharedPtr<TimerNode> tb = manager.pExpired;
			while(tb)
			{
				tb->func_ptr();
				if(tb->type == TimerType::REPETATIVE)
				{
					//tb->Start();
				}
			}
		}
	}
	
	void TimerTickHandler()
	{
		manager.counter++;
		if (manager.counter == 0xFFFF)
		{
			manager.counter = 0;
		}
		
		if (manager.pActive)
		{
			SharedPtr<TimerNode> tb = manager.pActive;
			while(tb)
			{
				if (tb->counter == manager.counter)
				{
					SharedPtr<TimerNode> ttb = tb;
					ttb->pNext = manager.pExpired;
					manager.pExpired = ttb;
					tb = tb->pNext;
				}
				else
				{
					break;
				}
			}
			
			if (manager.pExpired)
			{
				TimerHandler handler;
				handler.callback = TimerHandlerpvt;
				EventManager &evm = EventManager::Instance();
				evm.Triggar(handler);
			}
		}
	}
}