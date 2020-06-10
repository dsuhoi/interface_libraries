
/* юБРНП:              Papandopala Papandopalavich
 * хЛЪ ТЮИКЮ:          Atmega16_LCD_LIB.c
 * рХО лй:			   Atmega16, Flash 16 Kbytes, SRAM 1 Kbytes, EEPROM 512 bytes.
 * рЮЙРНБЮЪ ВЮЯРНРЮ:   F_CPU 8000000 цЖ
 * дЮРЮ:               28.06.2013 21:17:29
 * бЕПЯХЪ он:          ATMEL STUDIO VERSION 6.1.2562
 * FUSES:              HIGH xx, LOW xx;
 * нОХЯЮМХЕ:           сПЕГЮММЮЪ АХАКХНРЕЙЮ ДКЪ ПЮАНРШ Я LCD ДХЯОКЕЪЛХ АЮГХПСЧЫХЛХЯЪ МЮ HD44780 
					   ЙНМРПНККЕПЮУ. дЮММЮЪ АХАКХНРЕЙЮ ПЮАНРЮЕР ОН 4У Х 8ЛХ АХРМНИ ЯУЕЛЕ ОНДЙКЧВЕМХЪ
					   LCD, ОНДДЕПФХБЮЕР РНКЭЙН БШБНД ДЮММШУ МЮ ДХЯОКЕИ*/ 


//#define  F_CPU 8000000UL         
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "LCD.h"

//яХЯРЕЛМШЕ ТСМЙЖХХ, ХУ МЕ РПНЦЮЕЛ, НМХ ДКЪ ПЮАНРШ ДХЯОКЕЪ.
void Send_byte(uint8_t);	//оЕПЕДЮВЮ ДЮММШУ LCD, БШГШБЮЕРЯЪ ТСМЙЖХЪЛХ Send_command Х Send_data.
void Busy_flag(void);		//оПНБЕПЙЮ ТКЮЦЮ ГЮМЪРНЯРХ.
void HiPin(void);			//оЕПЕБНДХЛ ОНПР Б ЯНЯРНЪМХЕ HI.
void OutPin(void);			//оЕПЕБНДХЛ ОНПР Б ЯНЯРНЪМХЕ "БШУНД".
void InPin(void);			//оЕПЕБНДХЛ ОНПР Б ЯНЯРНЪМХЕ "БУНД".
void Strob(void);			//бЙК/БШЙК ЯРПНАЮ е


