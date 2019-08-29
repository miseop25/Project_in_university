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
//처음에는 우리가 쓸 변수 및 상수들을 정리해 논거임.
int m1,m2,m3,m4;  //m1,2,3,4 버튼 눌렀을때 사용하는 변수. 
int d1,d2,d3,d4;   //m1,2,3,4# 눌렀을때 기능을 가능하게 하는 변수 .
int inToLCD;
int comp=0;     //비교할때 사용하는 변수.
int shap=0;     //# 버튼 눌렀을때 사용하는 함수.
unsigned int home[10]= {1001,1002,1003,1004,1005,1006,1007,1008,1009,1010};         // 10개의 호수 설정
unsigned int homePassword[10]= {1000,2000,3000,4000,5000,6000,7000,8000,9000,1010}; //호수 초기 비밀번호 설정.
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

//LCD에 출련된 4자리 숫자 인티져로 옮겨주는 친구 & num_in 초기화 시켜줌.
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

//내가 입력한 호수의 비밀번호를 보여주는 함수.
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

//호수에 해당하는 비밀번호가 맞는지 알아봐 주는 친구
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

//내가 입력한 호수를 다시 LCD에 출력하는 함수.
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

//비밀번호 새로 설정해주는 친구.
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

//비밀번호 설정하는 화면 보여주는 친구.
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

//집으로 들어가기 위해 시작되는 첫단계인 친구.
void Go_To_Home(){
   Byte PressHo[] = "R";
   LCD_pos(0,1);
   LCD_STR(PressHo);
   LCD_Comm(0x0e); // 커서 켜주기.
   LCD_pos(0,2);
   shap=0;
   d4=1;
}

//m1,m2,m3,m4,# 값 읽어오는 친구
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

//키패드를 통해 받아온 숫자를 LCD에 출력해 주는 친구.
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

void Port_set()       //내가 사용할 포트들 정라
{
    DDRC = 0x0f; //상위 4bit 입력, 하위 4bit 출력 키패드 
    DDRD= 0xf0; // sw 상위 4개 입력으로 설정
    PORTC = 0xf0;//PORTC의 상위 4bit 내부 풀업 설정 키패드
    DDRG|=(1<<4); // 부저음 관련 포트 설정.
}

