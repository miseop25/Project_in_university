#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "220.149.128.100"
#define SERV_PORT 4106
#define BACKLOG 10

#define INIT_MSG "=========================\n==========HELLO!=========\n======Please Log In======\nINPUT YOUR ID :"
#define LOGIN_PW_MSG "Input yout PW :"
#define USER1_ID "user1"
#define USER1_PW "asd"
#define USER2_ID "user2"
#define USER2_PW "asd"
#define Success "Log in Success!!"
#define Fail "Log in Fail!!"

int while_brake =0;


int main(void){

    int sockfd, new_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    unsigned int sin_size;

    int rsv_byte;
    char list_buf[512];

    char id[40];
    char pw[40];
	  char mode_sel[2];
    char msg[512];

    int val = 1;
	  int users_num;

	FILE *listFile, *listComp;
	char listName[40]= "list.txt";
	size_t n_size;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Server-soket() error lol!");
        exit(1);
    }
    else printf("Server-socket() sokfd is OK...\n");

    my_addr.sin_family = AF_INET;

    my_addr.sin_port = htons(SERV_PORT);

    my_addr.sin_addr.s_addr = INADDR_ANY;

    memset(&(my_addr.sin_zero), 0,8);

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val))<0){
			perror("setsockopt");
			close(sockfd);
			return -1;
	}

    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Server-bind() error lol...!");
        exit(1);

    }
    else printf("Server-bind() is Ok....\n");

    if( listen(sockfd, BACKLOG) ==-1)
    {
        perror("listen() error lol");
        exit(1);
    }else printf("listen() is OK...\n");

    sin_size = sizeof(struct sockaddr_in);

	 pid_t pid;

