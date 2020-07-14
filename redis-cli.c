#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "redis_client.h"

char *ask_cmd(int conn_status)
{
  if (conn_status < 0)
  {
    printf("Not Connected $ ");
  }
  else
  {
    printf(RED_HOST_ADDR ":" RED_HOST_PORT " $ ");
  }

  char *cmd = calloc(255, 1);
  gets(cmd);
  return cmd;
}

int main(void)
{
  int sockfd = create_connection();

  while (1)
  {
    char *cmd = ask_cmd(sockfd);
    sockfd = create_connection();

    int l = strlen(cmd);
    char *n_cmd = calloc(l + 2, 1);
    strcpy(n_cmd, cmd);
    n_cmd[l] = '\r';
    n_cmd[l + 1] = '\n';

    send(sockfd, n_cmd, l + 2, 0);

    char buffer[256];
    bzero(buffer, 256);

    recv(sockfd, buffer, 255, 0);

    printf("%s", buffer);
  }

  return 0;
}
