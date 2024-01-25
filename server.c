#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

typedef struct {
 char phrase[256];
} Phrase;


int main() {

  int server_socket,client_socket;
  struct sockaddr_in server_address,client_address;
  char buffer[BUFFER_SIZE] = {0};
  if((server_socket = socket(AF_INET,SOCK_STREAM,0))==-1) {
    perror("Server creation failed");
    exit(EXIT_FAILURE);
  }
  server_address.sin_family= AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);
  
  if(bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address)) == -1) {
     perror("Bind failed");
     exit(EXIT_FAILURE);
     
  }
  
  if(listen(server_socket,5)==-1) {
     perror("Listen failed");
     exit(EXIT_FAILURE);
  }
  
  printf("Server listening on port %d ... \n",PORT);
  
  socklen_t client_address_len = sizeof(client_address);
  
  if((client_socket=accept(server_socket,(struct sockaddr*) & client_address,&client_address_len))==-1) 
  {
     perror("Accept failed");
     exit(EXIT_FAILURE);
  }
  printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
  
  while(1) {
     memset(buffer,0,sizeof(buffer));
     if(recv(client_socket,buffer,sizeof(buffer),0) <= 0) {
        perror("Receive failed");

     }
     
     
     printf("Received message %s\n",buffer);
     
  
    
     
  }
  
  close(server_socket);
  close(client_socket);
  
  
}
