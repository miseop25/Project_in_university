#include <mega128.h>
#include <delay.h>
#include "lcd.h"
#define Do  477
#define Re  424
#define Mi  378
#define Fa  357
#define Sol 318
#define La  283
#define Si  238
//ó������ �츮�� �� ���� �� ������� ������ �����.
int m1,m2,m3,m4;  //m1,2,3,4 ��ư �������� ����ϴ� ����. 
int d1,d2,d3,d4;   //m1,2,3,4# �������� ����� �����ϰ� �ϴ� ���� .
int inToLCD;
int comp=0;     //���Ҷ� ����ϴ� ����.
int shap=0;     //# ��ư �������� ����ϴ� �Լ�.
unsigned int home[10]= {1001,1002,1003,1004,1005,1006,1007,1008,1009,1010};         // 10���� ȣ�� ����
unsigned int homePassword[10]= {1000,2000,3000,4000,5000,6000,7000,8000,9000,1010}; //ȣ�� �ʱ� ��й�ȣ ����.
unsigned int num_in[5];     
unsigned int sum,comp_ho;
    Byte str[] = "WELCOME";
    Byte str1[] = "HAPPY HOUSE";
    Byte wrongPW[] = "WRONG PW";
    Byte rightPW[] = "RIGHT PW";
    Byte one[] = "1";
    Byte two[] = "2";
    Byte three[] = "3";
    Byte four[] = "4";
    Byte five[] = "5";
    Byte six[] = "6";
    Byte seven[] = "7";
    Byte eight[] = "8";
    Byte nine[] = "9";
    Byte zero[] = "0"; 
    Byte star[] = "*";
    Byte Emt[] = "";
    Byte PressPW[] = "PW:    ";

//LCD�� ��õ� 4�ڸ� ���� ��Ƽ���� �Ű��ִ� ģ�� & num_in �ʱ�ȭ ������.
void Num_to_int(){
    sum= num_in[3]*1000 + num_in[2]*100 + num_in[1]*10 + num_in[0];
    num_in[4] =0;
    num_in[3] =0;
    num_in[2] =0;
    num_in[1] =0;
    num_in[0] =0;
}

void Comp_Ho_To_int(){
    comp_ho= num_in[3]*1000 + num_in[2]*100 + num_in[1]*10 + num_in[0];
}

//���� �Է��� ȣ���� ��й�ȣ�� �����ִ� �Լ�.
void Show_Home_Password(){
    int ch_Num[4];
    int press_Password;
    int namuaje;
    int showPs;
    ch_Num[3] = num_in[3];
    ch_Num[2] = num_in[2];
    ch_Num[1] = num_in[1];
    ch_Num[0] = num_in[0];
    press_Password = ch_Num[3]*1000 + ch_Num[2]*100 + ch_Num[1]*10 +ch_Num[0];
    namuaje=press_Password%1000;
    switch(namuaje-1){
        case 0 : {showPs=homePassword[namuaje-1];break;}
        case 1 : {showPs=homePassword[namuaje-1];break;}
        case 2 : {showPs=homePassword[namuaje-1];break;}
        case 3 : {showPs=homePassword[namuaje-1];break;}
        case 4 : {showPs=homePassword[namuaje-1];break;}
        case 5 : {showPs=homePassword[namuaje-1];break;}
        case 6 : {showPs=homePassword[namuaje-1];break;}
        case 7 : {showPs=homePassword[namuaje-1];break;}
        case 8 : {showPs=homePassword[namuaje-1];break;}
        case 9 : {showPs=homePassword[namuaje-1];break;}
        default : break;}
    ch_Num[3] = showPs/1000;
    ch_Num[2] = showPs/100 - (showPs/1000)*10;
    ch_Num[1] = showPs/10 -(showPs/100)*10;
    ch_Num[0] = showPs-(showPs/10)*10;
    LCD_pos(0,7);
    LCD_CHAR(48+ch_Num[3]);
    LCD_CHAR(48+ch_Num[2]);
    LCD_CHAR(48+ch_Num[1]);
    LCD_CHAR(48+ch_Num[0]);
}

