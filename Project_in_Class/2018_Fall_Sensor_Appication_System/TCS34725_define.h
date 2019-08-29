#include "UFF4I2C_header.h"


#define TCS34725_ADDRESS         (0x29<<1)//(0x29)

#define TCS34725_COMMAND_BIT      (0x80)

#define TCS34725_READBIT (0x01)

#define TCS34725_ENABLE           (0x00)
#define TCS34725_ENABLE_AIEN      (0x10)    /* RGBC Interrupt Enable */
#define TCS34725_ENABLE_WEN       (0x08)    /* Wait enable - Writing 1 activates the wait timer */
#define TCS34725_ENABLE_AEN       (0x02)    /* RGBC Enable - Writing 1 actives the ADC, 0 disables it */
#define TCS34725_ENABLE_PON       (0x01)    /* Power on - Writing 1 activates the internal oscillator, 0 disables it */
#define TCS34725_ATIME            (0x01)    /* Integration time */
#define TCS34725_WTIME            (0x03)    /* Wait time (if TCS34725_ENABLE_WEN is asserted) */
#define TCS34725_WTIME_2_4MS      (0xFF)    /* WLONG0 = 2.4ms   WLONG1 = 0.029s */
#define TCS34725_WTIME_204MS      (0xAB)    /* WLONG0 = 204ms   WLONG1 = 2.45s  */
#define TCS34725_WTIME_614MS      (0x00)    /* WLONG0 = 614ms   WLONG1 = 7.4s   */
#define TCS34725_AILTL            (0x04)    /* Clear channel lower interrupt threshold */
#define TCS34725_AILTH            (0x05)
#define TCS34725_AIHTL            (0x06)    /* Clear channel upper interrupt threshold */
#define TCS34725_AIHTH            (0x07)
#define TCS34725_PERS             (0x0C)    /* Persistence register - basic SW filtering mechanism for interrupts */
#define TCS34725_PERS_NONE        (0b0000)  /* Every RGBC cycle generates an interrupt                                */
#define TCS34725_PERS_1_CYCLE     (0b0001)  /* 1 clean channel value outside threshold range generates an interrupt   */
#define TCS34725_PERS_2_CYCLE     (0b0010)  /* 2 clean channel values outside threshold range generates an interrupt  */
#define TCS34725_PERS_3_CYCLE     (0b0011)  /* 3 clean channel values outside threshold range generates an interrupt  */
#define TCS34725_PERS_5_CYCLE     (0b0100)  /* 5 clean channel values outside threshold range generates an interrupt  */
#define TCS34725_PERS_10_CYCLE    (0b0101)  /* 10 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_15_CYCLE    (0b0110)  /* 15 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_20_CYCLE    (0b0111)  /* 20 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_25_CYCLE    (0b1000)  /* 25 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_30_CYCLE    (0b1001)  /* 30 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_35_CYCLE    (0b1010)  /* 35 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_40_CYCLE    (0b1011)  /* 40 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_45_CYCLE    (0b1100)  /* 45 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_50_CYCLE    (0b1101)  /* 50 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_55_CYCLE    (0b1110)  /* 55 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_60_CYCLE    (0b1111)  /* 60 clean channel values outside threshold range generates an interrupt */
#define TCS34725_CONFIG           (0x0D)
#define TCS34725_CONFIG_WLONG     (0x02)    /* Choose between short and long (12x) wait times via TCS34725_WTIME */
#define TCS34725_CONTROL          (0x0F)    /* Set the gain level for the sensor */
#define TCS34725_ID               (0x12)    /* 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727 */
#define TCS34725_STATUS           (0x13)
#define TCS34725_STATUS_AINT      (0x10)    /* RGBC Clean channel interrupt */
#define TCS34725_STATUS_AVALID    (0x01)    /* Indicates that the RGBC channels have completed an integration cycle */
#define TCS34725_CDATAL           (0x14)    /* Clear channel data */
#define TCS34725_CDATAH           (0x15)
#define TCS34725_RDATAL           (0x16)    /* Red channel data */
#define TCS34725_RDATAH           (0x17)
#define TCS34725_GDATAL           (0x18)    /* Green channel data */
#define TCS34725_GDATAH           (0x19)
#define TCS34725_BDATAL           (0x1A)    /* Blue channel data */
#define TCS34725_BDATAH           (0x1B)

#define TCS34725_INTEGRATIONTIME_2_4MS   0xFF,   /**<  2.4ms - 1 cycle    - Max Count: 1024  */
#define TCS34725_INTEGRATIONTIME_24MS    0xF6,   /**<  24ms  - 10 cycles  - Max Count: 10240 */
#define TCS34725_INTEGRATIONTIME_50MS    0xEB,   /**<  50ms  - 20 cycles  - Max Count: 20480 */
#define TCS34725_INTEGRATIONTIME_101MS   0xD5,   /**<  101ms - 42 cycles  - Max Count: 43008 */
#define TCS34725_INTEGRATIONTIME_154MS   0xC0,   /**<  154ms - 64 cycles  - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_700MS  0x00 /**<  700ms - 256 cycles - Max Count: 65535 */

