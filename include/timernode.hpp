/*
 * timernode.h
 *
 * Created: 4/21/2020 1:56:01 PM
 *  Author: Asus
 */ 


#ifndef TIMERNODE_H_
#define TIMERNODE_H_


namespace Shrine
{
	
	typedef void (*TimerCallback)();
	
	
	enum class TimerType
	{
		ONE_SHOT,
		REPETATIVE,
		EVENT
	};
	
	
	enum class TimerStatus
	{
		RUNNING,
		STOPPED,
		EXPIRED
	};
	
	struct TimerNode
	{
		uint16_t counter;
		TimerCallback func_ptr;
		TimerType type;
		TickType timer_tick;
		TimerStatus status;
		TimerNode * pNext;
		
		inline bool Start();
		inline bool Stop();
		inline bool Reset();
	};
	
	
	
}


#endif /* TIMERNODE_H_ */