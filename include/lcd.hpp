/*
 * lcd.h
 *
 * Created: 6/5/2020 11:52:41 PM
 *  Author: Asus
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stddef.h>

namespace Shrine
{
	
	
	
	
	class LCD
	{
		LCD();
		public: 
		
		
		~LCD();
		
		enum class BuiltinChar
		{
			CHARGE_STAGE_1,
			CHARGE_STAGE_2,
			CHARGE_STAGE_3,
			CHARGE_STAGE_4,
			CHARGE_STAGE_5,
		};
		
		enum class CharMode
		{
			MODE_5X8,
			MODE_5X11	
		};
		
		enum class CursorState
		{
			OFF,
			ON,
			BLINK
		};
		
		static LCD & Instance();
		
		inline void Cursor(CursorState);
		
		inline void Write(uint8_t x, uint8_t y, const char * text);
		inline void Write(uint8_t x, uint8_t y, BuiltinChar block);
		inline void Clear();
		inline void Clear(const char ch);
		inline bool Create(uint8_t idx, const char * block);
		
		
		private:
		//Singleton implementation so copy and move constructor is deleted
		LCD(const LCD &) = delete;
		LCD(const LCD &&) = delete;
		LCD & operator=(const LCD &) = delete;
		LCD & operator=(const LCD &&) = delete;
		inline void SetRS();
		inline void ClearRS();
		inline void SetWR();
		inline void ClearWR();
		inline void SetE();
		inline void ClearE();
		inline bool IsBusy();
		
		inline void WriteData(char ch);
		inline void WriteCmd(uint8_t cmd);
		
		private:
		static LCD instance;
		
	};
	
	
	
}


#endif /* LCD_H_ */