//ȣ���� �ش��ϴ� ��й�ȣ�� �´��� �˾ƺ� �ִ� ģ��
void Home_password_compare(){
    int ch_Num[4];
    int press_Password;
    int namuaje;
    ch_Num[3] = num_in[3];
    ch_Num[2] = num_in[2];
    ch_Num[1] = num_in[1];
    ch_Num[0] = num_in[0];
    press_Password = ch_Num[3]*1000 + ch_Num[2]*100 + ch_Num[1]*10 +ch_Num[0];
    namuaje=sum%1000;
    switch(namuaje-1){
        case 0 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 1 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 2 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 3 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 4 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 5 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 6 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 7 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 8 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        case 9 : {if(press_Password == homePassword[namuaje-1]){comp=1;}else comp =2;break;}
        default : break;
    }
}

//���� �Է��� ȣ���� �ٽ� LCD�� ����ϴ� �Լ�.
void Show_Home_Ho(){
  int ch_Num[4];
    ch_Num[3] = sum/1000;
    ch_Num[2] = sum/100 - (sum/1000)*10;
    ch_Num[1] = sum/10 -(sum/100)*10;
    ch_Num[0] = sum-(sum/10)*10;
    LCD_CHAR(48+ch_Num[3]);
    LCD_CHAR(48+ch_Num[2]);
    LCD_CHAR(48+ch_Num[1]);
    LCD_CHAR(48+ch_Num[0]);
}

//��й�ȣ ���� �������ִ� ģ��.
void change_Password(){
    int ch_Num[4];
    int new_Password;
    int namuaje;
    ch_Num[3] = num_in[3];
    ch_Num[2] = num_in[2];
    ch_Num[1] = num_in[1];
    ch_Num[0] = num_in[0];
    new_Password = ch_Num[3]*1000 + ch_Num[2]*100 + ch_Num[1]*10 +ch_Num[0];
    
    namuaje=sum%1000;
    switch(namuaje-1){
        case 0 : {homePassword[namuaje-1]=new_Password;break;}
        case 1 : {homePassword[namuaje-1]=new_Password;break;}
        case 2 : {homePassword[namuaje-1]=new_Password;break;}
        case 3 : {homePassword[namuaje-1]=new_Password;break;}
        case 4 : {homePassword[namuaje-1]=new_Password;break;}
        case 5 : {homePassword[namuaje-1]=new_Password;break;}
        case 6 : {homePassword[namuaje-1]=new_Password;break;}
        case 7 : {homePassword[namuaje-1]=new_Password;break;}
        case 8 : {homePassword[namuaje-1]=new_Password;break;}
        case 9 : {homePassword[namuaje-1]=new_Password;break;}
        default : break;}
}

//��й�ȣ �����ϴ� ȭ�� �����ִ� ģ��.
void Set_password_Display(){
   Byte checkPass[] = "R    :      (C)";
   Byte checkPass2[] = "R    :      (U)";
   LCD_pos(0,1);
   LCD_STR(checkPass);
   LCD_pos(1,1);
   LCD_STR(checkPass2);
   m1=0;
   d1=1;
   LCD_Comm(0x0e); // Display ON/OFF
   LCD_pos(0,2);
}

//������ ���� ���� ���۵Ǵ� ù�ܰ��� ģ��.
void Go_To_Home(){
   Byte PressHo[] = "R";
   LCD_pos(0,1);
   LCD_STR(PressHo);
   LCD_Comm(0x0e); // Ŀ�� ���ֱ�.
   LCD_pos(0,2);
   shap=0;
   d4=1;
}

//m1,m2,m3,m4,# �� �о���� ģ��
void Switch_Verify(void)
{
    switch(inToLCD){
    case 12 : {m1=1;break;} 
    case 13 : {m2=1;break;} 
    case 14 : {m3=1;break;}
    case 15 : {m4=1;break;} 
    case 11 : {shap=1;break;}             
    default :break;
    }
    delay_ms(150);
}

