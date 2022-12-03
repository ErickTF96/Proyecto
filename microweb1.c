#include "compres2.h"
#include "microweb1.h"
#include "e4_base64_VF.h"

int main (int argc, char *argv[]) {

    int server_sockfd;
    int client_sockfd;
    int len, pid;
    struct sockaddr_in server_addr;   
    struct sockaddr_in remote_addr; 
    int sin_size;
    char buf[BUFSIZ];
    int ret; 
    struct stat sb;

  
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 



    server_addr.sin_port = htons(8888); 


    if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket failed\n");
        exit(0);
    }

   
    if (bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("bind failed\n");
        exit(0);
    }


 
    listen(server_sockfd, 5);
    sin_size = sizeof(struct sockaddr_in);

   printf("En espera de conexiones..\n");

    while(1)
    {
      
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &remote_addr, &sin_size);
       
       
        if (client_sockfd < 0)
        {
            perror("failed on accept");
        }

        pid = fork();
        if (pid < 0)
        {
            perror("failed on fork");
        }

        //El proceso hijo atiende la peticio web
        if (pid == 0)
        {
            close(server_sockfd);
            char header[] = "HTTP/1.0 200 OK\r\n\r\n";
            char error[] = "HTTP/Error 404!\r\n\r\n";

            //crear arreglo del tamaño necesario
             //validar antes de leer
            char html[100000] = {0}; //antes 1024+1024*10
            

            recv(client_sockfd, buf, BUFSIZ, 0);
            printf("Soy buffer: %s\n", buf);

            char *token, *delimitador[5] = {" ","/","."}, delimitador2[5]= "/";
            char url[50]= ".", *aux[50], *aux2[5], *compresExt[5] = {".compres"};
            int i = 0;

            token = strtok(buf, delimitador[0]);
            while (token != NULL){
                //printf("%s\n", token);
                token = strtok(NULL, delimitador[0]);
                aux[i] = token;
                i++;
            }

            strcat(url, aux[0]);
            printf("Soy Url: %s\n", url);
            i = 0;
            token = strtok(url, delimitador2);
            while (token != NULL){
                //printf("%s\n", token);
                token = strtok(NULL, delimitador2);
                aux2[i] = token;
                i++;
            }
            char mydco[1024] = "";
            char myb64[1024] = "";
            char mydst[1024] = "";


            char *files[5] = {"0",aux2[0]};
            strcat(aux2[0], compresExt[0]);
            files[2] = aux2[0];
            printf("Soy file1: %s\n", files[1]);
            printf("Soy file2: %s\n", files[2]);
           
            //leer el archivo enviado en el encabezado GET
            //read_file(url, html);
            if (strcmp(url, ".") == 0 || strcmp(url, "./") == 0){
                read_file("./index.html", html); 
                b64_encode(html, myb64);
                send(client_sockfd, myb64,strlen(html),0);       
            }
            else if (read_file(url, html)){
                b64_encode(html, myb64);
                // printf("La cadena\n[%s]\nse codifica en base64 como:\n[%s]\n", html, myb64);
                // printf("\n");

                //send(client_sockfd, myb64, strlen(html), 0);
                send(client_sockfd, myb64,strlen(html),0);
            }else{
                read_file("./error.html", html);
                send(client_sockfd, error, strlen(error),0);
                printf("Archivo no encontrado\n");
            }

            close(client_sockfd);
            exit(0);
        }

        if(pid>0){
          int status;
          //waitpid(pid, &status, 0);
          close(client_sockfd);
        }
    
    } 
    close(server_sockfd);



    return 0;
}
