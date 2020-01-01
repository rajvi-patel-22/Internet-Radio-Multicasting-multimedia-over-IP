//server tcp  with gtk

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 512000

//Structure of site info
struct site_info
{
	uint8_t site_name_size;
	char site_name[ 20 ];
	uint8_t site_desc_size;
	char site_desc[ 100 ];
	uint8_t station_count;
};

//Structure of station info
struct station_info 
{
	uint8_t station_number;	
	char station_name[50];
	char multicast_address[32];
	uint16_t data_port;	
	uint16_t info_port;
	uint32_t bit_rate;
};

int main()
{
  struct station_info stat1,stat2,stat3;
  struct site_info site1,site2,site3;  
  struct sockaddr_in sin;
  
  char buf[MAX_LINE];
  int len;
  int s, new_s;
  char str[INET_ADDRSTRLEN];
  int num;
  
  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(SERVER_PORT);
  
  
  /* setup passive open */
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  inet_ntop(AF_INET, &(sin.sin_addr), str, INET_ADDRSTRLEN);
  printf("Server is using address %s and port %d.\n", str, SERVER_PORT);

  if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
    perror("simplex-talk: bind");
    exit(1);
  }
  else
    printf("Server bind done.\n");

  listen(s, MAX_PENDING);	//Server listening
  
  while(1)
  {
		if((new_s = accept(s, (struct sockaddr*)&sin, &len))<0)	 //Accept
		{	
	  		 printf("Error in accepting\n");
		}    
		else
			 printf("Accepted\n\n");

		 recv(new_s, buf, sizeof(buf), 0);	//Receive "Start"

		 printf("%s\n",buf);
		
		 /*Declaration of site info for station 1 */
		 bzero(&site1,sizeof(site1));
		 strcpy(site1.site_name,"www.friends.com");
		 strcpy(site1.site_desc,"iconic series: F.R.I.E.N.D.S.  ");
		 
		 /*Declaration of station info for station 1 */
		 bzero(&stat1,sizeof(stat1));
		 stat1.station_number = 1;
		 strcpy(stat1.multicast_address,"239.192.4.1");
		 stat1.data_port = 5433; 
		 stat1.info_port = 5432; 
  		 stat1.bit_rate = 1087;
  		 strcpy(stat1.station_name,"F.R.I.E.N.D.S");
  		 
  		 /*Declaration of site info for station 2 */
  		 bzero(&site2,sizeof(site2));
  		 strcpy(site2.site_name,"www.himym.com");
		 strcpy(site2.site_desc,"How I met your mother ");
		  
		 /*Declaration of station info for station 2 */
		 bzero(&stat2,sizeof(stat2));
		 stat2.station_number = 2;
		 strcpy(stat2.multicast_address,"239.192.4.2");
       stat2.data_port = 5433;	//for udp
       stat2.info_port = 5432;	//for tcp
       stat2.bit_rate = 891;
		 strcpy(stat2.station_name,"H.I.M.Y.M");
		 
		 /*Sending structure of site info */
		 send(new_s, &(site1), sizeof(site1)+1, 0);
		 send(new_s, &(site2), sizeof(site2)+1, 0);
		 
		 /*Sending structure of station info*/
		 send(new_s, &(stat1), sizeof(stat1)+1, 0);
		 send(new_s, &(stat2), sizeof(stat2)+1, 0);
		 
	    close(new_s);		//Close socket
    }
 return 0;    
}
