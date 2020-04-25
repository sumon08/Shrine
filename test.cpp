// /*
//  * test.cpp
//  *
//  * Created: 4/17/2020 10:48:57 PM
//  *  Author: Asus
//  */ 

// #include <avr/io.h>
// #include "event.hpp"
// #include "memory.hpp"

// class Monitor 
// {
// 	public:
// 	Monitor()
// 	{
// 		current_state = false;
// 		sample_count = 0;
// 		DDRA &= ~(1 << PA2);
// 	}
	
	
	
// 	void Sample()
// 	{
// 		if (current_state == false && PinState())
// 		{
// 			sample_count++;
// 			if (sample_count >= 10)
// 			{
// 				current_state = true;
// 				PORTA |= 1 << PA1;
// 			}
// 		}
// 		else if (current_state == true && !PinState())
// 		{
// 			sample_count++;
// 			if (sample_count >= 10)
// 			{
// 				current_state = false;
// 				PORTA &= ~(1<<PA1);
// 			}
// 		}
// 		else
// 		{
// 			sample_count = 0;
// 		}
// 	}
	
// 	bool PinState()
// 	{
// 		if (PINA & 1 << PA2)
// 		{
// 			return true;
// 		}
// 		return false;
// 	}
	
// 	private:
// 	bool current_state;
// 	uint8_t sample_count;
// };


// Monitor monitor;

// void TestHandler()
// {
// 	PORTA ^= 1 << PA0;
// 	monitor.Sample();
// }





// int main(void)
// {
// 	Shrine::InitializeTimer();
// 	Shrine::System & system = Shrine::System::Instance();
// 	DDRA |= 1 << PA0;
// 	DDRA |= 1 << PA1;
	
// 	Shrine::Timer timer;
// 	timer.Callback(TestHandler);
// 	timer.Type(Shrine::TimerType::REPETATIVE);
// 	timer.Period(Shrine::TickType(10));
// 	timer.Start();
// 	system.Run();
	
	
// 	while(1)
// 	{
		
		
// 	}
// }