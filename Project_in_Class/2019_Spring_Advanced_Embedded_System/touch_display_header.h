typedef unsigned short int U32;
typedef short U16;

int check;
int frame_fd;
U16 pixel;
int offset;
int posx1, posy1, posx2, posy2;
int repx, repy;
struct fb_var_screeninfo fvs;

U16 makepixel(U32  r, U32 g, U32 b);
void swap(int *swapa, int *swapb);

void make_rect(int x1, int x2, int y1, int y2);
void make_rect_red(int x1, int x2, int y1, int y2);
void make_num(int x1, int x2, int y1, int y2);

void make_line_cross_down(int x, int y, int x_len, int y_len);
void make_line_cross_down_2(int x, int y, int x_len, int y_len);
void make_line_cross_up(int x, int y, int x_len, int y_len);

void num_1_make(int start_x, int start_y);
void num_2_make(int start_x, int start_y);
void num_3_make(int start_x, int start_y);
void num_4_make(int start_x, int start_y);
void num_5_make(int start_x, int start_y);
void num_6_make(int start_x, int start_y);
void num_7_make(int start_x, int start_y);
void num_8_make(int start_x, int start_y);
void num_9_make(int start_x, int start_y);
void num_0_make(int start_x, int start_y);

void init_display();
void car_num_input_mode();




U16 makepixel(U32  r, U32 g, U32 b)
{
	 U16 x = (U16)(r >> 3);
	 U16 y = (U16)(g >> 2);
	 U16 z = (U16)(b >> 3);

	 return (z|(x<<11)|(y<<5));
}

void swap(int *swapa, int *swapb) {
     int temp;
     if(*swapa > *swapb) {
         temp = *swapb;
         *swapb = *swapa;
         *swapa = temp;
    }
}

void make_rect(int x1, int x2, int y1, int y2){

	pixel = makepixel(0,255,0);   // 색상 만들기
	posx1 = x1;  // 사각형의 크기를 결정한다.
	posx2 = x2;  // rect(100,150,120,170)을 구현한 것이다.
	posy1 = y1;
	posy2 = y2;
	for(repy=posy1; repy < posy2; repy++) {
		offset = repy * fvs.xres * (sizeof(pixel)) + posx1 * (sizeof(pixel));
		if(lseek(frame_fd, offset, SEEK_SET) < 0) {
			perror("LSeek Error!");
			exit(1);
		}
		for(repx = posx1; repx <= posx2; repx++)
			write(frame_fd, &pixel,(sizeof(pixel)));
	}
}

void make_rect_red(int x1, int x2, int y1, int y2){

	pixel = makepixel(255,0,0);   // 색상 만들기
	posx1 = x1;  // 사각형의 크기를 결정한다.
	posx2 = x2;  // rect(100,150,120,170)을 구현한 것이다.
	posy1 = y1;
	posy2 = y2;
	for(repy=posy1; repy < posy2; repy++) {
		offset = repy * fvs.xres * (sizeof(pixel)) + posx1 * (sizeof(pixel));
		if(lseek(frame_fd, offset, SEEK_SET) < 0) {
			perror("LSeek Error!");
			exit(1);
		}
		for(repx = posx1; repx <= posx2; repx++)
			write(frame_fd, &pixel,(sizeof(pixel)));
	}
}


void init_display(){

	pixel = makepixel(255,255,255);

	// 색상 만들기
	posx1 = 0;  // 사각형의 크기를 결정한다.
	posx2 = 1048;  // rect(100,150,120,170)을 구현한 것이다.
	posy1 = 0;
	posy2 = 600;
	for(repy=posy1; repy < posy2; repy++) {
		offset = repy * fvs.xres * (sizeof(pixel)) + posx1 * (sizeof(pixel));
		if(lseek(frame_fd, offset, SEEK_SET) < 0) {
			perror("LSeek Error!");
			exit(1);
		}
		for(repx = posx1; repx <= posx2; repx++)
			write(frame_fd, &pixel,(sizeof(pixel)));
	}


}



