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



namespace Shrine
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
			Tick(ms);
		}
		
		~TickType() = default;
		
		//setter and getter
		const uint16_t Tick() const
		{
			return tick;
		}
		
		void Tick(uint16_t ms)
		{
			tick = ms / CONFIG_TIMER_TICK_PERIOD_MS;
			error = ms % CONFIG_TIMER_TICK_PERIOD_MS;
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