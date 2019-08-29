#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <linux/fb.h>
#include <linux/input.h>
#include <signal.h>
#include <string.h>
#include <time.h>

#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>


#include "touch_display_header.h"
#include "function_header.h"
#include "device_header.h"
#include "open_cv_header.h"

int car_buf, mode,time_buf,how_much, park_buf,available_park=0;
int parking_lot[8] = {0,};
int save_car_num[8] = {0,};
int save_Time_min[8] = {0,};
int led_input[8] = {0,0,0,0,0,0,0,0};
int i, input_led=0;
int car_num_buf,val,paid;


int main(int argc, char** argv) {
	pid_t pid;
	int num = 0;
	dev_led = open("/dev/fpga_led", O_RDWR);
	if (dev_led<0){
	        printf("Device fpga_led Open Error\n");
	        close(dev_led);
	        return -1;
	}

	text_lcd_show(dev_text_lcd, "  ", " ");

	for(i=0; i<8; i++){
		save_car_num[i] = -1;
	}
	num=0;
	set_led(dev_led,(char)num);
	while(1){
		step_motor(0,0,10);
		text_lcd_show(dev_text_lcd, "SELECT", "MODE");
		available_park = 0;
		for(i=0; i<8; i++){
			if(parking_lot[i] == 0){
				available_park++;
			}
		}

		FND_Display(available_park);
		mode = select_mode();
		if(mode == 1){
				text_lcd_show(dev_text_lcd, "Select ", "Parking space");
				park_buf = parking_lot_in(parking_lot);

				if(park_buf != -4){
					text_lcd_show(dev_text_lcd, "Input your", "Car number");
					car_num_buf = car_num_input();
					if(car_num_buf != -4){
						parking_lot[park_buf] = 1;
						save_car_num[park_buf] = car_num_buf;
						save_Time_min[park_buf] = time_set();
						printf("save_Time_min[park_buf] : %d \n",save_Time_min[park_buf]);

						pid = fork();
						if(pid ==0){
							for(i=0; i<8; i++) { led_input[i] == 0;}
							led_input[7-park_buf] = 1;
							for(i=0;i<8;i++)
								{if(led_input[i] == 1){num = num + power(2,i);}}
							set_led(dev_led,(char)num);
							get_us(dev_us);
							step_motor(1,0,10);
							text_lcd_show(dev_text_lcd, "Welcome", "Please enjoy");
							sleep(1);
							step_motor(0,0,10);
							num =0;
							set_led(dev_led,(char)num);
							exit(0);
						}
					}
				}


		}else if(mode == 2){
			while(1){
				car_buf = car_num_input();
				if(car_buf == -4) break;
				for(i=0; i<8;i++){
					if(save_car_num[i] == car_buf){
						break;
					}
				}
				if(i>=0 && i<8){
					pid = fork();
					if(pid ==0){
    					open_cv_camara();
    					exit(0);
					}
					val = get_push_switch(dev_push);
					if(val == 6){
						val =0;
						save_car_num[i] =-1;
						parking_lot[i] = 0;
						time_buf = time_set();
						how_much = (time_buf - save_Time_min[i])*100;
						printf("how much : %d \n",how_much);

						paid =0;
						while(paid != -1){
							How_Much_Display(paid,how_much);
							val = get_push_switch(dev_push);
							usleep(300000);
							switch(val){
								case 0 : paid = paid +100;  break;
								case 1 : paid = paid +500;  break;
								case 2 : paid = paid +1000; break;
								case 3 : paid = 0; break;
								case 4 : if(paid == how_much) paid = -1; break;
								default : paid = paid; break;
							}
						}
						parking_lot_out(i);
						step_motor(1,1,10);
						text_lcd_show(dev_text_lcd, "Good Bye", "See you");
						sleep(1);
						break;
					}else break;

				}
				Buzzer_Sound(80000);
			}

		}

		for(i=0; i<8;i++){
			printf("%d \t %d \n",parking_lot[i],save_car_num[i]);
		}
	}

	return 0;

}