void make_line_cross_down(int x, int y, int x_len, int y_len){
	int posx, posy, i, k;
	i=0; k=0;
	pixel = makepixel(0,0,0);   // 색상 만들기
	posx = x;  // 사각형의 크기를 결정한다.
	posy = y;
	for(k=0; k <=y_len; k++){
		for(i = 0 ; i <=x_len; i++){
			offset = posy * fvs.xres * (sizeof(pixel)) + posx * (sizeof(pixel));
			if(lseek(frame_fd, offset, SEEK_SET) < 0) {

				perror("LSeek Error!");
					exit(1);
			}
			write(frame_fd, &pixel,(sizeof(pixel)));
			posx++;
			posy++;
		}
		posx = x;
		posy = y+k;
	}

}
void make_line_cross_down_2(int x, int y, int x_len, int y_len){
	int posx, posy, i, k;
	i=0; k=0;
	pixel = makepixel(0,0,0);   // 색상 만들기
	posx = x;  // 사각형의 크기를 결정한다.
	posy = y;
	for(k=0; k <=y_len; k++){
		for(i = 0 ; i <=x_len; i++){
			offset = posy * fvs.xres * (sizeof(pixel)) + posx * (sizeof(pixel));
			if(lseek(frame_fd, offset, SEEK_SET) < 0) {

				perror("LSeek Error!");
					exit(1);
			}
			write(frame_fd, &pixel,(sizeof(pixel)));
			posx++;
			posy = posy+4;
		}
		posx = x;
		posy = y+k;
	}

}

void make_line_cross_up(int x, int y, int x_len, int y_len){
	int posx, posy, i, k;
	i=0; k=0;
	pixel = makepixel(0,0,0);   // 색상 만들기
	posx = x;  // 사각형의 크기를 결정한다.
	posy = y;
	for(k=0; k <=y_len; k++){
		for(i = 0 ; i <=x_len; i++){
			offset = posy * fvs.xres * (sizeof(pixel)) + posx * (sizeof(pixel));
			if(lseek(frame_fd, offset, SEEK_SET) < 0) {

				perror("LSeek Error!");
					exit(1);
			}
			write(frame_fd, &pixel,(sizeof(pixel)));
			posx++;
			posy--;
		}
		posx = x;
		posy = y-k;
	}

}


void make_num(int x1, int x2, int y1, int y2){

	pixel = makepixel(0,0,0);   // 색상 만들기
	posx1 = x1;  // 사각형의 크기를 결정한다.
	posx2 = x2;  // rect(100,150,120,170)을 구현한 것이다.
	posy1 = y1;
	posy2 = y2;

	for(repy=posy1; repy < posy2; repy++) {
		offset = repy * fvs.xres * (sizeof(pixel)) + posx1 * (sizeof(pixel));
		if(lseek(frame_fd, offset, SEEK_SET) < 0) {
			perror("LSeek Error!");
			exit(1);
		}

		for(repx = posx1; repx <= posx2; repx++)
			write(frame_fd, &pixel,(sizeof(pixel)));
	}



}

void num_1_make(int start_x, int start_y){
	make_num(start_x+35,start_x+65,start_y+10,start_y+90);
}

void num_2_make(int start_x, int start_y){
	make_num(start_x+10,start_x+90,start_y+10,start_y+26);
	make_num(start_x+60,start_x+90,start_y+26,start_y+42);
	make_num(start_x+10,start_x+90,start_y+42,start_y+58);
	make_num(start_x+10,start_x+40,start_y+58,start_y+74);
	make_num(start_x+10,start_x+90,start_y+74,start_y+90);
}

void num_3_make(int start_x, int start_y){
	make_num(start_x+10,start_x+90,start_y+10,start_y+26);
	make_num(start_x+60,start_x+90,start_y+26,start_y+42);
	make_num(start_x+10,start_x+90,start_y+42,start_y+58);
	make_num(start_x+60,start_x+90,start_y+58,start_y+74);
	make_num(start_x+10,start_x+90,start_y+74,start_y+90);
}

