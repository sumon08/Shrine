/*
 * new.h
 *
 * Created: 6/5/2020 10:30:22 PM
 *  Author: Asus
 */ 


#ifndef NEW_H_
#define NEW_H_


void * operator new(size_t size);
void operator delete(void * p);
void * operator new[](size_t size);
void * operator new(size_t, void * address);

#endif /* NEW_H_ */