//оНКЭГНБЮРЕКЭЯЙХЕ ТСМЙЖХХ, ХЛХ ОНКЭГСЕЛЯЪ Б ОПНЦПЮЛЛЕ.
void LCDinit(void)							//хМХЖХЮКХГХПСЕЛ ДХЯОКЕИ
{
	//оЕПЕД ХМХЖХЮКХГЮЖХЕИ LCD, МЮДН Б init ГЮДЕПФЙС Б 100 ЛЯЕЙ ЯДЕКЮРЭ, ВРНА ОХРЮМХЕ СЯРЮЙЮМХКНЯЭ. 
	_delay_ms(100);
	CDDR |=  (1<<RS)|(1<<E)|(1<<RW);   //мЮЯРПНИЙЮ ОНПРНБ 
	CPORT&=~((1<<RS)|(1<<E)|(1<<RW));  //мЮЯРПНИЙЮ ОНПРНБ 
	OutPin();						   //мЮЯРПНИЙЮ ОНПРНБ
	
	uint8_t i=0;
	while (i!=3)
	{
		#ifdef  LCD_8BIT       //НРОПЮБЙЮ ЯХЛБНКЮ 0x30.
		        DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4)|(0<<DB3)|(0<<DB2)|(0<<DB1)|(0<<DB0);
		#else
				DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4);
		#endif
		
		Strob();
		_delay_ms(5);
		i++;
	}
	
	//пЮГЛХМНВМШИ ЩРЮО ГЮЙНМВЕМ, ДЮКЕЕ ОЕПЕУНДХЛ Й НЯМНБМШЛ СОПЮФМЕМХЪЛ.
	
	#ifdef  LCD_8BIT
			LCDcommand(0b00111000);//8ЛХ АХРМШИ ХМРЕПТЕИЯ, ДБЕ ЯРПНЙХ, 5x8 РНВЕЙ.
	#else   //оЕПБШИ ПЮГ НРОПЮБКЪЕЛ РНКЭЙН ОНК ЯРЮПЬЕИ РЕРПЮДШ
			Busy_flag();
			OutPin();
			DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(0<<DB4);//4У АХРМШИ ХМРЕПТЕИЯ 
			Strob();
			LCDcommand(0b00101000);//дБЕ ЯРПНЙХ, 5x8 РНВЕЙ.
	#endif
	
	LCDcommand(0b1100);  //бЙКЧВЮЕЛ ДХЯОКЕИ + АЕГ НРНАПЮФЕМХЪ ЙСПЯНПНБ.
	LCDcommand(0b110);   //яВЕРВХЙ ЮДПЕЯЮ БЯЕЦДЮ АСДЕР ЯЛЕЫЮРЭЯЪ МЮ n+1
	LCDcommand(0b10);    //ЙСПЯНП Б ОНГХЖХЧ 0,0 + ЯАПНЯ БЯЕУ ЯДБХЦНБ
	LCDcommand(0b1);     //НВХЯРЙЮ ДХЯОКЕЪ 
	//нЯМНБМШЕ СОПЮФМЕМХЪ ГЮЙНМВЕМШ. оЕПЕУНДХЛ Й ПЕКЮЙЯЮЖХХ.
}
void LCDcommand(uint8_t i)					//нРОПЮБЙЮ ЙНЛЮМДШ, МЮЯРПНИЙЮ ДХЯОКЕЪ.
{
	Busy_flag();	//оПНБЕПХЛ ЯОЕПБЮ ТКЮЦ ГЮМЪРНЯРХ, Ю ЯБНАНДЕМ КХ ДХЯОКЕИ?
	Send_byte(i);
}
void LCDdata(uint8_t i)						//нРОПЮБЙЮ ЯХЛБНКЮ ДКЪ НРНАПЮФЕМХЪ МЮ ДХЯОКЕЕ.
{
	Busy_flag();	//оПНБЕПХЛ ЯОЕПБЮ ТКЮЦ ГЮМЪРНЯРХ, Ю ЯБНАНДЕМ КХ ДХЯОКЕИ?
	CPORT|=(1<<RS); //RS=1 ОНЯШКЮЕЛ ДЮММШЕ Б LCD
	Send_byte(i);
	CPORT&=~(1<<RS);//RS=0
}
void LCDGotoXY(uint8_t x,uint8_t y)			//сЯРЮМЮБКХБЮЕЛ ЙСПЯНП Б X, Y ОНГХЖХЧ
{
	 uint8_t Address;
	
	switch(y)
	{
		case 0: Address = LINE0+x; 
				break;
		case 1: Address = LINE1+x; 
				break;
		default: Address = LINE0+x;
	}
	
	LCDcommand(1<<7 | Address);
}
void LCDstring(char *i,uint8_t x,uint8_t y) //бШБЕЯРХ ЯРПНЙС МЮ ДХЯОКЕИ.
{
	LCDGotoXY(x,y);
	while( *i )
	{
		LCDdata(*i++ );
	}
}
void LCDstring_of_sram(uint8_t* data,uint8_t nBytes,uint8_t x, uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	if (!data) 
	{
		return;
	}
	
	for(i=0; i<nBytes; i++)
	{
		LCDdata(data[i]);
	}
	
	
}
void LCDstring_of_flash(const uint8_t *FlashLoc,uint8_t x,uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		LCDdata((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
}
void LCDset(void)			//дБСУЯРПНВМШИ ДХЯОКЕИ 5x8 РНВЕЙ
{
	LCDcommand(0b101000);
}
void LCDblank(void)			//яДЕКЮРЭ МЕБХДХЛНИ ХМТН МЮ ДХЯОКЕЕ
{
	LCDcommand(0b1000);
}
void LCDnblank(void)		//яДЕКЮРЭ БХДХЛНИ ХМТН МЮ ДХЯОКЕЕ + НРЙКЧВХРЭ БХДХЛШЕ ЙСПЯНПШ.
{
	LCDcommand(0b1100);
}
void LCDclear(void)			//нВХЯРЙЮ ДХЯОКЕЪ + ЙСПЯНП МЮ ОНГХЖХЧ 0,0
{
	LCDcommand(0b1);
}
void LCDcursor_bl(void)		//бЙКЧВХРЭ ЛХЦЮЧЫХИ ЙСПЯНП
{
	LCDcommand(0b1101);
}
void LCDcursor_on(void)		//бЙКЧВХРЭ ОНДВЕПЙХБЮЧЫХИ ЙСПЯНП
{
	LCDcommand(0b1110);
}
void LCDcursor_vi(void)		//бЙКЧВХРЭ НАЮ ЙСПЯНПЮ
{
	LCDcommand(0b1111);
}
void LCDcursorOFF(void)		//бШЙКЧВХРЭ ЙСПЯНП
{
	LCDcommand(0b1100);
}
void LCDacr(void)			//CВЕРВХЙ ЮДПЕЯЮ БЯЕЦДЮ АСДЕР ЯЛЕЫЮРЭЯЪ МЮ n+1
{
	LCDcommand(0b110);
}
void LCDacl(void)			//CВЕРВХЙ ЮДПЕЯЮ БЯЕЦДЮ АСДЕР ЯЛЕЫЮРЭЯЪ МЮ n-1
{
	LCDcommand(0b100);
}
void LCDcursorl(void)		//яЛЕЯРХРЭ ЙСПЯНП БКЕБН МЮ 1
{
	LCDcommand(0b10000);
}
void LCDcursorr(void)		//яЛЕЯРХРЭ ЙСПЯНП БОПЮБН МЮ 1
{
	LCDcommand(0b10100);
}
void LCDcursorln(uint8_t n)	//яЛЕЯРХРЭ ЙСПЯНП БКЕБН МЮ n ЯХЛБНКНБ
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b10000);
	}
}
void LCDcursorrn(uint8_t n)	//яЛЕЯРХРЭ ЙСПЯНП БОПЮБН МЮ n ЯХЛБНКНБ
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b10100);
	}
}
void LCDscreenl(void)		//яЛЕЯРХРЭ ЩЙПЮМ БКЕБН МЮ 1
{
	LCDcommand(0b11000);
}
void LCDscreenr(void)		//яЛЕЯРХРЭ ЩЙПЮМ БОПЮБН МЮ 1
{
	LCDcommand(0b11100);
}
void LCDscreenln(uint8_t n)	//яЛЕЯРХРЭ ЩЙПЮМ БКЕБН МЮ n ЯХЛБНКНБ
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b11000);
	}
}
void LCDscreenrn(uint8_t n)	//яЛЕЯРХРЭ ЩЙПЮМ БОПЮБН МЮ n ЯХЛБНКНБ
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b11100);
	}
}
void LCDscreenL(void)		//я ЙЮФДШЛ МНБШЛ ЯХЛБНКНЛ ЩЙПЮМ АСДЕР ЯЛЕЫЮРЭЯЪ БКЕБН
{
	LCDcommand(0b101);
}
void LCDscreenR(void)		//я ЙЮФДШЛ МНБШЛ ЯХЛБНКНЛ ЩЙПЮМ АСДЕР ЯЛЕЫЮРЭЯЪ БОПЮБН
{
	LCDcommand(0b111);
}
void LCDresshift(void)      //сЯРЮМНБХРЭ ЙСПЯНП Б ОНГХЖХЧ 0,0 + ЯАПНЯ БЯЕУ ЯДБХЦНБ, ХГНАПЮФЕМХЕ НЯРЮЕРЯЪ
{
	LCDcommand(0b10);
}


