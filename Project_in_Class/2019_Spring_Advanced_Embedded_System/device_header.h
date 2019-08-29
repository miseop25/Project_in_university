#define BUZZER_DEVICE "/dev/fpga_buzzer"
#define FND_DEVICE "/dev/fpga_fnd"
#define FPGA_STEP_MOTOR_DEVICE "/dev/fpga_step_motor"

#define MAX_DIGIT 4

#define MOTOR_ATTRIBUTE_ERROR_RANGE 4

#define MAX_BUTTON_PUSH 9
#define MAX_BUFF_LCD 32
#define LINE_BUFF 16

unsigned char quit = 0;
void usage(char* dev_info);
int dev_text_lcd;
int dev_us;
int dev_push;

int Buzzer_Sound(int usec);
int FND_Display(int value);
int set_led(int dev, char argv);
int power(int x, int y);
int step_motor(int power, int dir, int speed);
void text_lcd_show(int dev, char* argv1, char* argv2);
int get_us(int dev_us);
int time_set();
void user_signal1(int sig);
int get_push_switch(int dev_push);
int How_Much_Display(int paid , int how_much);



int Buzzer_Sound(int usec){
   int dev_buzzer;
    unsigned char state=0;
    unsigned char retval;
    unsigned char data;
    dev_buzzer = open(BUZZER_DEVICE, O_RDWR);
    if (dev_buzzer<0) {
        printf("Device open error : %s\n",BUZZER_DEVICE);
        exit(1);
    }

            data=1;
            retval=write(dev_buzzer,&data,1);
            if(retval<0) {
                printf("Write Error!\n");
                return -1;
            }
	    usleep(usec);
            data=0;
	    retval=write(dev_buzzer,&data,1);
            if(retval<0) {
                printf("Write Error!\n");
                return -1;
            }

	close(dev_buzzer);
}


int FND_Display(int value)
{
	int dev;
	char data[4];
	unsigned char retval;
	int i;
	int str_size;
	data[0]=value/1000;
	data[1]=(value/100)%10;
	data[2]=(value/10)%100%10;
	data[3]=(value%1000)%100%10;


	dev = open(FND_DEVICE, O_RDWR);

	retval=write(dev,&data,4);


	close(dev);


}


int dev_led;

//LED
int set_led(int dev, char argv)
{
        unsigned char data;
        unsigned char retval;

	data = argv;
        if((data<0)||(data>255))
        {
                printf("Invalid range!\n");
                exit(1);
        }
        retval=write(dev,&data,1);
        if(retval<0) {
                printf("Write Error!\n");
                return -1;
        }
        sleep(1);
        data=0;
        retval=read(dev,&data,1);
        if(retval<0) {
                printf("Read Error!\n");
                return -1;
        }

}

int power(int x, int y)
{
	if(y ==0) return 1;
	return x*power(x,y - 1);
}



int step_motor(int power, int dir, int speed){
	int i;
	int dev;
	int str_size;
	int motor_action;
	int motor_direction;
	int motor_speed;
	unsigned char motor_state[3];


	//on off dir ac
	motor_action = power;
	motor_direction = dir;
	motor_speed = speed;


	motor_state[0]=(unsigned char)motor_action;
	motor_state[1]=(unsigned char)motor_direction;
	motor_state[2]=(unsigned char)motor_speed;
	dev = open(FPGA_STEP_MOTOR_DEVICE, O_WRONLY);
	if (dev<0) {
		printf("Device open error : %s\n",FPGA_STEP_MOTOR_DEVICE);
		exit(1);
	}
	write(dev,motor_state,3);
	close(dev);
	return 0;
}

void usage(char* dev_info)
{
	printf("<Usage> %s [Motor Action] [Motor Diretion] [Speed]\n",dev_info);
	printf("Motor Action : 0 - Stop / 1 - Start\n");
	printf("Motor Direction : 0 - Left / 1 - Right\n");
	printf("Motor Speed : 0(Fast) ~ 250(Slow)\n");
	printf("ex) %s 1 0 10\n",dev_info);
}


//text_lcd
void text_lcd_show(int dev, char* argv1, char* argv2)
{
	int str_size;
	int chk_size;
	unsigned char string[32];
	memset(string,0,sizeof(string));
	dev_text_lcd = open("/dev/fpga_text_lcd", O_WRONLY);

	str_size=strlen(argv1);
	if(str_size>0) {
        	strncat(string,argv1,str_size);
      		memset(string+str_size,' ',LINE_BUFF-str_size);
    	}
   	str_size=strlen(argv2);
    	if(str_size>0) {
        	strncat(string,argv2,str_size);
        	memset(string+LINE_BUFF+str_size,' ',LINE_BUFF-str_size);
    	}
   	write(dev,string,MAX_BUFF_LCD);

	close(dev_text_lcd);

}

int get_us(int dev_us)
{
	int retn;
	long int val=0;
	char buf[10] = {0};
	int loop = 0;
	int cnt = 0;
	long int sum = 0;
	long int sum1 = 0;

	dev_us = open("/dev/us", O_RDWR);
	if(dev_us<0){
		perror("/dev/us error");
		exit(-1);
	}else{
		printf("< us device has been detected >\n");
	}
	while(1){
		val = read(dev_us,buf,2);
		cnt++;
		sum = sum + val;

		if(cnt==10)
		{
			sum = sum/cnt;
			if(sum < 20 && sum>0){ break;}
			printf("value_avg    : %.0ld\n\n",sum);
			cnt=0;
			sum=0;
		}

		usleep(10000);
	}
	close(dev_us);
	return 0;
}


int time_set()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("Time -> %d : %d (%d)",tm.tm_hour, tm.tm_min, tm.tm_sec);
	return tm.tm_min;
}

void user_signal1(int sig)
{
        quit = 1;
}

int get_push_switch(int dev_push)
{

   	dev_push = open("/dev/fpga_push_switch", O_RDWR);
	if (dev_push<0){
		printf("Device fpga_push_switch Open Error\n");
		close(dev_push);
		return -1;
	}

    int i,val = 0;
	int buff_size;
    unsigned char push_sw_buff[MAX_BUTTON_PUSH];
	buff_size=sizeof(push_sw_buff);
	printf("Press <ctrl+c> to quit. \n");
	while(1){
		usleep(100000);
	    read(dev_push, push_sw_buff, buff_size);
	    for(i=0;i<MAX_BUTTON_PUSH;i++) {
		    //printf("[%d] ",push_sw_buff[i]);
		    //printf(". ");
		    if(push_sw_buff[i] <9)
		    {
			    if(push_sw_buff[i] == 1)
				{
					val = i;
				}
		    }
        }
		if(push_sw_buff[val]==1)
		{
			break;
		}
	}
	close(dev_push);
	return val;

}

int How_Much_Display(int paid , int how_much)
{
	int dev;
	char data[10];
	char data2[10];
	char str[32]  = "Price : ";
	char str2[32] = "Paid  : ";
	unsigned char retval;
	int i;
	int str_size;
	sprintf(data, "%d", how_much);
	sprintf(data2, "%d", paid);
	strcat(str,data);
	strcat(str2,data2);
	text_lcd_show(dev_text_lcd, str, str2);

}
