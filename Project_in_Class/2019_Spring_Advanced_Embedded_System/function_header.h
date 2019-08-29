int car_num_input();
int select_mode();
int parking_lot_in(int parking_lot_state[8]);
int parking_lot_out(int my_car_locate);


int car_num_input(){

	if((frame_fd = open("/dev/fb0",O_RDWR))<0) {
		perror("Frame Buffer Open Error!");
		exit(1);
	}


	if((check=ioctl(frame_fd,FBIOGET_VSCREENINFO,&fvs))<0) {
		perror("Get Information Error - VSCREENINFO!");
		exit(1);
	}

	if(lseek(frame_fd, 0, SEEK_SET) < 0) {

		// Set Pixel Map

		perror("LSeek Error.");

		exit(1);

	}

	car_num_input_mode();

	int fd, ret;
	int re_car_num=0;
	int x, y,i;
	i=0;
	int write_x, write_y;
	write_x = 250;
	write_y = 350;
	const char* evdev_path = "/dev/input/by-path/platform-imx-i2c.2-event";
	struct input_event iev[3];
	unsigned int car_num[4] = {0,};

	fd = open(evdev_path, O_RDONLY);
	if(fd < 0) {
		perror("error: could not open evdev");
		return -1;
	}

	while(1)
	{
		ret = read(fd, iev, sizeof(struct input_event)*3);
		if(ret < 0) {
			perror("error: could not read input event");
			break;
		}
		if(iev[0].type == EV_REL && iev[0].code == REL_X)
			x = iev[0].value;
		if(iev[1].type == EV_REL && iev[1].code == REL_Y)
			y = iev[1].value;


		if(iev[0].type ==1 && iev[0].code==330 && iev[0].value ==1){
			x = iev[1].value;
			y = iev[2].value;
			if(x>100 && x<200 && y>50 && y<150){
				printf("Butten 1\n");
				if(i <4){
				num_1_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 1;
				}
			}else if(x>250 && x<350 && y>50 && y<150){
				printf("Butten 2\n");
				if(i <4){
				num_2_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 2;
				}
			}else if(x>400 && x<500 && y>50 && y<150){
				printf("Butten 3\n");
				if(i <4){
				num_3_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 3;
				}
			}else if(x>550 && x<650 && y>50 && y<150){
				printf("Butten 4\n");
				if(i <4){
				num_4_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 4;
				}
			}else if(x>700 && x<800 && y>50 && y<150){
				printf("Butten 5\n");
				if(i <4){
				num_5_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 5;
				}
			}else if(x>100 && x<200 && y>200 && y<300){
				printf("Butten 6\n");
				if(i <4){
				num_6_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 6;
				}
			}else if(x>250 && x<350 && y>200 && y<300){
				printf("Butten 7\n");
				if(i <4){
				num_7_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 7;}
			}else if(x>400 && x<500 && y>200 && y<300){
				if(i <4){
				printf("Butten 8\n");
				num_8_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 8;}
			}else if(x>550 && x<650 && y>200 && y<300){
				printf("Butten 9\n");
				if(i <4){
				num_9_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 9;}
			}else if(x>700 && x<800 && y>200 && y<300){
				printf("Butten 0\n");
				if(i <4){
				num_0_make(write_x,write_y);
				write_x = write_x +150;
				car_num[i++] = 0;}
			}else if(x>850 && x<980 && y>50 && y<150){
				printf("Butten ok\n");
				if(i == 4){
					i=0;
					write_x = 250;
					re_car_num = 1;
					make_rect(100, 980, 350, 450);
					break;
				}
			}else if(x>850 && x<980 && y>200 && y<300){
				printf("Butten del\n");
				if(i>0 && i<5){
					write_x = write_x - 150;
					make_rect(write_x, write_x+100, 350, 450);
					i = i-1;
				}else if(i==0){
					make_rect(write_x, write_x+100, 350, 450);
					write_x= 250;
				}

			}else if(x>880 && x<960 && y>460 && y<560){
				printf("Butten X\n");
				re_car_num = -4;
				break;

			}

		}

	}
	close(fd);
	close(frame_fd);
	if (re_car_num != -4){
		re_car_num = car_num[0]*1000 + car_num[1]*100 + car_num[2]*10 + car_num[3]; }
	return re_car_num;

}


