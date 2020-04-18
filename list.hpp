/*
 * list.h
 *
 * Created: 4/18/2020 1:49:02 AM
 *  Author: Asus
 */ 


#ifndef LIST_H_
#define LIST_H_


namespace Shrine 
{
	template <typename T>
	struct ListNode
	{
		T value;
		ListNode * pNext;
	};
	
	
	template <typename T>
	struct ListNode<UniquePtr<T>>
	{
		UniquePtr<T> value;
		ListNode * pNext;
	};
	
	template <typename T>
	class List 
	{
		List()
		{
			
		}
		
		List( size_t n, const T & value = T())
		{
			
		}
		
		//copy constructor
		List(const List & l)
		{
			
		}
		
		//move constructor
		List(const List && l)
		{
			
		}
		
		//destructor
		~List()
		{
			
		}
		
		bool Empty() const
		{
			
		}
		
		size_t Size() const
		{
			
		}
		
		size_t MaxSize() const
		{
			
		}
		
		void Clear()
		{
			
		}
		
		void PushBack(const T & value)
		{
			
		}
		
		void PushBack(T && value)
		{
			
		}
		
		
		void PushFront(const T & value)
		{
			
		}
		
		void PushFront(T && value)
		{
			
		}
		
		void PopBack()
		{
			
		}
		
		void PopFront()
		{
			
		}
		
		
		void Resize(size_t count)
		{
			
		}
		
		void Swap(List & other)
		{
			
		}
		
		void Merge(List & other)
		{
			
		}
		
		void Merge(List && other)
		{
			
		}
		
		template <typename Compare>
		void Merge(List & other, Compare comp)
		{
			
		}
		
		template <typename Compare>
		void Merge(List && other, Compare comp)
		{
			
		}
		
		size_t Remove(const T & value)
		{
			
		}
		
		template <typename BinaryPredicate>
		size_t RemoveIf(const T & value, BinaryPredicate p)
		{
			
		}
		
		void Reverse()
		{
			
		}
		
		size_t Unique()
		{
			
		}
		
		template <typename BinaryPredicate>
		size_t Unique(BinaryPredicate p)
		{
			
		}
		
		void Sort()
		{
			
		}
		
		template <typename Comapare>
		void Sort(Compare comp)
		{
			
		}
		
		
		List & operator=(const List& other)
		{
			
		}
		
		List & operator=(const List && other)
		{
			//
		}
		
		private:
		ListNode<T> * pHead;
		ListNode<T> * pTail;
		uint16_t count;
		
	};
}


#endif /* LIST_H_ */