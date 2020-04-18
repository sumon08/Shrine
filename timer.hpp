/*
 * timer.h
 *
 * Created: 3/30/2020 2:32:09 AM
 *  Author: Asus
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


#ifndef TIMER_H_
#define TIMER_H_


#include "ticktype.hpp"
#include "memory.hpp"


namespace Shrine 
{
	typedef void (*TimerCallback)();
	
	enum class TimerType
	{
		ONE_SHOT,
		REPETATIVE
	};
	
	
	enum class TimerStatus
	{
		RUNNING,
		STOPPED,
		EXPIRED
	};
	
	class ITimer 
	{
		public:
		ITimer() = default;
		virtual ~ITimer() = default;
		
		virtual const TimerType Type() const = 0;
		virtual void Type(const TimerType type) = 0;
		
		virtual const TickType Period() const = 0;
		virtual void Period(const TickType & tick) = 0;
		
		virtual void Callback(TimerCallback callback) = 0;		
		virtual bool Start() = 0;
		virtual bool Stop() = 0;
		virtual bool Reset() = 0;
		
		
		virtual const TimerStatus Status() const = 0;
		virtual void Status(const TimerStatus status) = 0;
				
	};
	
	
	void InitializeTimer();
	SharedPtr<ITimer> TimerInstantiate();
}



#endif /* TIMER_H_ */