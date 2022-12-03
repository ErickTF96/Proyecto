/* Cliente del micro servidor web 2 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include "uici.c"

#define BLKSIZE  1024

typedef struct{
  int id;
  char nombre[20];
  float precio;
} Producto;



void usr1handler(int s)
{
   fprintf(stderr, "SIGUSR1 signal caught\n");
}
 
void usr2handler(int s)
{
   fprintf(stderr, "SIGUSR2 signal caught\n");
}
 
 
void installusrhandlers()
{
    struct  sigaction  newact;
    newact.sa_handler = usr1handler;      /* set the new usr1 handler */
    sigemptyset(&newact.sa_mask);    /* no additional signals blocked */
    newact.sa_flags = 0;            /* nothing special on the options */
    if (sigaction(SIGUSR1, &newact, (struct sigaction *)NULL) == -1) {
       perror("Could not install SIGUSR1 signal handler");
       return;
    }
    newact.sa_handler = usr2handler;      /* set the new usr2 handler */
    if (sigaction(SIGUSR2, &newact, (struct sigaction *)NULL) == -1) {
       perror("Could not install SIGUSR2 signal handler");
       return;
    }
    fprintf(stderr,
       "Client process %ld set to use SIGUSR1 and SIGUSR2\n",
       (long)getpid());
}
 
int main(int argc, char *argv[])
/*
 *  This is a client test of UICI. It opens a connection
 *  to a machine specified by host and a port number.
 *  It reads a file from stdin in blocks of size BLKSIZE
 *  and outputs it to the connection.
 */
{
    u_port_t portnumber;
    int outfd;
    ssize_t bytesread;
    ssize_t byteswritten;
    char buf[BLKSIZE];
       
    if (argc != 3) {
        fprintf(stderr, "Usage: %s host port file\n", argv[0]);
        exit(1);
    }
       
    installusrhandlers();
 
    portnumber = (u_port_t)atoi(argv[2]);
 
    if ((outfd = u_connect(portnumber, argv[1])) < 0) {
       u_error("Unable to establish an Internet connection");
       exit(1);
    }
       
    fprintf(stderr, "Connection has been made to %s\n", argv[1]);
 
  //enviar una petición
  //printf("Url: %s\n", argv[2]);
  char *token, delimitador[5] = "/", *aux[50];
  char get[50] = "GET /", *http[5] = {" HTTP/1.1\r\n\r\n"};
  int i = 0;

   if (strcmp(argv[2], "8888") == 0 || strcmp(argv[2], "8888/") == 0){
      printf("INDEX\n");
   }else{

      token = strtok(argv[2], delimitador);
         while (token != NULL){
            //printf("%s\n", token);
            token = strtok(NULL, delimitador);
            aux[i] = token;
            i++;
         }

      strcat(get, aux[0]);
      strcat(get, http[0]);
      //printf("Soy Url: %s\n", get);
  }

  //char header[] = "GET / HTTP/1.1\r\n\r\n";
  char header2[10000];

  char html[100000] = {0}; 

   byteswritten = u_write(outfd, &get, sizeof(get) );

   send(outfd, get,strlen(get),0);

   //bytesread = u_read(outfd, &header2, sizeof(200) );
   //bytesread = u_read(outfd, &html, sizeof(1000) );
	
   //recv(outfd, header2, BUFSIZ, 0);
   recv(outfd, html, BUFSIZ, 0); 


   /* Escribir en pantalla */    
   //printf("\nEncabezado: %s \n",header2);   
   printf("\n\nContenido: %s\n",html);


   u_close(outfd);
   exit(0);
}



