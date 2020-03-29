/*
 * new.cpp
 *
 * Created: 3/30/2020 2:57:14 AM
 *  Author: Asus
 */ 
#include <stdlib.h>



void * operator new(size_t size)
{
	void * p = malloc(size);
	return p;
}

void operator delete(void * p)
{
	free(p);
}


void * operator new[](size_t size)
{
	return malloc(size);
}

void operator delete[](void * ptr)
{
	free(ptr);
}



__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);

extern "C" void __cxa_pure_virtual(void);


int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
	
void __cxa_pure_virtual(void) {};