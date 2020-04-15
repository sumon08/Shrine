/*
 * callback.h
 *
 * Created: 4/7/2020 10:53:03 PM
 *  Author: Asus
 */ 


#ifndef CALLBACK_H_
#define CALLBACK_H_


namespace Event
{
	template <typename T>
	class CallbackHandler
	{
		void Execute()
		{
			callback();
		}
		private:
		typedef T Callback;
		Callback callback;
	};
}


#endif /* CALLBACK_H_ */