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
