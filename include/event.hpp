/*
 * event.h
 *
 * Created: 3/30/2020 12:53:16 AM
 *  Author: Md. Mahmudul Hasan
 */ 


/*
MIT License

Copyright (c) 2020 Md. Mahmudul Hasan Sumon

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef EVENT_H_
#define EVENT_H_

#include "config.hpp"
#include "fifo.hpp"
#include <stdint.h>
#include "timer.hpp"
#include "list.hpp"
#include "dispatch.hpp"

namespace Shrine 
{
	
	
	typedef void (*Callback)();
	
	enum class EventType
	{
		SIMPLE,
		TIMED,
		STEPPED,
	};
	
	typedef uint16_t EventIndex;
	
	
	class IEvent
	{
		friend class System;
		protected:
		IEvent(EventIndex idx);
		
		
		public:
		virtual ~IEvent();
		const uint8_t Priority() const;
		void Priority(const uint8_t priority);
		DispatcherId Dispatcher(UniquePtr<IDispatcher> dispatcher);
		void Remove(DispatcherId);
		
		
		
		private:
		uint8_t priority;
		EventIndex event_index;
		
	};
	
	
	class ITimedEvent : public IEvent
	{
		public:
		ITimedEvent(EventIndex idx);
		virtual ~ITimedEvent();
		
		const TickType Period();
		void Period(const TickType & period);		
		private:		
		TimerNode timer_node;
	};
	
	struct InterruptHandler
	{
		
		InterruptHandler();
		InterruptHandler(Callback func_ptr);
		~InterruptHandler() = default;
		uint16_t data;
		Callback callback;
		
		void operator()()
		{
			callback();
		}
	};
	
	struct TimerHandler
	{
		TimerHandler();
		TimerHandler(Callback func_ptr);
		~TimerHandler() = default;
		
		// member variable
		Callback callback;
		
		void operator () ()
		{
			callback();
		}
	};
	
	class System
	{
		public:
		System() = default;
		~System() = default;
		
		static System & Instance();
		
		bool Run();
		bool Trigger(UniquePtr<IEvent> event); 
		bool Trigger(InterruptHandler handler); 
		bool Trigger(TimerHandler handler); 	
		
		template<typename T>
		bool Register();
	};


}

#endif /* EVENT_H_ */