int select_mode(){

	if((frame_fd = open("/dev/fb0",O_RDWR))<0) {
		perror("Frame Buffer Open Error!");
		exit(1);
	}


	if((check=ioctl(frame_fd,FBIOGET_VSCREENINFO,&fvs))<0) {
		perror("Get Information Error - VSCREENINFO!");
		exit(1);
	}

	if(lseek(frame_fd, 0, SEEK_SET) < 0) {

		// Set Pixel Map

		perror("LSeek Error.");

		exit(1);

	}

	init_display();
	make_rect(250,450,200,400);
	make_rect(550,850,200,400);

	//In
	make_num(260,340,210,230);
	make_num(260,340,370,390);
	make_num(280,320,230,370);

	make_num(360,380,210,390);
	make_num(420,440,210,390);
	make_line_cross_down_2(380,210,40,20);

	//out
	make_num(560,640,210,230);
	make_num(560,640,370,390);
	make_num(560,580,230,370);
	make_num(620,640,230,370);

	make_num(660,680,210,390);
	make_num(680,720,370,390);
	make_num(720,740,210,390);

	make_num(760,840,210,230);
	make_num(790,810,230,390);

	int fd, ret;
	int x, y,mode;
	const char* evdev_path = "/dev/input/by-path/platform-imx-i2c.2-event";
	struct input_event iev[3];


	fd = open(evdev_path, O_RDONLY);
	if(fd < 0) {
		perror("error: could not open evdev");
		return -1;
	}

	while(1)
	{
		ret = read(fd, iev, sizeof(struct input_event)*3);
		if(ret < 0) {
			perror("error: could not read input event");
			break;
		}
		if(iev[0].type == EV_REL && iev[0].code == REL_X)
			x = iev[0].value;
		if(iev[1].type == EV_REL && iev[1].code == REL_Y)
			y = iev[1].value;


		if(iev[0].type ==1 && iev[0].code==330 && iev[0].value ==1){
			x = iev[1].value;
			y = iev[2].value;
			if(x>250 && x<450 && y>200 && y<400){
				printf("mode In\n");
				mode = 1;
				break;

			}else if(x>550 && x<850 && y>200 && y<400){
				printf("mode Out\n");
				mode = 2;
				break;

			}

		}

	}
	close(fd);
	close(frame_fd);

	return mode;
}


int parking_lot_in(int parking_lot_state[8]){

	if((frame_fd = open("/dev/fb0",O_RDWR))<0) {
		perror("Frame Buffer Open Error!");
		exit(1);
	}


	if((check=ioctl(frame_fd,FBIOGET_VSCREENINFO,&fvs))<0) {
		perror("Get Information Error - VSCREENINFO!");
		exit(1);
	}

	if(lseek(frame_fd, 0, SEEK_SET) < 0) {

		// Set Pixel Map

		perror("LSeek Error.");

		exit(1);

	}




	init_display();

	make_rect(0,800,0,200);
	make_rect(0,800,400,600);

	int i=0,k=0;
	for(i=0; i<4; i++){
		if(parking_lot_state[i] == 1){
			make_rect_red(i*200, i*200 +200, 0,200);
		}
	}
	for(i=4; i<8; i++){
		if(parking_lot_state[i] == 1){
			make_rect_red(k*200, k*200 +200, 400,600);
		}
		k++;
	}

	//park_line
	make_num(180,200,0,200);
	make_num(380,400,0,200);
	make_num(580,600,0,200);

	make_num(180,200,400,600);
	make_num(380,400,400,600);
	make_num(580,600,400,600);

	make_num(0,800,180,200);
	make_num(0,800,400,420);

	make_num(800,824,0,600);

	//ok
	make_rect(850, 980, 50, 150);

	make_num(860,920,60,80);
	make_num(860,920,120,140);
	make_num(860,880,80,120);
	make_num(900,920,80,120);

	make_num(930,950,60,140);
	make_line_cross_down(950,100,20,20);
	make_line_cross_up(950,100,20,20);

	//X
	make_rect(880,960,460,560);
	make_line_cross_down(890,470,60,20);
	make_line_cross_up(890,550,60,20);

	//////////////////////////////////

	int fd, ret;
	int x, y,park_num = -1;
	const char* evdev_path = "/dev/input/by-path/platform-imx-i2c.2-event";
	struct input_event iev[3];


	fd = open(evdev_path, O_RDONLY);
	if(fd < 0) {
		perror("error: could not open evdev");
		return -1;
	}

	while(1)
	{
		ret = read(fd, iev, sizeof(struct input_event)*3);
		if(ret < 0) {
			perror("error: could not read input event");
			break;
		}
		if(iev[0].type == EV_REL && iev[0].code == REL_X)
			x = iev[0].value;
		if(iev[1].type == EV_REL && iev[1].code == REL_Y)
			y = iev[1].value;


		if(iev[0].type ==1 && iev[0].code==330 && iev[0].value ==1){
			x = iev[1].value;
			y = iev[2].value;
			if(x>0 && x<180 && y>0 && y<180){
				park_num = 0;
				if(parking_lot_state[park_num] ==1){
					park_num = -1;
					Buzzer_Sound(80000);
				}
				printf("park_num 0\n");
			}else if(x>200 && x<380 && y>0 && y<180){
				printf("park_num 1\n");
				park_num = 1;
				if(parking_lot_state[park_num] ==1){
					park_num = -1;
					Buzzer_Sound(80000);
				}

			}else if(x>400 && x<580 && y>0 && y<180){
				printf("park_num 2\n");
				park_num = 2;
				if(parking_lot_state[park_num] ==1){
					park_num = -1;
					Buzzer_Sound(80000);
				}

			}else if(x>600 && x<780 && y>0 && y<180){
				printf("park_num 3\n");
				park_num = 3;
				if(parking_lot_state[park_num] ==1){
					park_num = -1;
					Buzzer_Sound(80000);
				}

			}else if(x>0 && x<180 && y>380 && y<600){
				printf("park_num 4\n");
				park_num = 4;
				if(parking_lot_state[park_num] ==1){
					park_num = -1;
					Buzzer_Sound(80000);
				}

			}else if(x>200 && x<380 && y>380 && y<600){
				printf("park_num 5\n");
				park_num = 5;
				if(parking_lot_state[park_num] ==1){
					park_num = -1;
					Buzzer_Sound(80000);
				}

			}else if(x>400 && x<580 && y>380 && y<600){
				printf("park_num 6\n");
				park_num = 6;
				if(parking_lot_state[park_num] ==1){
					park_num = -1;
					Buzzer_Sound(80000);
				}

			}else if(x>600 && x<780 && y>380 && y<600){
				printf("park_num 7\n");
				park_num = 7;
				if(parking_lot_state[park_num] ==1){
					park_num = -1;
					Buzzer_Sound(80000);
				}

			}else if(x>850 && x<980 && y>50 && y<150){
				printf("Butten ok\n");
				if(park_num != -1){
				break;
				}
			}else if(x>880 && x<960 && y>460 && y<560){
				printf("Butten X\n");
				park_num = -4;
				break;

			}

		}

	}
	close(fd);
	close(frame_fd);
	return park_num;
}


