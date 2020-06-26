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
#include "timernode.hpp"


namespace Shrine 
{
	
	
	class Timer
	{
		public:
		Timer();
		virtual ~Timer();
		
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
		
		
		
		protected:
		TimerNode node;
	};
	
	void InitializeTimer();
}



#endif /* TIMER_H_ */