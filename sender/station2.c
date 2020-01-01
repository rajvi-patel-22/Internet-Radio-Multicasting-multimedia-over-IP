//sender_udp2 with gtk

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MC_PORT 5433
#define BUF_SIZE 64000

//structure of song info
struct song_info
{
	  char song_name[ 50 ];
	  uint16_t remaining_time_in_sec;
	  char next_song_name[ 50 ];
};

int main(int argc, char * argv[])
{  
	  int s; // socket descriptor 
	  struct sockaddr_in sin; // socket struct 
	  char buf[BUF_SIZE];
	  int len;
	  socklen_t sin_len;
	  sin_len = sizeof(sin);
	  
	  // Multicast specific 
	  char *mcast_addr; // multicast address 
	  char * video[5]; 
	  
	  //Array of video names
	  video[0] = "vid5.mp4";
	  video[1] = "vid6.mp4";
	  video[2] = "vid7.mp4";
	  video[3] = "vid8.mp4";
	  
	  
	  // Add code to take port number from user 
	  if (argc==2) 
	  {
		 	mcast_addr = argv[1];
	  }
	  else 
	  {
			 fprintf(stderr, "usage: sender multicast_address\n");
			 exit(1);
	  }
	  
	  if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) 
	  {
			 perror("server UDP: socket");
			 exit(1);
  	  }
  
	  // build address data structure 
	  memset((char *)&sin, 0, sizeof(sin));
	  sin.sin_family = AF_INET;
	  sin.sin_addr.s_addr = inet_addr(mcast_addr);
	  sin.sin_port = htons(MC_PORT);

	  printf("Connected in second station\n\n ");
	  memset(buf, 0, sizeof(buf));
	  
	  FILE *fp=NULL;	
	  int i;
	  while(1)
	  { 
	      for(i=0; i<4; i++)	//Sending videos one by one
	      {
	      	
         	fp=fopen(video[i],"rb");
       	       
	      	if(fp==NULL)		//Check if file exist
	      	{
	         	 printf("\nFile not found\n");
	         }
	      	else
         	{
					 int tot_frame,i;
					 fseek(fp, 0, SEEK_END);
					 long fsize = ftell(fp);		//Calculate file size
					 long p=(fsize % 64000);
					 if ((fsize % BUF_SIZE) != 0)
					 {
						 tot_frame = (fsize / BUF_SIZE) + 1;
					 }		
					 else
						 tot_frame = (fsize / BUF_SIZE);
				
					 printf("last packets are :%ld\n\n", p); 
					 printf("Total number of packets are :%d\n\n", tot_frame);
								  
					 fseek(fp, 0, SEEK_SET);
							  
					 if(tot_frame==0 || tot_frame==1)
					 {
							 char *string = malloc(fsize + 1);
							 fread(string,1,fsize+1,fp);		//Read data into string          
							 fseek(fp, 0, SEEK_SET);
							 int x=sendto(s,string,fsize+1,0,(struct sockaddr*)&sin, sin_len); //Sending data to the receiver
							 printf("%d\n",x);
					 }
					 else
					 { 
						    
							 for(i=1;i<=tot_frame;i++)
							 {
								         char *string = malloc(BUF_SIZE);
								         len=fread(string,1,BUF_SIZE,fp);	           
								         fseek(fp, 0, SEEK_CUR);
								         int x=sendto(s,string,len,0,(struct sockaddr*)&sin,sin_len); //Sending data frame by frame
								         printf("sent frame %d\n",i);
							         	usleep(300000);
							 }
						
					 }
					 fclose(fp); //close file pointer
		       }
	      }
	  }
	  return 0;
}

