/*
 * avr_timer.h
 *
 * Created: 3/31/2020 2:06:04 PM
 *  Author: Asus
 */ 


#ifndef AVR_TIMER_H_
#define AVR_TIMER_H_



namespace Hardware
{
	typedef void (*TickTimerHandler)();
	class TickTimer
	{
		public:
		TickTimer();		
		~TickTimer();
		
		
		bool Initialise(TickTimerHandler handler);
		static TickTimer * Instance();
		
		public:
		TickTimerHandler timer_handler;
		static TickTimer object;
	};
}


#endif /* AVR_TIMER_H_ */