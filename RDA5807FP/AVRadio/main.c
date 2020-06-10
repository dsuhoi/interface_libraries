#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "../../I2C/i2c.h"
#include "LCD/LCD.h"
#include "../RDA5807FP.h"
#include "Radio/RADIO.h"

extern uint8_t stat, vol;
extern uint16_t fr;
extern uint8_t station_ee EEMEM;

/////////////////Update buttons////////////////////
ISR (TIMER0_OVF_vect){
knopki_set();
}

int main(void){
timer_port();
i2c_init();
FM_init();
LCDinit();
LCDstring("AVRadio FM",0,0);
LCDstring("by DSuhoi (2019)",0,1);
_delay_ms(1500);

stat = eeprom_read_byte(&station_ee); //read station
set_station(stat);
Set_volume(vol);
sei();

while(1){
LCDstring("Freq: ",1,0);
LCDstring("MHz",13,0);

switch((uint8_t)get_knopka()){
case 1: fr++; if(fr>1080)fr=870; SetFreq(fr); break; //frequency setting
case 2: fr--; if(fr<870)fr=1080; SetFreq(fr); break;
case 3: LCDclear(); menu(); break; //menu with stations setting
case 4: volume_mod(); break; //volume setting
}

uint8_t f1=fr/1000;			//output frequency
uint8_t f2=fr/100-f1*10;
uint8_t f3=fr/10-f1*100-f2*10;
uint8_t f4=fr-f1*1000-f2*100-f3*10;
LCDGotoXY(7,0);
f1>0 ? LCDdata(f1+'0') : LCDdata(' ');
LCDdata(f2+'0');
LCDdata(f3+'0');
LCDdata('.');
LCDdata(f4+'0');

_delay_ms(100);
LCDclear();
} 
}