void num_4_make(int start_x, int start_y){
	make_num(start_x+10,start_x+30,start_y+10,start_y+60);
	make_num(start_x+30,start_x+90,start_y+40,start_y+60);
	make_num(start_x+50,start_x+70,start_y+10,start_y+90);

}

void num_5_make(int start_x, int start_y){

	make_num(start_x+10,start_x+90,start_y+10,start_y+26);
	make_num(start_x+10,start_x+40,start_y+26,start_y+42);
	make_num(start_x+10,start_x+90,start_y+42,start_y+58);
	make_num(start_x+60,start_x+90,start_y+58,start_y+74);
	make_num(start_x+10,start_x+90,start_y+74,start_y+90);
}

void num_6_make(int start_x, int start_y){

	make_num(start_x+10,start_x+40,start_y+10,start_y+90);
	make_num(start_x+40,start_x+90,start_y+40,start_y+55);
	make_num(start_x+70,start_x+90,start_y+55,start_y+75);
	make_num(start_x+40,start_x+90,start_y+75,start_y+90);
}

void num_7_make(int start_x, int start_y){
	make_num(start_x+10,start_x+90,start_y+10,start_y+30);
	make_num(start_x+10,start_x+30,start_y+30,start_y+50);
	make_num(start_x+60,start_x+90,start_y+30,start_y+90);
}

void num_8_make(int start_x, int start_y){

	make_num(start_x+10,start_x+40,start_y+10,start_y+90);
	make_num(start_x+60,start_x+90,start_y+10,start_y+90);
	make_num(start_x+40,start_x+60,start_y+10,start_y+26);
	make_num(start_x+40,start_x+60,start_y+42,start_y+58);
	make_num(start_x+40,start_x+60,start_y+74,start_y+90);
}

void num_9_make(int start_x, int start_y){

	make_num(start_x+10,start_x+90,start_y+10,start_y+26);
	make_num(start_x+10,start_x+40,start_y+26,start_y+42);
	make_num(start_x+10,start_x+60,start_y+42,start_y+58);
	make_num(start_x+60,start_x+90,start_y+10,start_y+90);

}

void num_0_make(int start_x, int start_y){
	make_num(start_x+10,start_x+90,start_y+10,start_y+26);
	make_num(start_x+10,start_x+40,start_y+26,start_y+74);
	make_num(start_x+60,start_x+90,start_y+26,start_y+74);
	make_num(start_x+10,start_x+90,start_y+74,start_y+90);
}

void car_num_input_mode(){
	init_display();
	make_rect(100, 200, 50, 150);
	make_rect(100, 200, 200, 300);
	make_rect(250, 350, 50, 150);
	make_rect(250, 350, 200, 300);
	make_rect(400, 500, 50, 150);
	make_rect(400, 500, 200, 300);
	make_rect(550, 650, 50, 150);
	make_rect(550, 650, 200, 300);
	make_rect(700, 800, 50, 150);
	make_rect(700, 800, 200, 300);
	make_rect(850, 980, 50, 150);
	make_rect(850, 980, 200, 300);
	make_rect(100, 980, 350, 450);


	num_1_make(100,50);
	num_2_make(250,50);
	num_3_make(400,50);
	num_4_make(550,50);
	num_5_make(700,50);
	num_6_make(100,200);
	num_7_make(250,200);
	num_8_make(400,200);
	num_9_make(550,200);
	num_0_make(700,200);

	//ok
	make_num(860,920,60,80);
	make_num(860,920,120,140);
	make_num(860,880,80,120);
	make_num(900,920,80,120);

	make_num(930,950,60,140);
	make_line_cross_down(950,100,20,20);
	make_line_cross_up(950,100,20,20);

	//<-
	make_line_cross_down(860,240,40,20);
	make_line_cross_up(860,260,40,20);
	make_num(865,970,240,260);

	//X
	make_rect(880,960,460,560);
	make_line_cross_down(890,470,60,20);
	make_line_cross_up(890,550,60,20);

}
