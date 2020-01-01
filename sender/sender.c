/* CSD 304 Computer Networks, Fall 2016
   Lab 4, Sender
   Team: 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define MC_PORT 5432
#define BUF_SIZE 64000


int main(int argc, char * argv[]){

  int s,s_tcp; /* socket descriptor */
  struct sockaddr_in sin,sin_t; /* socket struct */
  char buf[BUF_SIZE];
  int len;
  socklen_t sin_len;
  sin_len = sizeof(sin);
  /* Multicast specific */
  char *mcast_addr; /* multicast address */
  int tcp_ac;
  
  /* Add code to take port number from user */
  if (argc==2) {
    mcast_addr = argv[1];
  }
  else {
    fprintf(stderr, "usage: sender multicast_address\n");
    exit(1);
  }
  
//////////////////////////////////////////////////////////////////////////////////////////////////  

  	/* build address data structure for TCP*/
  bzero((char *)&sin_t, sizeof(sin_t));
  sin_t.sin_family = AF_INET;
  sin_t.sin_addr.s_addr = INADDR_ANY;
  sin_t.sin_port = htons(MC_PORT);
  
   /* Create a TCP socket */
  if ((s_tcp = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("server TCP: socket");
    exit(1);
  }
  else
  {	
  		printf("Socket created\n\n");
  }
  // binding server addr structure to s_tcp

     
  if ((bind(s_tcp, (struct sockaddr *) &sin_t, sizeof(sin_t))) < 0) {
    perror("receiver: bind()");
    close(s_tcp);
    exit(1);
  }
  else
  {	
  		printf("Binded\n\n");
  }
  
  if((listen(s_tcp, 512000))<0)
  {	
  		printf("Error in listening\n");
  }
  else
	printf("Listened\n\n");
  
  
  //if((tcp_ac = accept(s_tcp, (struct sockaddr*)&sin_t, &length))<0)	 //Accept
  if((tcp_ac = accept(s_tcp, (struct sockaddr*)&sin_t, &sin_len))<0)	 //Accept
  {	
  		printf("Error in accepting\n");
  }    
  else
	printf("Accepted\n\n");
  
    
    int num;

	//usleep(5000000);
	//while(num==0){
    	int n = recv(tcp_ac, &num, sizeof(num)+1, 0);
//}	
    //read(s_tcp, &num, sizeof(num));
    printf("Station number is: %d\n\n",num);
  
//////////////////////////////////////////////////////////////////////////////////////////////////  

  if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("server UDP: socket");
    exit(1);
  }
  
  // build address data structure 
  memset((char *)&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(mcast_addr);
  sin.sin_port = htons(MC_PORT);

	int length = sizeof(mcast_addr);
  //printf("\nWrite messages below to multicast!\n\n");


  memset(buf, 0, sizeof(buf));
  
  /*while (fgets (buf, BUF_SIZE, stdin)) {
    if ((len = sendto(s, buf, sizeof(buf), 0,
		      (struct sockaddr *)&sin, 
		      sizeof(sin))) == -1) {
      perror("sender: sendto");
      exit(1);
    }
    
    memset(buf, 0, sizeof(buf));
  
  }*/
  
  /*len = recvfrom(s, buf, sizeof(buf), 0,(struct sockaddr *)&sin, &sin_len);
        
        buf[len-2]='\0';*/
        FILE *fp=NULL;	
        fp=fopen("vid1.mp4","rb");
      	
      		//printf("entered!");        
		if(fp==NULL)
	    	{
		       sendto(s, "File Not Found\n", strlen("File Not Found\n")+1, 0,(struct sockaddr*)&sin, sin_len);
	    	}
		else
	    	{
		int tot_frame,i;
		fseek(fp, 0, SEEK_END);
		long fsize = ftell(fp);
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
		         
		if(sendto(s,&(tot_frame),sizeof(tot_frame),0,(struct sockaddr*)&sin, sin_len)<0)
		    printf("Error in sending frame no:\n");
			    
		if(tot_frame==0 || tot_frame==1)
		{
		      char *string = malloc(fsize + 1);
			      fread(string,1,fsize+1,fp);		          
			      fseek(fp, 0, SEEK_SET);
			      int x=sendto(s,string,fsize+1,0,(struct sockaddr*)&sin, sin_len); 
		      printf("%d\n",x);
		}
		else
		{ 
		      for(i=1;i<=tot_frame;i++)
		      {
			              char *string = malloc(BUF_SIZE);
			              len=fread(string,1,BUF_SIZE,fp);	           
			              fseek(fp, 0, SEEK_CUR);
			              int x=sendto(s,string,len,0,(struct sockaddr*)&sin,sin_len); 
			              printf("sent frame %d\n",i);
			                    //usleep(2*100000);
		              	  usleep(2*100000);
		      }
		      
		}
		
	       fclose(fp); 
        } 
      		
		
	      
        	fp=fopen("va1.mp4","rb");
        	
        	printf("\tCurrent Stream: va1.mp4\n\n");
        	printf("\tNext Stream: xyz.mp4\n\n");
        	
		//printf("entered!\n");        
		if(fp==NULL)
	    	{
		       //sendto(s, "File Not Found\n", strlen("File Not Found\n")+1, 0,(struct sockaddr*)&sin, sin_len);
		       sendto(s, "File Not Found\n", strlen("File Not Found\n")+1, 0,(struct sockaddr*)&sin, sin_len);
	    	}
		else
	    	{
			int tot_frame,i;
			fseek(fp, 0, SEEK_END);
			long fsize = ftell(fp);
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
				 
			if(sendto(s,&(tot_frame),sizeof(tot_frame),0,(struct sockaddr*)&sin, sin_len)<0)
			    printf("Error in sending frame no:\n");
				    
			if(tot_frame==0 || tot_frame==1)
			{
			      char *string = malloc(fsize + 1);
				      fread(string,1,fsize+1,fp);		          
				      fseek(fp, 0, SEEK_SET);
				      int x=sendto(s,string,fsize+1,0,(struct sockaddr*)&sin, sin_len); 
			      printf("%d\n",x);
			}
			else
			{ 
			      for(i=1;i<=tot_frame;i++)
			      {
					      char *string = malloc(BUF_SIZE);
					      len=fread(string,1,BUF_SIZE,fp);	           
					      fseek(fp, 0, SEEK_CUR);
					      int x=sendto(s,string,len,0,(struct sockaddr*)&sin,sin_len); 
					      printf("sent frame %d\n",i);
				      	usleep(2*100000);
			      }
			      
			}
			
			fclose(fp); 
        	} 
		 
	       
        	fp=fopen("cn.mp4","rb");
        	
        	//printf("entered!\n");        
		if(fp==NULL)
	    	{
		       sendto(s, "File Not Found\n", strlen("File Not Found\n")+1, 0,(struct sockaddr*)&sin, sin_len);
	    	}
		else
	    	{
			int tot_frame,i;
			fseek(fp, 0, SEEK_END);
			long fsize = ftell(fp);
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
				 
			if(sendto(s,&(tot_frame),sizeof(tot_frame),0,(struct sockaddr*)&sin, sin_len)<0)
			    printf("Error in sending frame no:\n");
				    
			if(tot_frame==0 || tot_frame==1)
			{
			      char *string = malloc(fsize + 1);
				      fread(string,1,fsize+1,fp);		          
				      fseek(fp, 0, SEEK_SET);
				      int x=sendto(s,string,fsize+1,0,(struct sockaddr*)&sin, sin_len); 
			      printf("%d\n",x);
			}
			else
			{ 
			      for(i=1;i<=tot_frame;i++)
			      {
					      char *string = malloc(BUF_SIZE);
					      len=fread(string,1,BUF_SIZE,fp);	           
					      fseek(fp, 0, SEEK_CUR);
					      int x=sendto(s,string,len,0,(struct sockaddr*)&sin,sin_len); 
					      printf("sent frame %d\n",i);
				      	usleep(10000);
			      }
			      
			}
			
			fclose(fp); 
        	} 
        	
	      close(s);  
  return 0; 
	}


