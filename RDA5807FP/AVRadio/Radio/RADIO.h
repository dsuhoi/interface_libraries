////////////////////////////////////////////////////////////////
///Library for configuration ports, timer and other functions///
////////////////////////////////////////////////////////////////

#ifndef _RADIO
#define _RADIO

///////////////Stations/////////////////////
#define Love_Radio 1076
#define Radio_Vanya 1070
#define Yumor_FM 1065
#define Novoe_Radio 1060
#define Radio_Record 1045
#define Vesti_FM 1040
#define Radio_DFM 1035
#define RUS_Radio 1026
#define Dorog_Radio 1020
#define AutoRadio 1015
#define Retro_FM 1008
#define EuroPlus 1003
#define Studio21 991
#define Radio_Bryansk 916
#define Radio_7 911
#define Radio_Mayak 906
#define Radio_Dacha 902
#define Radio_32 879

///////////////buttons///////////////
#define UP (1<<0)
#define DOWN (1<<1)
#define MODE (1<<2)
#define EXIT (1<<3)

////////////////Function//////////////////////////////////
void knopki_set(void);//button handler
uint8_t get_knopka(void);//condition button
void volume_mod(void);//config volume
void menu(void);//config station
void set_station(uint8_t);
void timer_port(void);//config timer&ports

#endif
