#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "redis_client.h"

int main(void)
{
  int sockfd = create_connection();

  write(sockfd, "PING\r\n", 8);

  char buffer[256];
  bzero(buffer, 256);

  read(sockfd, buffer, 255);

  printf("%s", buffer);

  return 0;
}
