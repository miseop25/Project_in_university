#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define SERV_IP "220.149.128.100"
#define SERV_PORT 4106
#define Client_PORT "4101"
#define Client_PORT_INT 4101
#define BACKLOG 10
#define Client_IP "220.149.128.101"

int while_brake =0;



 int main(void){

     int sockfd;
     struct sockaddr_in dest_addr;

     int sockfd2, new_fd;
     struct sockaddr_in my_addr;
     struct sockaddr_in their_addr;
     unsigned int sin_size;
     int val = 1;

     int rsv_byte;
     char buf[512];
     char id[20];
     char pw[20];
     char mode_sel[2];

	   DIR *dir_info;
	   struct dirent *dir_entry;

     pid_t pid;


///////////////////////////////////////////client

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd == -1){
         perror("Server-soket() error lol!");
         exit(1);
  }
  else printf("Server-socket() sokfd is OK...\n");

	 dest_addr.sin_family = AF_INET;
	 dest_addr.sin_port = htons(SERV_PORT);
	 dest_addr.sin_addr.s_addr = inet_addr(SERV_IP);

	 memset(&(dest_addr.sin_zero), 0 , 8);

	 if(connect(sockfd, (struct sockaddr *)&dest_addr,sizeof(struct sockaddr)) ==-1)
	 {
		 perror("Client - connect() error lol");
		 exit(1);
	 }
	 else printf("Client - connect() is Ok \n\n");
