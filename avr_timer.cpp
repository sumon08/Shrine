/*
 * avr_timer.cpp
 *
 * Created: 3/31/2020 2:10:52 PM
 *  Author: Asus
 */ 


#include <avr/interrupt.h>
#include <avr/io.h>

#include "avr_timer.hpp"

namespace Hardware
{
	TickTimer timer; 
	
	void DefaultHandler()
	{
		
	}
	TickTimer::TickTimer()
	{
		timer_handler = DefaultHandler;
	}
	
	TickTimer::~TickTimer()
	{
		
	}
	
	bool TickTimer::Initialise(TickTimerHandler handler)
	{
		cli();
		if (handler == 0)
			timer_handler = DefaultHandler;
		else
			timer_handler = handler;
		
		//Timer0 is used to create 5ms 		
		OCR0 = 0x35;
		TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS00);
		TIMSK |= 1 << OCIE0;	
		
		return true;	
	}
	
	TickTimer * TickTimer::Instance()
	{
		return &timer;
	}
	
}



ISR(TIMER0_COMP_vect)
{
	Hardware::timer.timer_handler();
}