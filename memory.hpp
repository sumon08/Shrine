/*
 * memory.h
 *
 * Created: 3/30/2020 2:05:00 AM
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




#ifndef _MEMORY_INCLUDE_H
#define _MEMORY_INCLUDE_H


#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>


namespace Event
{
	#ifndef NULL
		#define NULL (void *)0
	#endif
	
	#ifndef assert
		#define assert(x)
	#endif
	

	#define nullptr     NULL


	template <typename U> struct RemoveReference		{ typedef U Result; };
	template <typename U> struct RemoveReference<U&>	{ typedef U Result; };
	template <typename U> struct RemoveReference<U&&>	{ typedef U Result; };

	template <int target, int bitsize>
	struct ConstantByteSwap{
		enum {value=0};
	};
	template <uint32_t target>
	struct ConstantByteSwap<target,32>{
		enum {value = ( (target >> 24) & 0xff) | ( (target >> 8) & 0xff00 ) | ( (target << 8) & 0xff0000 ) | ( (target<<24) &0xff0000u )};
	};


	uint32_t ByteSwap(uint32_t target);


	template <typename T>
	inline constexpr typename RemoveReference<T>::Result && move (T&& v) noexcept
	{ return static_cast<typename RemoveReference<T>::Result&&>(v); }





	template <typename T>
	class UniquePtr {
		public:
		using element_type		= T;
		using pointer		= element_type*;
		using reference		= element_type&;
		public:
		inline constexpr		UniquePtr (void)		: _p (nullptr) {}
		inline constexpr explicit	UniquePtr (pointer p)		: _p (p) {}
		inline			UniquePtr (UniquePtr&& p)	: _p (p.release()) {}
		UniquePtr (const UniquePtr&) = delete;
		inline			~UniquePtr (void)		{ delete _p; }
		inline constexpr pointer	get (void) const		{ return _p; }
		inline pointer		release (void)			{ auto rv (_p); _p = nullptr; return rv; }
		inline void			reset (pointer p = nullptr)	{ assert (p != _p || !p); auto ov (_p); _p = p; delete ov; }
		//inline void			swap (unique_ptr& v)		{ swap (_p, v._p); }
		inline constexpr explicit	operator bool (void) const	{ return _p != nullptr; }
		inline UniquePtr&		operator= (pointer p)		{ reset (p); return *this; }
		inline UniquePtr&		operator= (UniquePtr&& p)	{ reset (p.release()); return *this; }
		UniquePtr&			operator=(const UniquePtr&) = delete;
		inline constexpr reference	operator* (void) const		{ return *get(); }
		inline constexpr pointer	operator-> (void) const		{ return get(); }
		inline constexpr reference	operator[] (size_t i) const	{ return get()[i]; }
		inline constexpr bool	operator== (const pointer p) const	{ return _p == p; }
		inline constexpr bool	operator== (const UniquePtr& p) const	{ return _p == p._p; }
		inline constexpr bool	operator< (const UniquePtr& p) const	{ return _p < p._p; }
		private:
		pointer			_p;
	};
	
	
	
	template <typename T>
	struct RefCounter
	{
		RefCounter()
		{
			count = 0;
		}
		uint16_t count;
		T * ptr;
	};
	
	template <typename T> 
	class SharedPtr
	{
		
		
		public:
		SharedPtr() noexcept
		{
			obj_ptr = NULL;
		}
		
		SharedPtr(T * ptr)
		{
			if(ptr != NULL)
			{
				obj_ptr = new RefCounter<T>();
				obj_ptr->count = 1;
				obj_ptr->ptr = ptr;
			}
			else
			{
				obj_ptr = NULL;
			}
		}
		
		SharedPtr(const SharedPtr<T> & ptr)
		{
			
			if(ptr.obj_ptr != NULL)
			{
				obj_ptr= ptr.obj_ptr;
				obj_ptr->count++;
			}
			else
			{
				obj_ptr = NULL;
			}
		}
		
		SharedPtr(const SharedPtr<T> && ptr)
		{
			if(ptr.obj_ptr != NULL)
			{
				obj_ptr= ptr.obj_ptr;
				ptr.obj_ptr = NULL;
			}
		}
		
		SharedPtr(UniquePtr<T> ptr)
		{
			if(ptr)
			{
				obj_ptr = new RefCounter<T>();
				obj_ptr->count = 1;
				obj_ptr->ptr = ptr->release();
			}
			else
			{
				obj_ptr = NULL;
			}
		}
		~SharedPtr()
		{
			Delete();
		}
		
		
		SharedPtr<T> & operator=(const SharedPtr<T> & ptr)
		{
			if(ptr.obj_ptr != obj_ptr)
			{
				Delete();
				obj_ptr = ptr.obj_ptr;
				obj_ptr->count++;
			}
			
			return *this;
		}
		
		SharedPtr<T> & operator=(SharedPtr<T> && ptr)
		{
			if (ptr.obj_ptr != obj_ptr)
			{
				Delete();
				obj_ptr = ptr.obj_ptr;
				ptr.obj_ptr = NULL;
			}
			return *this;
		}
		
		SharedPtr<T> & operator=(UniquePtr<T> &&ptr)
		{
			if(obj_ptr != NULL)
			{
				if (obj_ptr->count == 1)
				{
					obj_ptr->ptr = ptr->Release();
				}
				else
				{
					obj_ptr->count --;
					obj_ptr = new RefCounter<T>();
					obj_ptr->count = 1;
					obj_ptr->ptr = ptr->Release();
				}
			}
			else
			{
				obj_ptr = new RefCounter<T>();
				obj_ptr->count = 1;
				obj_ptr->ptr = ptr->Release();
			}
			return *this;
		}
		
		void Reset() noexcept
		{
			Delete();
		}
		
		void Reset( T * ptr) noexcept
		{
			if(obj_ptr != NULL)
			{
				obj_ptr->count --;
				if(obj_ptr->count == 0)
				{
					delete obj_ptr->ptr;
					obj_ptr->ptr = ptr;
					obj_ptr->count = 1;
				}
				else
				{
					obj_ptr = new RefCounter<T>();
					obj_ptr->ptr = ptr;
					obj_ptr->count = 1;
				}				
				
			}
		}
		
		void Swap(SharedPtr<T> & ptr)
		{
			RefCounter<T> * ref = obj_ptr;
			obj_ptr = ptr.obj_ptr;
			ptr.obj_ptr = ref;
		}
		
		T * Get() const noexcept
		{
			T * ret = NULL;
			if(obj_ptr != NULL && obj_ptr->ptr != NULL)
				ret = obj_ptr->ptr;
			return ret;
		}
		
		T & operator*()
		{
			return *obj_ptr->ptr;
		}
		
		T * operator->()
		{
			return obj_ptr->ptr;
		}
		
		uint16_t UseCount() const noexcept
		{
			if(obj_ptr != NULL)
				return obj_ptr->count;
			return 0;
		}
		
		explicit operator bool()
		{
			return Get() != NULL;
		}
		private:
		void Delete()
		{
			if (obj_ptr == NULL)
				return;
			obj_ptr->count--;
			if(obj_ptr->count == 0)
			{
				delete obj_ptr->ptr;			
				delete obj_ptr;
			}
			obj_ptr = NULL;
		}
		
		
		private:
		RefCounter<T> * obj_ptr;
	};
	
	template < typename T >
	bool operator==( const SharedPtr<T>& lhs, const SharedPtr<T>& rhs ) noexcept
	{
		if(!lhs && !rhs)
		{
			return true;
		}
		else
		{
			if (lhs.Get() == rhs.Get())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		return false;
	}
	
	template< typename T >
	bool operator!=( const SharedPtr<T>& lhs, const SharedPtr<T>& rhs ) noexcept
	{
		if (lhs == rhs)
		{
			return false;
		}
		return true;
	}
}




#endif  //_MEMORY_INCLUDE_H