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
	class unique_ptr {
		public:
		using element_type		= T;
		using pointer		= element_type*;
		using reference		= element_type&;
		public:
		inline constexpr		unique_ptr (void)		: _p (nullptr) {}
		inline constexpr explicit	unique_ptr (pointer p)		: _p (p) {}
		inline			unique_ptr (unique_ptr&& p)	: _p (p.release()) {}
		unique_ptr (const unique_ptr&) = delete;
		inline			~unique_ptr (void)		{ delete _p; }
		inline constexpr pointer	get (void) const		{ return _p; }
		inline pointer		release (void)			{ auto rv (_p); _p = nullptr; return rv; }
		inline void			reset (pointer p = nullptr)	{ assert (p != _p || !p); auto ov (_p); _p = p; delete ov; }
		//inline void			swap (unique_ptr& v)		{ swap (_p, v._p); }
		inline constexpr explicit	operator bool (void) const	{ return _p != nullptr; }
		inline unique_ptr&		operator= (pointer p)		{ reset (p); return *this; }
		inline unique_ptr&		operator= (unique_ptr&& p)	{ reset (p.release()); return *this; }
		unique_ptr&			operator=(const unique_ptr&) = delete;
		inline constexpr reference	operator* (void) const		{ return *get(); }
		inline constexpr pointer	operator-> (void) const		{ return get(); }
		inline constexpr reference	operator[] (size_t i) const	{ return get()[i]; }
		inline constexpr bool	operator== (const pointer p) const	{ return _p == p; }
		inline constexpr bool	operator== (const unique_ptr& p) const	{ return _p == p._p; }
		inline constexpr bool	operator< (const unique_ptr& p) const	{ return _p < p._p; }
		private:
		pointer			_p;
	};
}




#endif  //_MEMORY_INCLUDE_H