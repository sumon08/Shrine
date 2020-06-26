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
	
	
	//template <typename T>
	//struct ListNode<UniquePtr<T>>
	//{
		//UniquePtr<T> value;
		//ListNode * pNext;
	//};
	
	template <typename T>
	class List 
	{
		public:
		List()
		{
			pHead = NULL;
			pTail = NULL;
			count = 0;
		}
		
		//List( size_t n, const T & value = T())
		//{
			//
		//}
		
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
			Clear();
		}
		
		bool Empty() const
		{
			return (count == 0);
		}
		
		size_t Size() const
		{
			return static_cast<size_t>(count);
		}
		
		size_t MaxSize() const
		{
			return Size();
		}
		
		void Clear()
		{
			ListNode<T> * node = pHead;
			for (uint16_t i = 0; i < count; i++)
			{
				pHead = node->pNext;
				delete node;
				node = pHead;
				if (node == NULL)
					break;
			}
			count = 0;
		}
		
		void PushBack(const T & value)
		{
			ListNode<T> * node = new ListNode<T>();
			node->pNext = NULL;
			node->value = value;
			pTail->pNext = node;
			pTail = node;
			count++;
		}
		
		void PushBack(T && value)
		{
			ListNode<T> * node = new ListNode<T>();
			node->pNext = NULL;
			node->value = move(value);
			pTail->pNext = node;
			pTail = node;
			count++;
		}
		
		
		void PushFront(const T & value)
		{
			ListNode<T> * node = new ListNode<T>();
			node->pNext = NULL;
			node->value = value;
			node->pNext = pHead;
			pHead = node;
			count++;
		}
		
		void PushFront(T && value)
		{
			ListNode<T> * node = new ListNode<T>();
			node->pNext = NULL;
			node->value = move(value);
			node->pNext = pHead;
			pHead = node;
			count++;
		}
		
		void PopBack()
		{
			//ListNode<T> * node = pTail;
			//pTail = 
		}
		
		void PopFront()
		{
			ListNode<T> * node = pHead;
			pHead = pHead->pNext;
			
			delete node;
		}
		
		
		//void Resize(size_t count)
		//{
			//
		//}
		//
		//void Swap(List & other)
		//{
			//
		//}
		//
		//void Merge(List & other)
		//{
			//
		//}
		//
		//void Merge(List && other)
		//{
			//
		//}
		//
		//template <typename Compare>
		//void Merge(List & other, Compare comp)
		//{
			//
		//}
		//
		//template <typename Compare>
		//void Merge(List && other, Compare comp)
		//{
			//
		//}
		
		//size_t Remove(const T & value)
		//{
			//
		//}
		//
		//template <typename BinaryPredicate>
		//size_t RemoveIf(const T & value, BinaryPredicate p)
		//{
			//
			//
		//}
		template <typename BinaryPredicate>
		size_t RemoveIf(BinaryPredicate p)
		{
			size_t c = 0;
			ListNode<T> * node = pHead;
			ListNode<T> * prev = NULL;
			while(node != NULL)
			{
				if (p(node->value))
				{
					if (prev == NULL)
					{
						pHead = node->pNext;
					}
					else
					{
						prev->pNext = node->pNext;
					}
					c++;
					delete node;
				}
				prev = node;
				node = node->pNext;
			}
			
			return c;
		}
		//
		//void Reverse()
		//{
			//
		//}
		//
		//size_t Unique()
		//{
			//
		//}
		//
		//template <typename BinaryPredicate>
		//size_t Unique(BinaryPredicate p)
		//{
			//
		//}
		//
		//void Sort()
		//{
			//
		//}
		//
		//template <typename Comapare>
		//void Sort(Compare comp)
		//{
			//
		//}
		//
		//
		//List & operator=(const List& other)
		//{
			//
		//}
		//
		//List & operator=(const List && other)
		//{
			////
		//}
		
		T & operator[](size_t at)
		{
			ListNode<T> * node = pHead;
			for (size_t i = 0; i <= at; i++)
			{
				node = node->pNext;
			}
			return node->value;
		}
		
		private:
		ListNode<T> * pHead;
		ListNode<T> * pTail;
		//ListNode<T> * pFree;
		uint16_t count;
		//uint16_t free_count;
		
	};
}


#endif /* LIST_H_ */