int Scan_Col(int row)  //Row 값(row = 0이면 첫번째 행, row = 3이면 네번째 행 선택)에 따라 Column 스캔 함수, 출력 Col1(1열) = 0x01, Col2(2열) = 0x02, Col3(3열) = 0x04
{
    int col_temp=0 , col_num =0;    //col_temp : column값 임시 저장 변수, col_num : column 값
    PORTC =~(1<<row);          //row 값에 따라 포트 C의 하위 비트 출력 선택  ex)3번째 줄(row = 2) 선택, PORTC = 0b11111011        
    delay_us(1);                //인식하기까지 시간이 걸리기 때문에 딜레이
    col_temp = PINC>>4;         //포트 C의 입력값 스캔(포트 C의 상위 4비트 입력값만 필요, 오른쪽으로 4비트 이동) ex)col_temp = 0b0000???? = 0x0? 
    col_num =  col_temp & 0x0f; //column 값은 하위 비트만 필요하므로 0x0f AND 연산 ex)col_num = 0b0000???? = 0x0?, 버튼이 눌렸다면  0x01, 0x02, 0x04로 출력
    return col_num; //Column 값 반환                  
}
int KeyNumScan(int row, int col_data) //row와 column 값에 따른 숫자 변환
{
    int sel_num = -1; //select number선택, 버튼에 따른 숫자 저장 변수, 초기값 -1 : 아무것도 누르지 않은 상태  
           
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
            if(col_data == 0x01) sel_num = 10;  // *에 해당하는 값 10 
            if(col_data == 0x02) sel_num = 0;   // 0에 해당하는 값 0
            if(col_data == 0x04) sel_num = 11;  // #에 해당하는 값 11 
            if(col_data == 0x08) sel_num=15;  //m4
            break; 
        default:break;
    }
    return sel_num;     //선택된 숫자값 반환.
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
    PortInit();//LCD포트 초기화
    Port_set(); //내가 사용하는 포트 사용 설정
    LCD_Init();//LCD 화면 초기화
    LCD_pos(0,2);
    LCD_STR(str);
    LCD_pos(1,2);
    LCD_STR(str1);
    LCD_Comm(0x0c); // Display ON/OFF
    //LCD에 초기 화면 설정 
        
    while(1){
    
    Switch_Verify();//m1,m2,m3,m4,#의 기능을 수행하기 위해서 일단 읽어본다.
    if(m1==1){
        m2=0; d2=0;
        m1=0; d1=0;
        m3=0;
        shap=0;  d4=0;
        countNum=0;
        LCD_Clear(); 
        Set_password_Display();//m1의 버튼을 눌렀을때에 비밀번호 설정 화면을 표시하게 된다.
        }
    //m2는 LCD의 화면을 초기의 화면으로 설정해 주는 친구임.
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
    LCD_Comm(0x0c); // 커서지워주기.
    //모든 변수값 초기화 진행 하였음.
    }
    //shap 친구는 집으로 들어가기 위해 처음 화면을 보여주는 친구임.
    if(shap==1){
    LCD_Clear();
    Go_To_Home();
    countNum=0;
    m2=0; d2=0;
    m1=0; d1=0;
    m3=0;
    comp=0;
    }
             
        for(row_count = 0; row_count < 4; row_count++)//키패드 관련 일거오는 포문임. 
        {
            col_count = Scan_Col(row_count);        
            Num = KeyNumScan(row_count, col_count);  
            delay_ms(1);
            if(Num !=-1)
            {   
                inToLCD = Num;
                //기능 외에는 아무리 버튼을 눌러도 더 눌리지 않음 ex) 홈화면에서 0~9키 눌러도 소용없음 m1,m2,#키만 작동함. 
                if(countNum <9){
                SelectNum();//내가 누른 숫자 화면에 뛰워주는 함수.
                }
                
                //d1은 비밀번호 설정 화면에서 기능을 온 시켜주는 친구임 1이면 작동 0이면 미작동.
                if(d1==1){
                    if(inToLCD <10){countNum++;}//숫자 0~9가 눌러지게 되면 카운트를 세는거임.
                    if(countNum == 4)   //카운트가 4일때 즉 4자리 숫자가 입력되면 이일을 진행하게됨.
                    {
                        Comp_Ho_To_int(); //내가 받은 4개의 값을 comp_ho에  int 값으로 넣는 것!.
                        
                        if(comp_ho>1000 & comp_ho<1011)     //1001~1010 사이의 값이 있으면 기존의 비밀번호 보여줌 + 내가 입력한 호수 표시.
                        {
                            Cursor_shift(RIGHT);
                            Show_Home_Password();
                            LCD_pos(1,2);
                            LCD_CHAR(48+num_in[3]); //내가 입력한 호수 복붙복붙 아스키 코드 사용해서 48더해준거임.
                            LCD_CHAR(48+num_in[2]);
                            LCD_CHAR(48+num_in[1]);
                            LCD_CHAR(48+num_in[0]);
                            Num_to_int();
                            LCD_pos(1,7);
                            LCD_Comm(0x0f); // 블링크 기능 가능하도록 해주는것.                           
                            }
                        else{m1=1; countNum=0;} //만약 1001~1010 이외의 값이면 다시 호 입력화면으로 돌아감.
                      }  
                            if((countNum==5)|(countNum==6)|(countNum==7)|(countNum==8)) //비밀번호 입력시에 *로 표시함.
                            {
                            LCD_Comm(0x0f); // 블링크 기능!.                         
                            LCD_pos(1,countNum+2);
                            LCD_STR(star);
                             } 

                            if(countNum == 8)//호수 입력하고 비밀번호4자리 입력하면 해당 호수의 비밀번호를 변경 할 수 있도록 한거임.
                            {change_Password();
                            countNum =0;
                            d1=0; 
                            LCD_Comm(0x0c); // 커서 지워주기.
                            countNum =9;
                            }

                }
                //d4는 집으로 들어가기위해 #을 누르면 일을 하는 친구임.
                if(d4==1){
                LCD_Comm(0x0e); // Display ON/OFF
                if(inToLCD <10){countNum++;}
                    if(countNum == 4){
                    Num_to_int();
                        if(sum>1000 & sum <1011) // 위에와 마찬가지로 호수가 있는지 부터 확인하기 위한 작업임.
                        {
                        LCD_pos(0,7);
                        LCD_STR("Press PW!");
                        LCD_pos(1,1);
                        LCD_STR(PressPW);
                        LCD_pos(1,4);
                        LCD_Comm(0x0f); // 블링크 해주는 거임.
                        }
                        else {shap=1; countNum =0;}
                    }
                    
                    // 별로 표시하는 작업 위와 동일함.
                    if((countNum==5)|(countNum==6)|(countNum==7)|(countNum==8)){
                    LCD_Comm(0x0f); // 블링크 해주는 것.                            
                    LCD_pos(1,countNum-1);
                    LCD_STR(star);
                    }
                    if(countNum == 8){
                    LCD_Comm(0x0c ); // 커서지워주기!.
                    countNum =9;                           
                    }
                    m3=0;
                    Switch_Verify(); // m3의 값을 받기위해서 스위치값 받는 작업 다시 실행.
                    if(m3 == 1){
                    Home_password_compare(); // 함수명 그대로 비밀번호 비교하는 거임, 1이면 일치 2이면 불일치.
                        if(comp ==1){
                        LCD_pos(1,1);
                        LCD_STR(rightPW);
                        SSound(Do);
                        SSound(Mi);
                        SSound(Sol);
                        d4=0;
                        m3=0;
                        countNum=9;
                        LCD_Comm(0x0c); //커서지워주기.
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
