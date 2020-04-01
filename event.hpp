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


namespace Event 
{
	
	
	typedef void (*Callback)();
	
	class Event 
	{
		public:
		Event();
		#ifdef CONFIG_DEBUG_EVENT
		Event(uint16_t event_id, char * event_name);
		#endif // CONFIG_DEBUG_EVENT
		virtual ~Event();
		
		uint8_t & Priority();
		virtual void EventHandler();
		
		
		#ifdef CONFIG_DEBUG_EVENT
		uint16_t & Id();
		char * Name();
		#endif // CONFIG_DEBUG_EVENT
		
		private:
			#ifdef CONFIG_DEBUG_EVENT
			uint16_t id;
			char name[10];
			#endif // CONFIG_DEBUG_EVENT	
			
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
	
	
	class EventManager
	{		
		EventManager();			
		public: 
		
		~EventManager() = default;
		
		bool Trigger(unique_ptr<Event> event);
		bool Trigger(InterruptHandler handler);
		bool Triggar(TimerHandler handler);
		bool Run();
		
		static EventManager & Instance();
		
		private:
		Fifo<unique_ptr<Event>> event_buffer[CONFIG_EVENT_MAX_PRIORITY];
		Fifo<TimerHandler> timer_handler_buffer;
		Fifo<InterruptHandler> interrupt_bufer;
		
		static EventManager manager_instance;
		
		
	};
	 
	
}

#endif /* EVENT_H_ */