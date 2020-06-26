/*
 * dispatch.h
 *
 * Created: 6/12/2020 11:48:29 PM
 *  Author: Asus
 */ 


#ifndef DISPATCH_H_
#define DISPATCH_H_


namespace Shrine
{
	typedef uint16_t DispatcherId;
	class IEvent;
	
	class IDispatcher
	{
		friend class IEvent;
		public:
		IDispatcher();
		virtual ~IDispatcher();
		virtual void Dispatch(const IEvent * event);
		
		private:
	};
}


#endif /* DISPATCH_H_ */