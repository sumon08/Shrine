///*
 //* test.cpp
 //*
 //* Created: 4/17/2020 10:48:57 PM
 //*  Author: Asus
 //*/ 
//
//#include <avr/io.h>
//#include "event.hpp"
//#include "memory.hpp"
//#include "new.hpp"
//
//class Monitor 
//{
	//public:
	//Monitor()
	//{
		//current_state = false;
		//sample_count = 0;
		//DDRA &= ~(1 << PA2);
	//}
	//
	//
	//
	//void Sample()
	//{
		//if (current_state == false && PinState())
		//{
			//sample_count++;
			//if (sample_count >= 10)
			//{
				//current_state = true;
				//PORTA |= 1 << PA1;
			//}
		//}
		//else if (current_state == true && !PinState())
		//{
			//sample_count++;
			//if (sample_count >= 10)
			//{
				//current_state = false;
				//PORTA &= ~(1<<PA1);
			//}
		//}
		//else
		//{
			//sample_count = 0;
		//}
	//}
	//
	//bool PinState()
	//{
		//if (PINA & 1 << PA2)
		//{
			//return true;
		//}
		//return false;
	//}
	//
	//private:
	//bool current_state;
	//uint8_t sample_count;
//};
//
//
//Monitor monitor;
//
//void TestHandler()
//{
	//PORTA ^= 1 << PA0;
	//monitor.Sample();
//}
//
//uint8_t count = 0;
//uint8_t flag = 1;
//void TestHandler2()
//{
	//if(flag == 1)
		//PORTC = count ++;
	//else
		//PORTC = count --;
		//
		//if(count == 15)
		//{
			//flag = 0;
		//}
		//else if( count == 0)
		//{
			//flag = 1;
		//}
//}
//
//
//
//
//int main(void)
//{
	//Shrine::InitializeTimer();
	//Shrine::System & system = Shrine::System::Instance();
	//DDRA |= 1 << PA0;
	//DDRA |= 1 << PA1;
	//DDRA |= 1 << PA3;
	//DDRC = 0xFF;
	//Shrine::Timer timer;
	//timer.Callback(TestHandler);
	//timer.Type(Shrine::TimerType::REPETATIVE);
	//timer.Period(Shrine::TickType(10));
	////timer.Start();
	//
	//Shrine::Timer timer1;
	//timer1.Callback(TestHandler2);
	//timer1.Period(Shrine::TickType(1000));
	//timer1.Type(Shrine::TimerType::REPETATIVE);
	//timer1.Start();
	//
	//uint8_t buf[sizeof(Shrine::Timer)];
	//
	//Shrine::Timer * tim = new((void*)buf) Shrine::Timer();
	//tim->Callback(TestHandler2);
	//
	//
	//system.Run();
//}