int parking_lot_out(int my_car_locate){

	if((frame_fd = open("/dev/fb0",O_RDWR))<0) {
		perror("Frame Buffer Open Error!");
		exit(1);
	}


	if((check=ioctl(frame_fd,FBIOGET_VSCREENINFO,&fvs))<0) {
		perror("Get Information Error - VSCREENINFO!");
		exit(1);
	}

	if(lseek(frame_fd, 0, SEEK_SET) < 0) {

		// Set Pixel Map

		perror("LSeek Error.");

		exit(1);

	}




	init_display();

	make_rect(0,800,0,200);
	make_rect(0,800,400,600);

	int i=0,k=0;
	if(my_car_locate<4){
		make_rect_red(my_car_locate*200, my_car_locate*200 +200, 0,200);
	}else if(my_car_locate >=4){
		make_rect_red((my_car_locate-4)*200, (my_car_locate-4)*200 +200, 400,600);
	}

	//park_line
	make_num(180,200,0,200);
	make_num(380,400,0,200);
	make_num(580,600,0,200);

	make_num(180,200,400,600);
	make_num(380,400,400,600);
	make_num(580,600,400,600);

	make_num(0,800,180,200);
	make_num(0,800,400,420);

	make_num(800,824,0,600);

	//ok
	make_rect(850, 980, 50, 150);

	make_num(860,920,60,80);
	make_num(860,920,120,140);
	make_num(860,880,80,120);
	make_num(900,920,80,120);

	make_num(930,950,60,140);
	make_line_cross_down(950,100,20,20);
	make_line_cross_up(950,100,20,20);
	//////////////////////////////////


	int fd, ret;
	int x, y,park_num = -1;
	const char* evdev_path = "/dev/input/by-path/platform-imx-i2c.2-event";
	struct input_event iev[3];


	fd = open(evdev_path, O_RDONLY);
	if(fd < 0) {
		perror("error: could not open evdev");
		return -1;
	}

	while(1)
	{
		ret = read(fd, iev, sizeof(struct input_event)*3);
		if(ret < 0) {
			perror("error: could not read input event");
			break;
		}
		if(iev[0].type == EV_REL && iev[0].code == REL_X)
			x = iev[0].value;
		if(iev[1].type == EV_REL && iev[1].code == REL_Y)
			y = iev[1].value;


		if(iev[0].type ==1 && iev[0].code==330 && iev[0].value ==1){
			x = iev[1].value;
			y = iev[2].value;
			if(x>850 && x<980 && y>50 && y<150){
				printf("Butten ok\n");
				break;
			}

		}

	}
	close(fd);
	close(frame_fd);
	return 0;

}
