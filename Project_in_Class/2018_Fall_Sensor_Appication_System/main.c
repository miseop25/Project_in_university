#include <mega128.h>
#include <delay.h>
#include <stdlib.h>
#include <math.h>
#include "lcd.h"
#include "keypad_Header.h"
#include "TCS34725_define.h"

int LCD_show = 1;
int sw;                                       
int counter=0;
int dir_motor = 0;
int select_num;
int m1,m2,m3,m4;  //m1,2,3,4 버튼 눌렀을때 사용하는 변수. 

void Switch_Verify(void)
{
    switch(select_num){
    case 12 : {m1=1; m2=0; m3=0; m4=0;break;} 
    case 13 : {m2=1; m1=0; m3=0; m4=0;break;} 
    case 14 : {m3=1; m1=0; m2=0; m4=0;break;}
    case 15 : {m4=1; m1=0; m2=0; m3=0;break;} 
    default :break;
    }
    delay_ms(150);
}


void Timer2_Init()
{   
    TCCR2 = 0x00;
    TCCR2 = (1<<WGM20)|(1<<WGM21)|(1<<COM21);
    OCR2 = 0xFF;
    TIMSK |= (1<<OCIE2);
    DDRB.7 = 1;
}

interrupt[TIM2_COMP] void timer2_comp(void)
{

}



void main(void)
{
int row_count ;
int col_count ;
int Num;
unsigned int r,g,b,c;
unsigned char st[7];
LCD_Init();
LCD_Clear();
LCD_Pos(0,0); 
LCD_Str("Select MODE");
LCD_Pos(1,0); 
LCD_Str("M1:ManualM2:Auto");
DDRB = 0x0F;
DDRC = 0x0f; //상위 4bit 입력, 하위 4bit 출력 키패드 
PORTC = 0xf0;//PORTC의 상위 4bit 내부 풀업 설정 키패드
Timer2_Init();

SREG |= 0x80;
TCCR2 |= 1<<CS21;


TWBR = 0x40;
TCS34725_enable();
TCS34725_SetIntegrationTime(TCS34725_INTEGRATIONTIME_700MS);
TCS34725_SetGain(TCS34725_GAIN_1X);
delay_ms(500);


while (1)
      {
      for(row_count = 0; row_count < 4; row_count++)//키패드 관련 일거오는 포문임. 
        {
        col_count = Scan_Col(row_count);        
        Num = KeyNumScan(row_count, col_count);  
        delay_ms(1);
        if(Num !=-1)
            {  
                select_num = Num; 
                Switch_Verify();
                if(m1 ==1){
                    LCD_Clear();
                    LCD_Pos(0,0); 
                    LCD_Str("Manual Mode");
                    switch(select_num){
                    case 2: 
                        PORTB.0 = 0; 
                        PORTB.1 = 1;
                        PORTB.2 = 0; 
                        PORTB.3 = 0;
                        break;
                    case 4:
                        PORTB.0 = 0;
                        PORTB.1 = 0;
                        PORTB.2 = 1; 
                        PORTB.3 = 0;
                        break;  
                    case 8:
                        PORTB.0 = 1;
                        PORTB.1 = 0;
                        PORTB.2 = 0; 
                        PORTB.3 = 0;
                        break;
                    case 6:
                        PORTB.0 = 0;
                        PORTB.1 = 0;
                        PORTB.2 = 0; 
                        PORTB.3 = 1;
                        break;
                    case 5:
                        PORTB.0 = 0;
                        PORTB.1 = 0;
                        PORTB.2 = 0; 
                        PORTB.3 = 0;
                        break;   
                    default:
                        PORTB.0 = 0;
                        PORTB.1 = 0;
                        PORTB.2 = 0; 
                        PORTB.3 = 0;
                    break;

                 }
                }else if(m2 == 1){
                    LCD_Clear();
                    LCD_Pos(0,0); 
                    LCD_Str("Auto Mode");
                    LCD_Pos(1,0); 
                    LCD_Str("M3 : Show data");
                }else if(m3 == 1){

                }

            } 
        }

       
      sw = (0x0f&PIND);      
            
           if(sw == 0x0e){
           delay_ms(5);
           while(PIND == 0x0e){}
           if(LCD_show ==0){ LCD_show = 1; }
           else if(LCD_show ==1){ LCD_show =0;  }
           }
           TCS34725_GetRawData(&r,&g,&b,&c);   
           if(LCD_show==1 && m3==1){
           LCD_Clear();
           LCD_Pos(0,0); 
           LCD_Str("R=");
           itoa(r,st);
           LCD_Str(st);
           LCD_Pos(0,7); 
           LCD_Str("G=");
           itoa(g,st);
           LCD_Str(st);
           LCD_Pos(1,0);  
           LCD_Str("B=");
           itoa(b,st);
           LCD_Str(st);
           LCD_Pos(1,7);  
           LCD_Str("C=");
           itoa(c,st);
           LCD_Str(st);  
           }
           if (LCD_show ==0 && m3==1){
           LCD_Clear();
           LCD_Pos(0,0); 
           LCD_Str("Col=");
           itoa(TCS34725_CalculateColorTemperature(r,g,b) ,st);
           LCD_Str(st);   
           LCD_Pos(1,0); 
           LCD_Str("Lux=");
           itoa(TCS34725_5CalculateLux(r,g,b) ,st);
           LCD_Str(st);  
           }
           if (r>g && r>b && c>5000 && (m2==1 || m3==1)){
                PORTB.0 = 1;
                PORTB.1 = 0;
                PORTB.2 = 0; 
                PORTB.3 = 0;
           }else if(g>r && g>b && c>5000 && (m2==1 || m3==1)){
                PORTB.0 = 0;
                PORTB.1 = 1;
                PORTB.2 = 0; 
                PORTB.3 = 1;
           }else if(b>r && b>g && c>5000&& (m2==1 || m3==1)){
                PORTB.0 = 0;
                PORTB.1 = 1;
                PORTB.2 = 1; 
                PORTB.3 = 0;
           }else if(c<5000 && (m2==1 || m3==1)){
                PORTB.0 = 0;
                PORTB.1 = 0;
                PORTB.2 = 0; 
                PORTB.3 = 0;
           }
           
      }
}

