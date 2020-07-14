#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "redis_client.h"

struct sockaddr_in get_redis_server(void)
{
  struct sockaddr_in redis_server;
  bzero(&redis_server, sizeof(redis_server));

  redis_server.sin_family = AF_INET;
  redis_server.sin_addr.s_addr = inet_addr(RED_HOST_ADDR);
  redis_server.sin_port = htons(RED_HOST_PORT);

  return redis_server;
}

int create_connection()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
  {
    perror("ERROR opening socket");
    exit(1);
  }

  const struct sockaddr_in redis_server = get_redis_server();

  if (connect(sockfd, (const struct sockaddr *)&redis_server, sizeof(redis_server)) < 0)
  {
    perror("ERROR connecting");
    exit(1);
  }

  return sockfd;
}
