#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

#include "redis_client.h"
#include "resp_parser.h"

#define RES_BUFF_SIZE 1024

char *ask_inp(int conn_status)
{
  if (conn_status < 0)
  {
    printf("Not Connected $ ");
  }
  else
  {
    printf(RED_HOST_ADDR ":" RED_HOST_PORT " $ ");
  }

  char *inp = calloc(255, 1);
  gets(inp);
  return inp;
}

int main(void)
{
  int sockfd = create_connection();

  while (1)
  {
    char *cmd = make_cmd(ask_inp(sockfd));
    sockfd = create_connection();

    send(sockfd, cmd, strlen(cmd), 0);

    char buffer[RES_BUFF_SIZE];
    bzero(buffer, RES_BUFF_SIZE);

    recv(sockfd, buffer, RES_BUFF_SIZE - 1, 0);

    printf("%s", buffer);
  }

  return 0;
}
