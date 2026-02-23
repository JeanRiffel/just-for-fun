#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){

  int server_fd, client_fd;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  char buffer[2048];

  server_fd = socket(AF_INET, SOCK_STREAM, 0);  

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  bind(server_fd, (struct sockaddr *)&address, sizeof(address));
  listen(server_fd, 1);

  printf("HTTP SERVER RUNNING ON http://localhost:%d\n", PORT);

  client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);

  int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
  buffer[bytes] = '\0';

  printf("Request receveid: \n%s\n", buffer);

  char *response = "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 18\r\n"
        "\r\n"
        "Hello HTTP World!";
  

  send(client_fd, response, strlen(response), 0);

  close(client_fd);
  close(server_fd);

  return 0;

}
