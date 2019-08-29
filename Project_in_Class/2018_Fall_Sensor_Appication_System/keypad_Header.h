#include <mega128.h>
#include <delay.h>


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
            if(col_data == 0x01) sel_num = 10;  // *�� �ش��ϴ� �� 10 
            if(col_data == 0x02) sel_num = 0;   // 0�� �ش��ϴ� �� 0
            if(col_data == 0x04) sel_num = 11;  // #�� �ش��ϴ� �� 11 
            if(col_data == 0x08) sel_num=15;  //m4
            break; 
        default:break;
    }
    return sel_num;     //���õ� ���ڰ� ��ȯ.
}



