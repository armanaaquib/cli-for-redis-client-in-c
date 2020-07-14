#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>

#include "redis_client.h"
#include "resp_parser.h"

#define RES_BUFF_SIZE 1024

void update_db(int *db, char *cmd, char *res);

char *ask_inp(int conn_status, int db)
{
  if (conn_status < 0)
  {
    printf("Not Connected");
  }
  else
  {
    printf(RED_HOST_ADDR ":" RED_HOST_PORT);
    if (db > 0)
    {
      printf("(%d)", db);
    }
  }
  printf(" $ ");

  char *inp = calloc(255, 1);
  gets(inp);
  return inp;
}

int main(void)
{
  int sockfd = create_connection();
  int db = 0;

  while (1)
  {
    char *inp = ask_inp(sockfd, db);

    if (strcmp(inp, "exit") == 0)
    {
      break;
    }

    char *cmd = make_cmd(inp);

    send(sockfd, cmd, strlen(cmd), 0);

    char buffer[RES_BUFF_SIZE];
    bzero(buffer, RES_BUFF_SIZE);

    if (recv(sockfd, buffer, RES_BUFF_SIZE - 1, 0) <= 0)
    {
      sockfd = create_connection();
      send(sockfd, cmd, strlen(cmd), 0);
      recv(sockfd, buffer, RES_BUFF_SIZE - 1, 0);
    }

    parse_and_show(buffer);
    update_db(&db, cmd, buffer);
  }

  return 0;
}

void update_db(int *db, char *cmd, char *res)
{
  if (strncasecmp(cmd, "select", 6) == 0)
  {
    if (strncasecmp(res + 1, "ok", 2) == 0)
    {
      int n_db = atoi(cmd + 7);
      *db = n_db;
    }
  }
}
