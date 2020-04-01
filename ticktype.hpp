/*
 * ticktype.h
 *
 * Created: 3/31/2020 12:51:40 PM
 *  Author: Asus
 */ 


#ifndef TICKTYPE_H_
#define TICKTYPE_H_

#include <stdint.h>
#include "config.hpp"



namespace Event
{
	
	class TickType 
	{
		public:
		TickType()
		{
			tick = 0;
		}
		
		
		TickType(uint16_t ms)
		{
			tick = (ms / CONFIG_TIMER_TICK_PERIOD_MS);
		}
		
		~TickType() = default;
		
		//setter and getter
		uint16_t & Tick()
		{
			return tick;
		}
		
		const uint8_t Error() const
		{
			return error;
		}
		
		
		//private member variable.
		private:
		uint16_t tick;
		uint8_t error;
		
	};
}


#endif /* TICKTYPE_H_ */