while(while_brake ==0){
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
  	pid = fork();

	if(pid == 0){
    send(new_fd, INIT_MSG,strlen(INIT_MSG) +1,0);
	//send 함수의 두번쟤 인자는 송신할 데이터가 있는 메모리주소
	//세번쨰 인자로 송신할 바이트 수 , 반환값으로 실제 송신한
	//바이트 수를 반환한다.
	recv(new_fd,id,sizeof(id),0);

	if(strcmp(id,USER1_ID) ==0){
	printf("%s is connected\n",id);
	users_num = 1;
	}else if(strcmp(id, USER2_ID) ==0){ printf("%s is connected\n",id); users_num = 2;}
	else {printf("NO ID in here\n"); users_num =-1;}


    send(new_fd, LOGIN_PW_MSG,strlen(LOGIN_PW_MSG) +1,0);
	sleep(1);
	recv(new_fd, pw, sizeof(pw), 0);

	printf("====================\nUSER Information\n ID : %s , PW : %s\n",id,pw);

	switch(users_num){
		case 1: {
		if(strcmp(pw,USER1_PW) ==0) {
			printf("===================\n Log -in success!! [%s] *^^*\n",id);
			send(new_fd, Success ,strlen(Success) +1,0);
		}else{
			printf("==================\n Log in fail, Incorrect PW\n");
			send(new_fd, "Log in fail, Incorrect PW" ,strlen("Log in fail, Incorrect PW") +1,0);
			users_num = -1;
		}
		} break ;
		case 2:{
	    if(strcmp(pw,USER2_PW) ==0) {
	       printf("===================\n Log -in success!! [%s] *^^*\n",id);
	       send(new_fd, Success ,strlen(Success) +1,0);
	       }else{
	       printf("==================\n Log in fail, Incorrect PW\n");
	       send(new_fd,"Log in fail, Incorrect PW" ,strlen("Log in fail, Incorrect PW") +1,0);
		   users_num = -1;
		   }
	    }break;
		case -1:{
	       printf("==================\n Log in fail, Incorrect ID\n");
	       send(new_fd,"Log in fail, Incorrect ID" ,strlen("Log in fail, Incorrect ID") +1,0);  }break;
		}

if(users_num != -1){
	int mode_int;
  int list_non = 0;
	int count;
	char cnt_ch[50]={0.};
	char client_IP[50];
	char client_Port[10];

  short num=1;
  char num_ch[512];
  char* inName;
	recv(new_fd,client_IP, sizeof(client_IP), 0);
	send(new_fd,"recv_OK" ,strlen("recv_OK") +1,0);

	recv(new_fd, client_Port, sizeof(client_Port), 0);
	send(new_fd,"recv_OK" ,strlen("recv_OK") +1,0);
	recv(new_fd, client_Port, sizeof(client_Port), 0);

	printf("IP : %s Port : %s \n",client_IP, client_Port);

  while(1){
    	//recv(new_fd, mode_sel, sizeof(mode_sel), 0);
    	send(new_fd,"recv_OK" ,strlen("recv_OK") +1,0);
    	recv(new_fd, mode_sel, sizeof(mode_sel), 0);
      mode_int = atoi(mode_sel);

    	switch(mode_int){
    		case 1:{
               printf("\n====== %s are uploading list ======\n",id );
    				   listFile = fopen(listName,"a+");
    				   send(new_fd,"recv_OK" ,strlen("recv_OK") +1,0);
    			 	   recv(new_fd, cnt_ch, sizeof(cnt_ch),0);
    				   count = atoi(cnt_ch);

    				   while(count > 0){
      			 	   recv(new_fd, msg, sizeof(msg),0);
      				   send(new_fd,"recv_OK" ,strlen("recv_OK") +1,0);

                 listComp = fopen(listName,"r");
      				   while(1){
                     fgets(list_buf, sizeof(list_buf), listComp);
                     inName = strtok(list_buf, " ");
                     if(feof(listComp)) break;
                     if(strcmp(inName, msg)==0) {
                       list_non = 1;
                       printf("%s is alraday in list\n",msg );
                     }
                  }
                  fclose(listComp);

                 if(list_non ==0){
          				   strcat(msg," ");
          				   strcat(msg,id);
          				   strcat(msg," ");
          				   strcat(msg,client_IP);
          				   strcat(msg," ");
          				   strcat(msg,client_Port);
          				   strcat(msg,"\n");
          				   fputs(msg,listFile);
          				   printf("%s",msg);
                   }
                 list_non = 0;
      				   count--;
    				   }
               count=0;
    				   fclose(listFile);
    		}break;//case1;
    		case 2:{
               printf("\n====== %s are request the list ======\n",id );
    				   listFile = fopen(listName,"r");
               count = 0;
    				   while(!feof(listFile)){
                 fgets(list_buf, sizeof(list_buf), listFile);
                 count++;
                }fclose(listFile);

                char cnt_ch[50]= {0,};
         	 			sprintf(cnt_ch,"%d",count);
         				send(new_fd,cnt_ch, sizeof(cnt_ch), 0);
         				recv(new_fd, msg, sizeof(msg), 0);

                num=1;

                listFile = fopen(listName,"r");
                while(count!=num){
                   fgets(list_buf, sizeof(list_buf), listFile);
                   sprintf(num_ch,"%d",num);
                   strcat(num_ch," ");
                   strcat(num_ch,list_buf);

                   send(new_fd,num_ch ,sizeof(num_ch) ,0);
                   recv(new_fd, msg, sizeof(msg),0);
                   num++;
                 }
                 count=0;
                 num=1;
                 fclose(listFile);
         }break;//case2
         case 3:{
               printf("\n====== %s are want's to file download ======\n",id );
     				   listFile = fopen(listName,"r");
               count = 0;
     				   while(!feof(listFile)){
                  fgets(list_buf, sizeof(list_buf), listFile);
                  count++;
                 }fclose(listFile);

                  char fileNum[10]= {0,};
                  int file_int;
                  send(new_fd, "recv_OK", sizeof("recv_OK") +1, 0);
                  recv(new_fd, fileNum, sizeof(fileNum), 0);

                  file_int = atoi(fileNum);
                  num=1;

                  listFile = fopen(listName,"r");
                  while(count!=num){
                      fgets(list_buf, sizeof(list_buf), listFile);
                      sprintf(num_ch,"%d",num);
                      strcat(num_ch," ");
                      strcat(num_ch,list_buf);
                      if(file_int == num){
                        send(new_fd,num_ch ,sizeof(num_ch) ,0);
                        recv(new_fd, msg, sizeof(msg),0);
           					    printf("%s Downloading %s",id, list_buf);
                      }
                      num++;
                  }
                  fclose(listFile);
          }break;//case3

         default: break;

    	}//switch
    }//while end
  }//right user(end if)
  close(new_fd);
	}
	else if(pid >0){
	  printf("accept is OK....\n");
	}

}//for while end
		close(sockfd);
}
