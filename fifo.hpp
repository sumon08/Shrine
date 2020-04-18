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
#include "config.hpp"


namespace Shrine
{
	template <typename T>
	struct StorageNode
	{
		StorageNode()
		{
			pNext = NULL;
		}
		T value;
		StorageNode * pNext;
	};
	
	
	template <typename T>
	struct StorageNode<UniquePtr<T>>
	{
		UniquePtr<T> value;
		StorageNode<UniquePtr<T>> * pNext;
	};
	

	template<typename T>
	class Fifo
	{
		private:
		StorageNode<T> * pHead;
		StorageNode<T> * pTail;
		StorageNode<T> * pFree;
		int queue_size;



		public:



		Fifo()
		{
			pHead = NULL;
			pFree = NULL;
			queue_size = 0;
		}

		~Fifo()
		{
			StorageNode<T> * node = pHead;
			while(1)
			{
				 if (node == NULL)
				 {
					 break;
				 }
				 StorageNode<T> * pnode = node->pNext;
				 delete node;
				 node = pnode;
			}
			
			node = pFree;
			while(1)
			{
				if (node == NULL)
				{
					break;
				}
				StorageNode<T> * pnode = node->pNext;
				delete node;
				node = pnode;
			}
		}

		bool Push(const T & element)
		{
			if(pFree == NULL){
				pFree = new StorageNode<T>();
			}
			
			StorageNode<T> * node = pFree;
			pFree = node->pNext;
			node->value = element;
			node->pNext = NULL;
			if(pHead == NULL){
				pHead = node;
			}
			else {
				StorageNode<T> * pnode = pHead;
				while(1)
				{
					if(pnode->pNext == NULL)
					{
						pnode->pNext = node;
						break;
					}
					pnode = pnode->pNext;
				}
			}
			
			queue_size++;
			return true;
		}
		

		T  Pop()
		{
			if(queue_size == 0)
			{
				return T();
			}

			queue_size--;

			StorageNode<T> * node = pHead;
			pHead = pHead->pNext;
			node->pNext = pFree;
			pFree = node;
			return node->value;
		}

		int Length()
		{
			return queue_size;
		}
		bool Empty()
		{
			return (queue_size==0);
		}
	};


	template<typename T>
	class Fifo<UniquePtr<T>>
	{
		private:
		StorageNode<UniquePtr<T>> * pHead;
		StorageNode<UniquePtr<T>> * pTail;
		StorageNode<UniquePtr<T>> * pFree;
		int queue_size;



		public:



		Fifo()
		{
			pHead = NULL;
			pFree = NULL;
			queue_size = 0;
		}

		~Fifo()
		{
			// add delete code here.
		}



		bool Push(UniquePtr<T> element)
		{
			if(pFree == NULL){
				pFree = new StorageNode<UniquePtr<T>>();
			}
			
			StorageNode<UniquePtr<T>> * node = pFree;
			pFree = node->pNext;
			node->value = move(element);
			node->pNext = NULL;
			if(pHead == NULL)
			{
				pHead = node;
			}
			else
			{
				StorageNode<UniquePtr<T>> * pnode = pHead;
				while(1)
				{
					if(pnode->pNext == NULL)
					{
						pnode->pNext = node;
						break;
					}
					pnode = pnode->pNext;
				}
			}
			queue_size++;
			return true;
		}

		UniquePtr<T>  Pop()
		{
			if(queue_size == 0)
			{
				return UniquePtr<T>();
			}

			queue_size--;

			StorageNode<UniquePtr<T>> * node = pHead;
			UniquePtr<T> temp = move(node->value);
			pHead = pHead->pNext;
			node->pNext = pFree;
			pFree = node;
			

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

		
	};
}
#endif //_FIFO_INCLUDE_H
