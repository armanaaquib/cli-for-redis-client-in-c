#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "resp_parser.h"

char *make_cmd(char *inp)
{
  int len = strlen(inp);
  char *cmd = calloc(len + 2, 1);

  strcpy(cmd, inp);
  cmd[len] = '\r';
  cmd[len + 1] = '\n';

  return cmd;
}

void parse_and_show(char *res)
{
  char resp_type = res[0];

  if (resp_type == '+' || resp_type == '-')
  {
    char *response = res;
    response++;
    printf("%s", response);
  }

  else if (resp_type == ':')
  {
    char *response = res;
    response++;
    printf("%d\r\n", atoi(response));
  }

  else
  {
    printf("%s", res);
  }
}