///////////////////////////////////////////////////////

	 rsv_byte = recv(sockfd, buf, sizeof(buf), 0);
	 printf("%s", buf);


	 scanf("%s",id);
	 send(sockfd, id, sizeof(id) +1,0);

	 recv(sockfd, buf, sizeof(buf), 0);
	 printf("%s", buf);

	 scanf("%s",pw);
	 send(sockfd, pw, sizeof(pw) +1, 0);

	 recv(sockfd, buf, sizeof(buf), 0);
	 printf("%s\n", buf);

 if((strcmp(buf,"Log in fail, Incorrect ID")&& strcmp(buf,"Log in fail, Incorrect PW")) != 0){

   /////////////////////////////////////////////client as server
        sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd2 == -1){
            perror("Server-soket2() error lol!");
            exit(1);
        }
        else printf("Server-socket2() sokfd is OK...\n");

        my_addr.sin_family = AF_INET;

        my_addr.sin_port = htons(Client_PORT_INT);

        my_addr.sin_addr.s_addr = INADDR_ANY;

        memset(&(my_addr.sin_zero), 0,8);

    	if(setsockopt(sockfd2, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val))<0){
    			perror("setsockopt");
    			close(sockfd2);
    			return -1;
    	}

        if(bind(sockfd2, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
        {
            perror("Server-bind() error lol...!");
            exit(1);

        }
        else printf("Server-bind() is Ok....\n");

        if( listen(sockfd2, BACKLOG) ==-1)
        {
            perror("listen() error lol");
            exit(1);
        }else printf("listen() is OK...\n");

        sin_size = sizeof(struct sockaddr_in);
///////////////////////////////////////////////////

  pid = fork();

  if(pid ==0){

	 char client_IP[50] = Client_IP;
	 char client_Port[10] = Client_PORT;
   int mode_int;
   int count = 0;
   char cnt_ch[50]= {0,};
   char msg[512];

	 send(sockfd, client_IP, sizeof(client_IP) +1, 0);
	 recv(sockfd, buf, sizeof(buf), 0);

	 send(sockfd, client_Port, sizeof(client_Port) +1, 0);
	 recv(sockfd, buf, sizeof(buf), 0);

   while(while_brake ==0){
  	 printf("\n==========Select mode==========\n    1 : list upload\n    2 : list recive\n    3 : download file\n");
     printf("select:");

  	 scanf("%s", mode_sel);
  	 send(sockfd, mode_sel, sizeof(mode_sel), 0);
     recv(sockfd, buf, sizeof(buf), 0);
  	 mode_int = atoi(mode_sel);
  	 switch(mode_int){
    		case 1:{
    				dir_info = opendir("./my_file");
    				if(NULL != dir_info){
    					while(dir_entry = readdir(dir_info)){count++;}
    					count = count - 2;
    				}
    				sprintf(cnt_ch,"%d",count);
    				send(sockfd,cnt_ch, sizeof(cnt_ch), 0);
    				recv(sockfd, buf, sizeof(buf), 0);
    				closedir(dir_info);
    				count = 0;
    				dir_info = opendir("./my_file");
    				if(NULL != dir_info){
    					while(dir_entry = readdir(dir_info))
    					{
    						if((strcmp(dir_entry->d_name,"..")&& strcmp(dir_entry->d_name,".")!=0)){
      						send(sockfd, dir_entry->d_name, sizeof(dir_entry->d_name) +1, 0);
      					  recv(sockfd, buf, sizeof(buf), 0);
      						printf("%s // Success \n",dir_entry->d_name);
    						}
    					}
    				}closedir(dir_info);
    		}break;

    		case 2:{
                recv(sockfd, cnt_ch, sizeof(cnt_ch),0);
                send(sockfd,"recv_OK" ,strlen("recv_OK") +1,0);
                count = atoi(cnt_ch);
                printf("===============File List===============\n");
                while(count>1){
                  recv(sockfd, buf, sizeof(buf), 0);
                  send(sockfd, "recv_OK", sizeof("recv_OK") +1, 0);
                  printf("%s",buf);
                  count--;
                }count = 0;
                printf("=======================================\n");

    		}break;

        case 3:{
                char fileNum[10] = {0,};
                int file_int;

                printf("Select file : ");
                scanf("%s", fileNum);
                file_int = atoi(fileNum);

                send(sockfd,fileNum, sizeof(fileNum), 0);
                recv(sockfd, buf, sizeof(buf), 0);

                send(sockfd, "recv_OK", sizeof("recv_OK") +1, 0);
                recv(sockfd, buf, sizeof(buf), 0);


                char d_filename[40] = {0,};
                char d_port[40] = {0,};
                char d_IP[40] = {0,};

                char* ptr = strtok(buf, " ");
                while (ptr != NULL)
                {
                    ptr = strtok(NULL, " ");
                    if(count == 0) strcpy(d_filename,ptr);
                    if(count == 2) strcpy(d_IP,ptr);
                    if(count == 3) strcpy(d_port,ptr);
                    count++;
                }
                int cl_port;
                cl_port = atoi(d_port);
                printf("file name : %s, IP : %s Port : %d\n",d_filename,d_IP,cl_port);
                count = 0;
//////////////////////////////////////////////////////////////////////////
                int sockfd3;
                struct sockaddr_in dest_addr2;

                sockfd3 = socket(AF_INET, SOCK_STREAM, 0);
                if(sockfd3 == -1){
                       perror("Server-soket() error lol!");
                       exit(1);
                }
                else printf("Server-socket3() sokfd is OK...\n");

              	 dest_addr2.sin_family = AF_INET;
              	 dest_addr2.sin_port = htons(cl_port);
              	 dest_addr2.sin_addr.s_addr = inet_addr(d_IP);

              	 memset(&(dest_addr2.sin_zero), 0 , 8);

              	 if(connect(sockfd3, (struct sockaddr *)&dest_addr2,sizeof(struct sockaddr)) ==-1)
              	 {
              		 perror("Client3 - connect() error lol");
              		 exit(1);
              	 }
              	 else printf("Client3 - connect() is Ok \n\n");

                 FILE *downFile;
                 size_t n_size;

                 char root[40] = {"./Download/"};
                 int msg_count=0;
                 strcat(root,d_filename);

                 send(sockfd3,d_filename ,sizeof(d_filename) +1,0);
                 recv(sockfd3, buf, sizeof(buf),0);
                 printf("Downloading %s\n", d_filename);

                 send(sockfd3,"recv_OK" ,strlen("recv_OK") +1,0);
                 recv(sockfd3, buf, sizeof(buf),0);
                 msg_count = atoi(buf);

                 downFile = fopen(root,"a");
      				   while(msg_count>0){
                   send(sockfd3,"recv_OK" ,strlen("recv_OK") +1,0);
        			 	   recv(sockfd3, msg, sizeof(msg)+1,0);
        				   fputs(msg,downFile);
                   msg_count--;
      				   }
                 printf("Download Success\n");
      				   fclose(downFile);


        }break;

        default: break;
  	 }//end switch
   }//end while

 }//end right user if
}//child process
if(pid >0){
  while(1){
      new_fd = accept(sockfd2, (struct sockaddr *)&their_addr, &sin_size);
      FILE *sendFile;
      size_t n_size;
      char root[40] = {"./my_file/"};
      char file_msg[512];
      int msg_count=0;
      char msgc_ch[20];

      recv(new_fd, buf, sizeof(buf),0);
      send(new_fd,"recv_OK" ,strlen("recv_OK") +1,0);
      strcat(root,buf);

      sendFile = fopen(root,"r");
        while(fgets(file_msg,sizeof(file_msg),sendFile) !=NULL) msg_count++;
      fclose(sendFile);

        sprintf(msgc_ch,"%d",msg_count);
        recv(new_fd,buf,sizeof(buf),0);
        send(new_fd,msgc_ch,sizeof(msgc_ch),0);

      sendFile = fopen(root,"r");
          while(fgets(file_msg,sizeof(file_msg),sendFile) !=NULL)
            {
              recv(new_fd,buf,sizeof(buf),0);
              send(new_fd,file_msg,sizeof(file_msg) +1,0);
            }
      fclose(sendFile);
      close(new_fd);
    }
  close(sockfd2);
}


	 return 0;
 }
