/*
 * fifo.h
 *
 * Created: 3/30/2020 2:11:09 AM
 *  Author: Asus
 */ 



/*
MIT License

Copyright (c) 2020 Md. Mahmudul Hasan Sumon

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef _FIFO_INCLUDE_H
#define _FIFO_INCLUDE_H

#include "memory.hpp"


namespace Event {



	#define LIST_DEFAULT_SIZE       10

	template<typename T>
	class Fifo
	{
		private:
		T * queue;
		int queue_size;
		int head,tail;
		int max_size;



		public:



		Fifo<T>(int size): max_size(size)
		{
			queue = new T[size];
			queue_size = 0;
			head = 0;
			tail=0;

		}

		~Fifo<T>()
		{
			delete [] queue;
		}

		bool Push(T element)
		{
			if(tail == max_size){
				tail=0;
			}
			queue[tail] = element;
			tail++;
			queue_size++;
			return true;
		}

		T  Pop()
		{
			if(head == max_size){
				head = 0;
			}

			queue_size--;

			T temp = queue[head++];

			return temp;

		}

		int Length()
		{
			return queue_size;
		}
		bool Empty()
		{
			return (queue_size==0);
		}

		int  Capacity()
		{
			return max_size;
		}
	};


	template<typename T>
	class Fifo<unique_ptr<T>>
	{
		private:
		unique_ptr<T> * queue;
		int queue_size;
		int head,tail;
		int max_size;



		public:



		Fifo<unique_ptr<T>>(int size): max_size(size)
		{
			queue = new unique_ptr<T>[size];
			queue_size = 0;
			head = 0;
			tail=0;

		}

		~Fifo<unique_ptr<T>>()
		{
			delete [] queue;
		}



		bool Push(unique_ptr<T> & element)
		{
			if(tail == max_size){
				tail=0;
			}
			queue[tail] = Event::move(element);
			tail++;
			queue_size++;
			return true;
		}

		unique_ptr<T>  Pop()
		{
			if(head == max_size){
				head = 0;
			}

			queue_size--;

			unique_ptr<T> temp = Event::move(queue[head++]);

			return temp;

		}

		int Length()
		{
			return queue_size;
		}
		bool Empty()
		{
			return (queue_size==0);
		}

		int Capacity()
		{
			return max_size;
		}
	};
}
#endif //_FIFO_INCLUDE_H
