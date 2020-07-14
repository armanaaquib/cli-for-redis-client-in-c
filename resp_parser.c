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

int parse_len(char *res)
{
  char *pos = strchr(res, '\n');

  *pos = '\0';
  int len = atoi(res + 1);

  *pos = '\n';
  return len;
}

void parse_and_show(char *buffer)
{
  char resp_type = buffer[0];
  char *res = buffer;

  if (resp_type == ':')
  {
    res++;
    printf("(integer) %d\r\n", atoi(res));
    return;
  }

  if (resp_type == '+' || resp_type == '-')
  {
    res++;
  }

  if (resp_type == '$')
  {
    int len = parse_len(res);

    if (len == -1)
    {
      res = "(nil)\r\n";
    }
    else
    {
      res = strchr(res, '\n');
      res++;
    }
  }

  if (resp_type == '*')
  {
    int len = parse_len(res);

    if (len == -1)
    {
      res = "(nil)\r\n";
    }

    else if (len == 0)
    {
      res = "(empty list)\r\n";
    }

    else
    {
      res = strchr(res, '\n');
      res++;

      for (size_t i = 0; i < len; i++)
      {
        char type = res[0];
        int no_of_steps = 1;

        if ((type == '$' || type == '*') && parse_len(res) >= 0)
        {
          no_of_steps = 2;
        }

        char *temp = res;
        for (size_t i = 0; i < no_of_steps; i++)
        {
          temp = strchr(temp, '\n');
          temp++;
        }

        char old_char = *temp;
        *temp = '\0';

        parse_and_show(res);
        *temp = old_char;
        res = temp;
      }
    }
  }

  printf("%s", res);
}
