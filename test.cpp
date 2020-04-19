/*
 * test.cpp
 *
 * Created: 4/17/2020 10:48:57 PM
 *  Author: Asus
 */ 

#include <avr/io.h>
#include "event.hpp"
#include "memory.hpp"

class TestEvent : public Shrine::IEvent
{
	void Handler()
	{
		PORTA ^= 1 << PA1;
	}
	
	private:
	int data;
};



void TestHandler()
{
	PORTA ^= 1 << PA0;
	Shrine::System& system = Shrine::System::Instance();
	Shrine::UniquePtr<Shrine::IEvent> event = Shrine::UniquePtr<Shrine::IEvent>(new TestEvent());
	event->Priority(2);
	system.Trigger(Shrine::move(event));
}





int main(void)
{
	Shrine::InitializeTimer();
	Shrine::System & system = Shrine::System::Instance();
	DDRA |= 1 << PA0;
	DDRA |= 1 << PA1;
	
	Shrine::Timer timer;
	timer.Callback(TestHandler);
	timer.Type(Shrine::TimerType::REPETATIVE);
	timer.Period(Shrine::TickType(200));
	timer.Start();
	system.Run();
	
	
	while(1)
	{
		
		
	}
}