#define TCS34725_GAIN_1X    0x00   /**<  No gain  */
#define TCS34725_GAIN_4X    0x01   /**<  4x gain  */
#define TCS34725_GAIN_16X   0x02   /**<  16x gain */
#define TCS34725_GAIN_60X   0x03 /**<  60x gain */



void TCS34725_write8(unsigned char Reg,unsigned char Value);
void TCS34725_enable(void);
void TCS34725_read8(unsigned char Reg,unsigned char *Value);
void TCS34725_disable(void);
void TCS34725_SetIntegrationTime(unsigned char it);
void TCS34725_SetGain(unsigned char gain);
void TCS34725_GetRawData(unsigned int *red, unsigned int *green, unsigned int *blue, unsigned int *clear);
unsigned int TCS34725_CalculateColorTemperature(unsigned int r, unsigned int g, unsigned int b);
unsigned int  TCS34725_5CalculateLux(unsigned int  r, unsigned int  g, unsigned int  b);



void TCS34725_write8(unsigned char Reg,unsigned char Value)
{
    writeByte_i2c(TCS34725_ADDRESS,(TCS34725_COMMAND_BIT | Reg) , (Value & 0xFF));
}
void TCS34725_read8(unsigned char Reg,unsigned char *Value)
{
    *Value=readByte_i2c(TCS34725_ADDRESS,(TCS34725_COMMAND_BIT | Reg));
}
void TCS34725_enable(void)
{
    TCS34725_write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);  
    delay_ms(4);
    TCS34725_write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
    delay_ms(2); 
}
void TCS34725_disable(void)
{
    unsigned char reg=0;
    TCS34725_read8(TCS34725_ENABLE, &reg);
    TCS34725_write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN)) ;
}
void TCS34725_SetIntegrationTime(unsigned char it)
{
    TCS34725_write8(TCS34725_ATIME, it);
}
void TCS34725_SetGain(unsigned char gain)
{
    TCS34725_write8(TCS34725_CONTROL, gain);
}
void TCS34725_GetRawData(unsigned int *red, unsigned int *green, unsigned int *blue, unsigned int *clear)
{
    unsigned char Htemp=0,Ltemp=0;
    TCS34725_read8(TCS34725_CDATAL,&Ltemp);    
    TCS34725_read8(TCS34725_CDATAH,&Htemp);   
    *clear=(Htemp*256) + Ltemp;  
    
    TCS34725_read8(TCS34725_RDATAL,&Ltemp);    
    TCS34725_read8(TCS34725_RDATAH,&Htemp);   
    *red=(Htemp*256)+ Ltemp; 
    
    
    TCS34725_read8(TCS34725_GDATAL,&Ltemp);    
    TCS34725_read8(TCS34725_GDATAH,&Htemp);   
    *green=(Htemp*256)+ Ltemp;
    
    
    TCS34725_read8(TCS34725_BDATAL,&Ltemp);    
    TCS34725_read8(TCS34725_BDATAH,&Htemp);   
    *blue=(Htemp*256)+ Ltemp;  
    
    delay_ms(1000);
}

unsigned int TCS34725_CalculateColorTemperature(unsigned int r, unsigned int g, unsigned int b)
{
  float X, Y, Z;      /* RGB to XYZ correlation      */
  float xc, yc;       /* Chromaticity co-ordinates   */
  float n;            /* McCamy's formula            */
  float cct;

  /* 1. Map RGB values to their XYZ counterparts.    */
  /* Based on 6500K fluorescent, 3000K fluorescent   */
  /* and 60W incandescent values for a wide range.   */
  /* Note: Y = Illuminance or lux                    */
  X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
  Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  Z = (-0.68202F * r) + (0.77073F * g) + ( 0.56332F * b);

  /* 2. Calculate the chromaticity co-ordinates      */
  xc = (X) / (X + Y + Z);
  yc = (Y) / (X + Y + Z);

  /* 3. Use McCamy's formula to determine the CCT    */
  n = (xc - 0.3320F) / (0.1858F - yc);

  /* Calculate the final CCT */
  cct = (449.0F * pow(n, 3)) + (3525.0F * pow(n, 2)) + (6823.3F * n) + 5520.33F;

  /* Return the results in degrees Kelvin */
  return (unsigned int)cct;
}

unsigned int  TCS34725_5CalculateLux(unsigned int  r, unsigned int  g, unsigned int  b)
{
  float illuminance;

  /* This only uses RGB ... how can we integrate clear or calculate lux */
  /* based exclusively on clear since this might be more reliable?      */
  illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

  return (unsigned int )illuminance;
}