//Ű�е带 ���� �޾ƿ� ���ڸ� LCD�� ����� �ִ� ģ��.
void SelectNum(){
    switch(inToLCD){
        case 1 : {LCD_STR(one);break;}
        case 2 : {LCD_STR(two);break;}
        case 3 : {LCD_STR(three);break;}
        case 4 : {LCD_STR(four);break;}
        case 5 : {LCD_STR(five);break;}
        case 6 : {LCD_STR(six);break;}
        case 7 : {LCD_STR(seven);break;}
        case 8 : {LCD_STR(eight);break;}
        case 9 : {LCD_STR(nine);break;}
        case 0 : {LCD_STR(zero);break;}
        default : break;
    }
    num_in[4]=num_in[3];
    num_in[3]=num_in[2];
    num_in[2]=num_in[1];
    num_in[1]=num_in[0];
    num_in[0]=inToLCD;
    delay_ms(50);
}

void Port_set()       //���� ����� ��Ʈ�� ����
{
    DDRC = 0x0f; //���� 4bit �Է�, ���� 4bit ��� Ű�е� 
    DDRD= 0xf0; // sw ���� 4�� �Է����� ����
    PORTC = 0xf0;//PORTC�� ���� 4bit ���� Ǯ�� ���� Ű�е�
    DDRG|=(1<<4); // ������ ���� ��Ʈ ����.
}

int Scan_Col(int row)  //Row ��(row = 0�̸� ù��° ��, row = 3�̸� �׹�° �� ����)�� ���� Column ��ĵ �Լ�, ��� Col1(1��) = 0x01, Col2(2��) = 0x02, Col3(3��) = 0x04
{
    int col_temp=0 , col_num =0;    //col_temp : column�� �ӽ� ���� ����, col_num : column ��
    PORTC =~(1<<row);          //row ���� ���� ��Ʈ C�� ���� ��Ʈ ��� ����  ex)3��° ��(row = 2) ����, PORTC = 0b11111011        
    delay_us(1);                //�ν��ϱ���� �ð��� �ɸ��� ������ ������
    col_temp = PINC>>4;         //��Ʈ C�� �Է°� ��ĵ(��Ʈ C�� ���� 4��Ʈ �Է°��� �ʿ�, ���������� 4��Ʈ �̵�) ex)col_temp = 0b0000???? = 0x0? 
    col_num =  col_temp & 0x0f; //column ���� ���� ��Ʈ�� �ʿ��ϹǷ� 0x0f AND ���� ex)col_num = 0b0000???? = 0x0?, ��ư�� ���ȴٸ�  0x01, 0x02, 0x04�� ���
    return col_num; //Column �� ��ȯ                  
}
int KeyNumScan(int row, int col_data) //row�� column ���� ���� ���� ��ȯ
{
    int sel_num = -1; //select number����, ��ư�� ���� ���� ���� ����, �ʱⰪ -1 : �ƹ��͵� ������ ���� ����  
           
    switch(3-row)
    {
        case 0:               
            if(col_data == 0x01) sel_num = 1;
            if(col_data == 0x02) sel_num = 2;
            if(col_data == 0x04) sel_num = 3;
            if(col_data == 0x08) sel_num=12;  //m1
            break;
        case 1:               
            if(col_data == 0x01) sel_num = 4;
            if(col_data == 0x02) sel_num = 5;
            if(col_data == 0x04) sel_num = 6;
            if(col_data == 0x08) sel_num=13;  //m2
            break;
        case 2:               
            if(col_data == 0x01) sel_num = 7;
            if(col_data == 0x02) sel_num = 8;
            if(col_data == 0x04) sel_num = 9;
            if(col_data == 0x08) sel_num=14;   //m3
            break;
        case 3:               
            if(col_data == 0x01) sel_num = 10;  // *�� �ش��ϴ� �� 10 
            if(col_data == 0x02) sel_num = 0;   // 0�� �ش��ϴ� �� 0
            if(col_data == 0x04) sel_num = 11;  // #�� �ش��ϴ� �� 11 
            if(col_data == 0x08) sel_num=15;  //m4
            break; 
        default:break;
    }
    return sel_num;     //���õ� ���ڰ� ��ȯ.
}


