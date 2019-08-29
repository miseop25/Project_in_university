#include <mega128.h>
#include <delay.h>


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
        case 2:               
            if(col_data == 0x01) sel_num = 4;
            if(col_data == 0x02) sel_num = 5;
            if(col_data == 0x04) sel_num = 6;
            if(col_data == 0x08) sel_num=13;  //m2
            break;
        case 1:               
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



