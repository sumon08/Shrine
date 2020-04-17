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


namespace Event 
{
	
	
	typedef void (*Callback)();
	
	class IEvent
	{
		public:
		IEvent();
		virtual ~IEvent();
		const uint8_t Priority() const;
		void Priority(const uint8_t priority);
		
		virtual void EventHandler() = 0;
		
		private:
		uint8_t priority;
		
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
	
	
	
	class ISystem
	{
		public:
		ISystem() = default;
		virtual ~ISystem() = default;
		
		virtual bool Run() = 0;
		virtual bool Trigger(UniquePtr<IEvent> event) = 0; 
		virtual bool Trigger(InterruptHandler handler) = 0; 
		virtual bool Trigger(TimerHandler handler) = 0; 
		
		virtual SharedPtr<ITimer> CreateTimer() = 0;
		
	};
	
	
	SharedPtr<ISystem> System();
	
	
	
}

#endif /* EVENT_H_ */