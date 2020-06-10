#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "../LCD/LCD.h"
#include "../../RDA5807FP.h"
#include "RADIO.h"


uint16_t fr = 1000;//Frequency
uint8_t stat = 1;//stattion counter
uint8_t vol = 5;//volume
uint8_t pausa;//delay
uint8_t set_knopka;//
uint8_t station_ee EEMEM;
/////////////////////////////////////////////////////////////
///////////////////////buttons//////////////////////////////////////
void knopki_set(void){
char knopka = 0, dlinnaya = 10 , korotkaya = 3;
if((PINC & UP) == 0)
knopka = 1;
else if((PINC & DOWN) == 0)
knopka = 2;
else if((PINC & MODE) == 0)
knopka = 3;
else if((PINC & EXIT) == 0)
knopka = 4;

if(knopka){
if(pausa > dlinnaya){
pausa = dlinnaya - 2;
set_knopka = knopka;
return;}
 pausa++;
 if(pausa == korotkaya){
 set_knopka = knopka;
 return;}}
else pausa = 0;
}
///////////////////////////////////////////
uint8_t get_knopka(){
uint8_t reg = set_knopka;
set_knopka = 0;
return reg;
}

//////////////Stations///////////////////////////
void set_station (uint8_t st) {

if (st==1) {SetFreq(Love_Radio);   fr=Love_Radio;     LCDstring("Love Radio",0,1);}
if (st==2) {SetFreq(Radio_Vanya);  fr=Radio_Vanya;    LCDstring("Radio Vanya",0,1);}
if (st==3) {SetFreq(Yumor_FM);     fr=Yumor_FM;       LCDstring("Yumor FM",0,1);}
if (st==4) {SetFreq(Novoe_Radio);  fr=Novoe_Radio;    LCDstring("Novoe Radio",0,1);}
if (st==5) {SetFreq(Radio_Record); fr=Radio_Record;   LCDstring("Radio Record",0,1);}
if (st==6) {SetFreq(Vesti_FM);     fr=Vesti_FM;       LCDstring("Vesti FM",0,1);}
if (st==7) {SetFreq(Radio_DFM);    fr=Radio_DFM;	  LCDstring("Radio DFM",0,1);}
if (st==8) {SetFreq(RUS_Radio);    fr=RUS_Radio;	  LCDstring("Russkoe Radio",0,1);}
if (st==9) {SetFreq(Dorog_Radio);  fr=Dorog_Radio;	  LCDstring("Dorognoe Radio",0,1);}
if (st==10) {SetFreq(AutoRadio);   fr=AutoRadio;	  LCDstring("AutoRadio",0,1);}
if (st==11) {SetFreq(Retro_FM);    fr=Retro_FM;		  LCDstring("Retro FM",0,1);}
if (st==12) {SetFreq(EuroPlus);    fr=EuroPlus;		  LCDstring("EuroPlus",0,1);}
if (st==13) {SetFreq(Studio21);    fr=Studio21;		  LCDstring("Studio21",0,1);}
if (st==14) {SetFreq(Radio_Bryansk); fr=Radio_Bryansk; LCDstring("Radio Bryansk",0,1);}
if (st==15) {SetFreq(Radio_7);       fr=Radio_7;	  LCDstring("Radio 7",0,1);}
if (st==16) {SetFreq(Radio_Mayak);   fr=Radio_Mayak;  LCDstring("Radio Mayak",0,1);}
if (st==17) {SetFreq(Radio_Dacha);   fr=Radio_Dacha;  LCDstring("Radio Dacha",0,1);}
if (st==18) {SetFreq(Radio_32);      fr=Radio_32;	  LCDstring("Radio 32",0,1);}

eeprom_write_byte(&station_ee, st);

}

////////////Config volume////////////////
void volume_mod(void){
uint8_t a=1;
LCDclear();
LCDstring("Volume:",0,1);
while(a){

switch((uint8_t)get_knopka()){
case 1: vol++; if(vol>15)vol=15; Set_volume(vol); break;
case 2: vol--; if(vol<1)vol=1; Set_volume(vol); break;
case 3: if(PORTB & (1<<4)) PORTB &=~(1<<4); else PORTB |=(1<<4); break;
case 4: a=0; break;
}

LCDGotoXY(7,1);
LCDdata(vol/10 + '0');
vol >= 10 ? LCDdata(vol-10+'0'):
LCDdata(vol+'0');
_delay_ms(100);
}
return;
}


///////////////////Set stations///////////////////////
void menu(void){
uint8_t a=1;
while(a){
LCDstring("*Freq:",0,0);
LCDstring("MHz",13,0);
uint8_t f1=fr/1000;
uint8_t f2=fr/100-f1*10;
uint8_t f3=fr/10-f1*100-f2*10;
uint8_t f4=fr-f1*1000-f2*100-f3*10;
LCDGotoXY(7,0);
f1>0 ? LCDdata(f1+'0') : LCDdata(' ');
LCDdata(f2+'0');
LCDdata(f3+'0');
LCDdata('.');
LCDdata(f4+'0');

switch((uint8_t)get_knopka()){
case 1: stat--; if(stat<1) stat=18; LCDclear(); set_station(stat);  break;
case 2: stat++; if(stat>18) stat=1; LCDclear(); set_station(stat);  break;
case 3: a=0; break;
case 4: volume_mod(); break;
}
_delay_ms(100);
}
return;
}

///////////////////////////Timer&Ports/////////////////////////////////////////
void timer_port(void){
TCCR0 |= 0x05;
TIMSK |= 0x01;
TCNT0 = 0;
DDRC = 0x00;
DDRB |=0x10;
PORTC |= UP | DOWN | EXIT | MODE;
}



