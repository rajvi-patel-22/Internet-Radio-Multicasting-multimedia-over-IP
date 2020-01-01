//Client_with gtk

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define MC_PORT 5432
#define BUF_SIZE 64000

struct site_info
{
	uint8_t site_name_size;
	char site_name[ 20 ];
	uint8_t site_desc_size;
	char site_desc[ 100 ];
	uint8_t station_count;
};

struct station_info
{
uint8_t station_number;
char station_name[50];
char multicast_address[32];
uint16_t data_port;

uint16_t info_port;
uint32_t bit_rate;
};

int updateLabel(GtkLabel *lab, gchar *display)
{
	gtk_label_set_text (GTK_LABEL(lab), display); //set label to "display"
	return 0;
}

/* function for button 1 "station 1" */
int func1(GtkWidget *widget,gpointer   data, GtkLabel *lab)
{
	gchar *display;
	display="Connected to Station 1!";
	updateLabel(GTK_LABEL(lab), display);
	while(gtk_events_pending())
	gtk_main_iteration();
	system("gcc `pkg-config --cflags gtk+-3.0` -o receiver receiver.c  `pkg-config --libs gtk+-3.0` ");
	char string[200] = "sudo ./receiver ";
	strcat(string,"239.192.4.1");
	system(string);
	return 0;
}  

/* function for button 2 "station 2" */
int func2(GtkWidget *widget,gpointer   data, GtkLabel *lab)
{
	gchar *display;
	display="Connected to Station 2!";
	updateLabel(GTK_LABEL(lab), display);
	while(gtk_events_pending())
	gtk_main_iteration();
	system("gcc `pkg-config --cflags gtk+-3.0` -o receiver receiver.c  `pkg-config --libs gtk+-3.0` ");
	char string1[200] = "sudo ./receiver ";
	strcat(string1,"239.192.4.2");
	system(string1);
	return 0;
}

int func3(GtkWidget *widget,gpointer   data, GtkLabel *lab)
{
	exit(0);
	return 0;
}


/* function for button 3*/
int main(int argc, char * argv[])
{
  char string[200]="./receiver ";
  char string1[200]="./temp ";
  FILE *fp;
  int s,s_tcp; 									/* socket descriptor */
  struct hostent *hp;
  struct sockaddr_in sin,sin_t,cliaddr;   /* socket struct */
  char *if_name; 									/* name of interface */
  struct ifreq ifr; 								/* interface struct */
    char *host;
  struct station_info stat1,stat2,stat3;
  struct site_info site1,site2,site3;
  //struct site_info site;
 

 
  char buf[BUF_SIZE],buf1[BUF_SIZE];
  int len;
  char str[200];
  /* Multicast specific */
  char *mcast_addr; 					 /* multicast address */
  struct ip_mreq mcast_req;  		 /* multicast join struct */
  struct sockaddr_in mcast_saddr; /* multicast sender*/
  socklen_t mcast_saddr_len;
 
 
  if (argc==2) {
    host = argv[1];
  }
  else {
    fprintf(stderr, "usage: simplex-talk host\n");
    exit(1);
  }
  printf("\n Host: %s\n\n",host);
  /* translate host name into peer's IP address */
  hp = gethostbyname(host);
  if (!hp) {
    fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
    exit(1);
  }
  else
    printf("Client's remote host: %s\n", argv[1]);
 
 

  /* build address data structure for TCP*/
  memset((char *)&sin_t, 0, sizeof(sin_t));
  sin_t.sin_family = AF_INET;
  bcopy(hp->h_addr, (char *)&sin_t.sin_addr,hp->h_length);
  //sin_t.sin_addr.s_addr = INADDR_ANY;
  sin_t.sin_port = htons(MC_PORT);

  // Create a TCP socket
  if ((s_tcp = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("server TCP: socket");
    exit(1);
  }
  else
    printf("TCP side socket created.\n");
   
  if (connect(s_tcp, (struct sockaddr *)&sin_t, sizeof(sin_t)) < 0)
    {
     // perror("simplex-talk: connect");
     printf("\ntcp not connected\n");
      close(s_tcp);
      exit(1);
    }
  else
    printf("Client connected in tcp.\n");
   

  int num;

 if((send(s_tcp, "Start\n", strlen("Start\n")+1, 0)) <0)
  printf("\nclient not ready to receive\n");
 
 else
  printf("\nstart send successfully\n");
 
  //Reset 
  bzero(&stat1,sizeof(stat1));
  bzero(&stat2,sizeof(stat2));
  bzero(&site1,sizeof(site1));
  bzero(&site2,sizeof(site2));
 
 
  //Receive site info for station 1
  recv(s_tcp, &(site1), sizeof(site1)+1, 0); 	
   
  printf("\n-------------------------------------------------------\n");
  printf("For station 1 site info\n");
  printf("\nSite name: %s",site1.site_name);
  printf("\nSite description: %s\n",site1.site_desc);
 
  //Receive site info for station 2
  recv(s_tcp, &(site2), sizeof(site2)+1, 0);
  
  printf("\n-------------------------------------------------------\n");
  printf("For station 2 site info\n");
  printf("\nSite name: %s",site2.site_name);
  printf("\nSite description: %s\n",site2.site_desc);
 
 
  //Receive station info for station 1
  recv(s_tcp, &(stat1), sizeof(stat1)+1, 0);
  
  printf("\n\n-------------------------------------------------------\n");
  printf("info port        : %d\n", stat1.info_port);
  printf("Station Number   : %d\n",stat1.station_number);
  printf("Station name     : %s\n",stat1.station_name);
  printf("Multicast Address: %s\n",stat1.multicast_address);
  printf("Data port        : %d\n", stat1.data_port);
  printf("Bit rate         : %d kb/s\n",stat1.bit_rate);

  //Receive station info for station 2
  recv(s_tcp, &(stat2), sizeof(stat2)+1, 0);
 
  printf("\n\n-------------------------------------------------------\n");
  printf("info port        : %d\n", stat2.info_port);
  printf("Station Number   : %d\n",stat2.station_number);
  printf("Station name     : %s\n",stat2.station_name);
  printf("Multicast Address: %s\n",stat2.multicast_address);
  printf("Data port        : %d\n", stat2.data_port);
  printf("Bit rate         : %d kb/s",stat2.bit_rate);
  printf("\n-------------------------------------------------------\n");
 
 
  //GUI for station list
  gtk_init (&argc, &argv);
  GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *label;
  GtkWidget *lab;
  GdkColor color;

  gtk_window_set_title (GTK_WINDOW (window), "Welcome to Television!");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gdk_color_parse ("light yellow", &color);		//Set color of GUI window
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  
  
  lab = gtk_label_new ("Hello!!");
  grid = gtk_grid_new ();
  
  gtk_container_add (GTK_CONTAINER (window), grid);

 
  button = gtk_button_new_with_label ("F.R.I.E.N.D.S");
  g_signal_connect (button, "clicked", G_CALLBACK (func1), lab);	//Call func1 for station 1

  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("H.I.M.Y.M");
  g_signal_connect (button, "clicked", G_CALLBACK (func2), lab);	//Call func2 for station 2
 
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label ("EXIT");
  g_signal_connect (button, "clicked", G_CALLBACK (func3), lab);	//Call func2 for exit
 
  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 2, 1);


  gtk_grid_attach (GTK_GRID(grid), lab, 0, 4, 4, 1);
     
  gtk_widget_show_all (window);
  gtk_main ();

  close(s_tcp);		//close socket
  return 0;
}
	
