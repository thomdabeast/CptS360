#include "client_funcs.h"

// end of stream 
const char EOS[] = "EOS";

int clientInit(char *argv[])
{
  printf("======= clinet init ==========\n");

  printf("1 : get server info\n");
  hp = gethostbyname(argv[1]);
  if (hp==0){
     printf("unknown host %s\n", argv[1]);
     exit(1);
  }

  SERVER_IP   = *(long *)hp->h_addr;
  SERVER_PORT = atoi(argv[2]);

  printf("2 : create a TCP socket\n");
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock<0){
     printf("socket call failed\n");
     exit(2);
  }

  printf("3 : fill server_addr with server's IP and PORT#\n");
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = SERVER_IP;
  server_addr.sin_port = htons(SERVER_PORT);

  // Connect to server
  printf("4 : connecting to server ....\n");
  r = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (r < 0){
     printf("connect failed\n");
     exit(1);
  }

  printf("5 : connected OK to \007\n"); 
  printf("---------------------------------------------------------\n");
  printf("hostname=%s  IP=%d  PORT=%d\n", 
          hp->h_name, inet_ntoa(SERVER_IP), SERVER_PORT);
  printf("---------------------------------------------------------\n");

  printf("========= init done ==========\n");
}

// TODO: Keon's
int lcat(char filename[])
{
  FILE *file = fopen(filename,"r");
  long fileSize = ftell(file);
  char *buffer = (char*) malloc(sizeof(char)*fileSize);
  
  buffer = (char*)fread(buffer, 1, fileSize,file);
  printf("%s",buffer);
  printf("\n");
  
  fclose(file);
  free(buffer);
  return 0;
}
int lpwd(char filename[])
{
	
}
int lls(char filename[])
{
	
}
int lcd(char filename[])
{
	
}
// TODO: Keon's                                                                                       
int myPut(char *pathname)
{
  FILE *file = fopen(pathname, "r");
  char *buffer = (char*)malloc(sizeof(char)*MAX);

  if(file==0)
    return 0;
  while(fread(buffer, 1, MAX, file) >= MAX)
    {
      sendMessage("%s",buffer);
    }
  sendMessage("%s",EOS);
  return 0;
}

int myget(char *pathname)
{
  sendMessage("%s",pathname);
}
// TODO: Keon's
int lmkdir(char filename[])
{
  if(mkdir(filename, 777) == 0)
    {
      printf("created successfully\n");
    }
}

// TODO: Keon's
int lrmdir(char filename[])
{
  if(rmdir(filename) == 0)
    {
      printf("%s created successfully!\n", filename);
    }
}
int lrm(char filename[])
{
  if(unlink(filename) == 0)
    {
      printf("removed dir %s successfully!\n",filename);
    }
}

int readMessage(char *msg)
{
	// keep reading line from server until EOS is received
  n = read(sock, msg, MAX);
  while(strcmp(msg, EOS))
  {
    printf("received: %s\n", msg);
    n = read(sock, msg, MAX);
  }
}

int sendMessage(char msg[], ...)
{
  // Send ENTIRE line to server
  n = write(sock, msg, MAX);
  printf("sent: %s\n", msg);
}
 
