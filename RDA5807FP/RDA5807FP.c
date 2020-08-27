#include <avr/io.h>
#include <util/delay.h>
#include "../I2C/i2c.h"
#include "RDA5807FP.h"

extern uint8_t fm_buf[9];   // Radio buffer


// Write bytes
void I2C_write(void)
{
    i2c_start();
    i2c_write_byte(0x20);
    i2c_write_byte(fm_buf[0]);
    i2c_write_byte(fm_buf[1]);
    i2c_write_byte(fm_buf[2]);
    i2c_write_byte(fm_buf[3]);
    i2c_write_byte(fm_buf[4]);
    i2c_write_byte(fm_buf[5]);
    i2c_write_byte(fm_buf[6]);
    i2c_write_byte(fm_buf[7]);
    i2c_write_byte(fm_buf[8]);
    i2c_stop(); 
    return;
}

// Initializations RDA5807
void FM_init(void)
{
    fm_buf[0] = 0b11010010; 
    fm_buf[1] = 0b10001101;
    fm_buf[2] = 0;
    fm_buf[3] = 0;
    fm_buf[4] = 0b00000010;
    fm_buf[5] = 0b00000000;
    fm_buf[6] = 0b00001000;
    fm_buf[7] = 0b10001111;
    //writeBuf[8] = 0b00000000;

    I2C_write();
    return;
}

// Write frequency
void setFreq(uint16_t freq)
{
    uint16_t chan = (freq - 870);
    //uint16_t chan = (freq - RDA5807_FREQ_MIN) / RDA5807_CHAN_SPACING;

    fm_buf[2]  = chan >> 2;                 
    fm_buf[3] = (chan << 6) | RDA5807_TUNE;

    I2C_write();
    return;
}

// Write volume
void set_volume(uint8_t volume)
{
    fm_buf[7] &= 0b11110000;
    fm_buf[7] |= volume;
    I2C_write();
    return;
}

// Setting up auto search ( 1 - up, 0 - down)
void auto_seek (uint8_t d)
{

    fm_buf[0] |= (d<<1)|(1<<0);
    I2C_write();
    return;
}
