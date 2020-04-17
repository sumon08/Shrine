/*
 * test.cpp
 *
 * Created: 4/17/2020 10:48:57 PM
 *  Author: Asus
 */ 

#include <avr/io.h>
#include "event.hpp"
#include "memory.hpp"

void TestHandler()
{
	PORTA ^= 1 << PA0;
}


int main(void)
{
	Event::InitializeTimer();
	Event::SharedPtr<Event::ISystem> system = Event::System();
	DDRA |= 1 << PA0;
	DDRA |= 1 << PA1;
	
	Event::SharedPtr<Event::ITimer> timer = system->CreateTimer();
	timer->Callback(TestHandler);
	timer->Type(Event::TimerType::REPETATIVE);
	timer->Period(Event::TickType(1000));
	timer->Start();
	
	while(1)
	{
		system->Run();
		
	}
}