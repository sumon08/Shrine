/*
 * portable.h
 *
 * Created: 6/5/2020 7:43:30 PM
 *  Author: Asus
 */ 

#include <avr/io.h>
#ifndef PORTABLE_H_
#define PORTABLE_H_



#define __NOP()	/*extern "C"	*/__asm__ __volatile__ ("nop\n\t" ::)




namespace Hardware
{
	
	
	//template <typename Handler>
	//class TickTimert
	//{
		//public:
		//
		//
		//private:
		//static Handler handler;
	//};
	//
	//template <typename Handler>
	//Handler TickTimert<Handler>::handler;
}


#endif /* PORTABLE_H_ */