void myDelay_us(unsigned int delay)
{
  int i;
  for(i=0; i<delay; i++)
  {
    delay_us(1);
  }
}

void SSound(int time)
{
    int i, tim;
    tim = 50000/time;
    for (i=0; i<tim; i++)
    {
      PORTG|= 1<<4;
      myDelay_us(time);
      PORTG &= ~(1<<4);
      myDelay_us(time);
    }
}

void main(void)
{
    int row_count ;
    int col_count ;
    int countNum=9;
    int Num;
    PortInit();//LCD��Ʈ �ʱ�ȭ
    Port_set(); //���� ����ϴ� ��Ʈ ��� ����
    LCD_Init();//LCD ȭ�� �ʱ�ȭ
    LCD_pos(0,2);
    LCD_STR(str);
    LCD_pos(1,2);
    LCD_STR(str1);
    LCD_Comm(0x0c); // Display ON/OFF
    //LCD�� �ʱ� ȭ�� ���� 
        
    while(1){
    
    Switch_Verify();//m1,m2,m3,m4,#�� ����� �����ϱ� ���ؼ� �ϴ� �о��.
    if(m1==1){
        m2=0; d2=0;
        m1=0; d1=0;
        m3=0;
        shap=0;  d4=0;
        countNum=0;
        LCD_Clear(); 
        Set_password_Display();//m1�� ��ư�� ���������� ��й�ȣ ���� ȭ���� ǥ���ϰ� �ȴ�.
        }
    //m2�� LCD�� ȭ���� �ʱ��� ȭ������ ������ �ִ� ģ����.
    if(m2==1){
    LCD_Clear();
    LCD_pos(0,2);
    LCD_STR(str);
    LCD_pos(1,2);
    LCD_STR(str1);
    m2=0; d2=0;
    m1=0; d1=0;
    m3=0;
    shap=0;  d4=0;
    countNum=9;
    LCD_Comm(0x0c); // Ŀ�������ֱ�.
    //��� ������ �ʱ�ȭ ���� �Ͽ���.
    }
    //shap ģ���� ������ ���� ���� ó�� ȭ���� �����ִ� ģ����.
    if(shap==1){
    LCD_Clear();
    Go_To_Home();
    countNum=0;
    m2=0; d2=0;
    m1=0; d1=0;
    m3=0;
    comp=0;
    }
             
        for(row_count = 0; row_count < 4; row_count++)//Ű�е� ���� �ϰſ��� ������. 
        {
            col_count = Scan_Col(row_count);        
            Num = KeyNumScan(row_count, col_count);  
            delay_ms(1);
            if(Num !=-1)
            {   
                inToLCD = Num;
                //��� �ܿ��� �ƹ��� ��ư�� ������ �� ������ ���� ex) Ȩȭ�鿡�� 0~9Ű ������ �ҿ���� m1,m2,#Ű�� �۵���. 
                if(countNum <9){
                SelectNum();//���� ���� ���� ȭ�鿡 �ٿ��ִ� �Լ�.
                }
                
                //d1�� ��й�ȣ ���� ȭ�鿡�� ����� �� �����ִ� ģ���� 1�̸� �۵� 0�̸� ���۵�.
                if(d1==1){
                    if(inToLCD <10){countNum++;}//���� 0~9�� �������� �Ǹ� ī��Ʈ�� ���°���.
                    if(countNum == 4)   //ī��Ʈ�� 4�϶� �� 4�ڸ� ���ڰ� �ԷµǸ� ������ �����ϰԵ�.
                    {
                        Comp_Ho_To_int(); //���� ���� 4���� ���� comp_ho��  int ������ �ִ� ��!.
                        
                        if(comp_ho>1000 & comp_ho<1011)     //1001~1010 ������ ���� ������ ������ ��й�ȣ ������ + ���� �Է��� ȣ�� ǥ��.
                        {
                            Cursor_shift(RIGHT);
                            Show_Home_Password();
                            LCD_pos(1,2);
                            LCD_CHAR(48+num_in[3]); //���� �Է��� ȣ�� ���ٺ��� �ƽ�Ű �ڵ� ����ؼ� 48�����ذ���.
                            LCD_CHAR(48+num_in[2]);
                            LCD_CHAR(48+num_in[1]);
                            LCD_CHAR(48+num_in[0]);
                            Num_to_int();
                            LCD_pos(1,7);
                            LCD_Comm(0x0f); // ��ũ ��� �����ϵ��� ���ִ°�.                           
                            }
                        else{m1=1; countNum=0;} //���� 1001~1010 �̿��� ���̸� �ٽ� ȣ �Է�ȭ������ ���ư�.
                      }  
                            if((countNum==5)|(countNum==6)|(countNum==7)|(countNum==8)) //��й�ȣ �Է½ÿ� *�� ǥ����.
                            {
                            LCD_Comm(0x0f); // ��ũ ���!.                         
                            LCD_pos(1,countNum+2);
                            LCD_STR(star);
                             } 

                            if(countNum == 8)//ȣ�� �Է��ϰ� ��й�ȣ4�ڸ� �Է��ϸ� �ش� ȣ���� ��й�ȣ�� ���� �� �� �ֵ��� �Ѱ���.
                            {change_Password();
                            countNum =0;
                            d1=0; 
                            LCD_Comm(0x0c); // Ŀ�� �����ֱ�.
                            countNum =9;
                            }

                }
                //d4�� ������ �������� #�� ������ ���� �ϴ� ģ����.
                if(d4==1){
                LCD_Comm(0x0e); // Display ON/OFF
                if(inToLCD <10){countNum++;}
                    if(countNum == 4){
                    Num_to_int();
                        if(sum>1000 & sum <1011) // ������ ���������� ȣ���� �ִ��� ���� Ȯ���ϱ� ���� �۾���.
                        {
                        LCD_pos(0,7);
                        LCD_STR("Press PW!");
                        LCD_pos(1,1);
                        LCD_STR(PressPW);
                        LCD_pos(1,4);
                        LCD_Comm(0x0f); // ��ũ ���ִ� ����.
                        }
                        else {shap=1; countNum =0;}
                    }
                    
                    // ���� ǥ���ϴ� �۾� ���� ������.
                    if((countNum==5)|(countNum==6)|(countNum==7)|(countNum==8)){
                    LCD_Comm(0x0f); // ��ũ ���ִ� ��.                            
                    LCD_pos(1,countNum-1);
                    LCD_STR(star);
                    }
                    if(countNum == 8){
                    LCD_Comm(0x0c ); // Ŀ�������ֱ�!.
                    countNum =9;                           
                    }
                    m3=0;
                    Switch_Verify(); // m3�� ���� �ޱ����ؼ� ����ġ�� �޴� �۾� �ٽ� ����.
                    if(m3 == 1){
                    Home_password_compare(); // �Լ��� �״�� ��й�ȣ ���ϴ� ����, 1�̸� ��ġ 2�̸� ����ġ.
                        if(comp ==1){
                        LCD_pos(1,1);
                        LCD_STR(rightPW);
                        SSound(Do);
                        SSound(Mi);
                        SSound(Sol);
                        d4=0;
                        m3=0;
                        countNum=9;
                        LCD_Comm(0x0c); //Ŀ�������ֱ�.
                        }
                        
                        if(comp ==2){
                        LCD_Clear();
                        Go_To_Home();
                        Show_Home_Ho();
                        LCD_pos(0,7);
                        LCD_STR("Press PW!");
                        LCD_pos(1,1);
                        LCD_STR(PressPW);
                        LCD_pos(1,4);
                        LCD_Comm(0x0f);                       
                        comp=0;
                        countNum=4;
                        SSound(Sol);
                        SSound(Mi);
                        SSound(Do);
                        m3=0;
                        }

                    }
                }
             }
        }
    }
 }