//яХЯРЕЛМШЕ ТСМЙЖХХ, ХУ МЕ РПНЦЮЕЛ, НМХ ДКЪ ПЮАНРШ ДХЯОКЕЪ.
void Send_byte(uint8_t i)	//оЕПЕДЮВЮ ДЮММШУ LCD, БШГШБЮЕРЯЪ ТСМЙЖХЪЛХ Send_command Х Send_data.
{
	OutPin();
	
	#ifdef  LCD_8BIT
			if ((i&1)==1)
			{
				DPORT|=(1<<DB0);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB1);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB2);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB3);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB7);
			}
			
		    Strob();
			
	#else
			
			uint8_t higb = ((i&0b11110000)>>4);
			uint8_t lowb =  (i&0b00001111);
	
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB7);
			}
	
			Strob();
			OutPin();
	
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB7);
			}
	
			Strob();
	#endif
	
	HiPin();
}
void Busy_flag(void)		//оПНБЕПЙЮ ТКЮЦЮ ГЮМЪРНЯРХ
{
	InPin();
	CPORT|=(1<<RW);	  //R/W=1 ВХРЮЕЛ ХГ LCD
	
	#ifdef  LCD_8BIT
			uint8_t i=1;
			while(i==1)
			{
				CPORT|=(1<<E);//бЙКЧВХКХ ЯРПНА.
				asm("nop");
				asm("nop");
				
				if (!(DPIN&(1<<DB7)))//яВХРЮКХ Х ОПНБЕПХКХ ТКЮЦ ГЮМЪРНЯРХ.
				{
					i=0;
				}
				
				CPORT&=~(1<<E);//бШЙКЧВХКХ ЯРПНА.
				asm("nop");
				asm("nop");						
			}
	#else
			uint8_t i=1;
			while(i==1)
			{
				CPORT|=(1<<E);//бЙКЧВХКХ ЯРПНА.
				asm("nop");
				asm("nop");
		
				if (!(DPIN&(1<<DB7)))//яВХРЮКХ Х ОПНБЕПХКХ ТКЮЦ ГЮМЪРНЯРХ.
				{
					i=0;
				}
		
				CPORT&=~(1<<E);//бШЙКЧВХКХ ЯРПНА.
				asm("nop");
				asm("nop");
				Strob();
				asm("nop");
				asm("nop");
		
			}
	#endif
	
	CPORT&=~(1<<RW);   //R/W=0 
}
void HiPin(void)			//оЕПЕБНДХЛ ОНПР Б ЯНЯРНЪМХЕ Hi.
{
	#ifdef  LCD_8BIT
			DDDR =0;
			DPORT=0;
	#else
			DDDR &=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
			DPORT&=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
    #endif
}
void OutPin(void)			//оЕПЕБНДХЛ ОНПР Б ЯНЯРНЪМХЕ "БШУНД".
{
	#ifdef  LCD_8BIT
			DDDR =0xFF;
			DPORT=0;
	#else
			DDDR |=  (1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4);
			DPORT&=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
	#endif
}
void InPin(void)			//оЕПЕБНДХЛ ОНПР Б ЯНЯРНЪМХЕ "БУНД".
{
	#ifdef  LCD_8BIT
			DDDR =0;
			DPORT=0xFF;
	#else
			DDDR &=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
			DPORT|=  (1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4);
	#endif
}
void Strob(void)            //бЙКЧВЮЕЛ БШЙКЧВЮЕЛ ЯРПНАЮПЭ.
{
	CPORT|=(1<<E);//бЙКЧВХКХ ЯРПНА.
	_delay_us(1);
	CPORT&=~(1<<E);//бШЙКЧВХКХ ЯРПНА.
}

