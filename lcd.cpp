/*
 * lcd.cpp
 *
 * Created: 6/5/2020 11:52:52 PM
 *  Author: Asus
 */ 


#include <avr/io.h>
#include "lcd.hpp"
#include "hardware/portable.hpp"
#include <string.h>

namespace Shrine
{
	
	LCD LCD::instance;
	
	typedef unsigned char BufferCount;
	

	class PCD8544
	{
		#define BUFFER_SIZE		504
		
		PCD8544()
		{
			
		}
		
		public:
		~PCD8544()
		{
			
		}
		void Initialize()
		{
			//init SPI 
			DDRB |= 1 << PORTB0 | 1 << PORTB1 | 1 << PORTB2 | 1 << PORTB3 | 1 << PORTB5;
			PORTB |= 1 << PORTB1 | 1 << PORTB2;
			SPCR |= 1 << SPE | 1 << MSTR;
			memset(buffer, 0, 504);
			Reset();
			
		}
		void SPISelect(bool state)
		{
			if (state)
				PORTB &= ~ (1 << PORTB2);
			else
				PORTB |= 1 << PORTB2;
		}
		
		uint8_t SPISendByte(uint8_t byte)
		{
			SPDR = byte;
			while(!(SPSR & 1 << SPIF));
			return SPDR;
		}
		
		void Reset()
		{
			PORTB &= ~(1 << PORTB1);
			uint8_t count = 0xFF;
			while(count--);
			PORTB |= 1 << PORTB0;
		}
		
		void SendCommand(uint8_t cmd)
		{
			
			PORTB &= ~(1 << PORTB0);
			SPISelect(true);
			SPISendByte(cmd);
			SPISelect(false);
		}
		
		void SendData(uint8_t * data, uint16_t length)
		{
			PORTB |= (1 << PORTB0);
			SPISelect(true);
			for(uint16_t i = 0; i < length; i++)
			{
				SPISendByte(data[i]);
			}
			SPISelect(false);
		}
				
		private:
		uint8_t buffer[BUFFER_SIZE];
	};
	
	
	LCD & LCD::Instance()
	{
		return instance;
	}
	
	
	
	
	
	LCD::LCD()
	{
		DDRB = 0xFF;
		DDRD |= 1<<PORTD0;
		DDRD |= 1<<PORTD1;
		DDRD |= 1<<PORTD2;
	}
	
	inline void LCD::SetRS()
	{
		PORTD |= 1 << PORTD0;
	}
	
	inline void LCD::ClearRS()
	{
		PORTD &= ~( 1 << PORTD0);
	}
	
	inline void LCD::SetWR()
	{
		PORTD |= 1 << PORTD1;
	}
	
	inline void LCD::ClearWR()
	{
		PORTD &= ~( 1 << PORTD1);
	}
	
	inline void LCD::SetE()
	{
		PORTD |= 1 << PORTD2;
	}
	
	
	inline void LCD::ClearE()
	{
		PORTD &= ~( 1 << PORTD2);
	}
	
	
	
	inline bool LCD::IsBusy()
	{
		ClearRS();
		SetWR();
		DDRB &= ~(1 << PORTB7);
		__NOP();
		bool ret = PINB & 1 << PINB7? true : false;
		DDRB |= (1 << PORTB7);
		//Hardware::__NOP();
		return ret;
	}
	
	
	void LCD::WriteData(char ch)
	{

	}

	void LCD::WriteCmd(uint8_t cmd)
	{

	}

	inline void LCD::Cursor(CursorState state)
	{
		switch(state)
		{
			default:
			break;
		}
	}
	
	inline void LCD::Write(uint8_t x, uint8_t y, const char * text)
	{
		
	}
	inline void LCD::Write(uint8_t x, uint8_t y, LCD::BuiltinChar block)
	{
		
	}
	inline void LCD::Clear()
	{
		
	}
	inline void LCD::Clear(const char ch)
	{
		
	}

}