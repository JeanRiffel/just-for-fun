#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
  int server_fd, client_fd;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);  
  int port = 8080;
  char buffer[1024];
  
  server_fd = socket(AF_INET,  SOCK_STREAM, 0);
  if(server_fd == -1){
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port); 
  
  if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  
  if(listen(server_fd, 1) < 0){
    perror("listend failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", port);

  client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
  if (client_fd < 0){
    perror("accept failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Client connected \n");

  int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
  if(bytes >0){
    buffer[bytes] = '\0';
    printf("Received from client: \n%s\n", buffer);
  }

  close(client_fd);
  close(server_fd);

  return 0;
}