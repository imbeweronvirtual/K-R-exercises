#include <stdio.h>
#include <stdbool.h>

#define MAXLINE 1000 /* max input line size */
char line[MAXLINE];   /* current input line */

int custom_getline(void);  /* from K&R */

int main(void)
{
    int len;
    int i;
    int brace = 0, bracket = 0, parenthesis = 0;
    int s_quote = 1, d_quote = 1;
    int in_escape = 0;
    bool in_multistrings_comment = false;
    
    while ((len = custom_getline()) > 0)
    {
      bool in_s_quotes = false;
      bool in_d_quotes = false;
      i = 0;
      
      while (i < len)
      {
        char c = line[i];
        char next_char = (i + 1 < len) ? line[i + 1] : '\0';

        if (in_d_quotes && c != '"')
        {
            i++;
            continue;
        } else if (in_s_quotes && c != '\'')
        {
            i++;
            continue;
        }

        if (in_multistrings_comment)
        {
            if (c == '*' && next_char == '/')
            {
              in_multistrings_comment = false;
              i += 2;
            } else
            {
                i++;
                continue;
            }
        }
        
        if (c == '/')
        {
          if (next_char == '/')
          {
            break;
          }
          else if (next_char == '*')
          {
            in_multistrings_comment = true;
            i++;
            continue;
          }
        }
        
        if (c == '"')
        {
          in_d_quotes = !in_d_quotes;
          d_quote *= -1;
        } else if (c == '\'')
        {
            in_s_quotes = !in_s_quotes;
            s_quote *= - 1;
        } else if (c == '[')
        {
            bracket++;
        } else if (c == ']')
        {
            bracket--;
        } else if (c == '{')
        {
            brace++;
        } else if (c == '}')
        {
            brace--;
        } else if (c == '(')
        {
            parenthesis++;
        } else if (c == ')')
        {
            parenthesis--;
        } else if (c == '\\' && !in_d_quotes && !in_s_quotes)
        {
            if (i + 2 < len)
            {
                i += 2;
                continue;
            } else
            {
                break;
            }      
        }
        
        i++;
      }
    }

    if (d_quote != 1)
        printf("Mismatching double-quote mark\n");
    if (s_quote != 1)
        printf("Mismatching single-quote mark\n");
    if (parenthesis != 0)
        printf("Mismatching parenthesis\n");
    if (brace != 0)
        printf("Mismatching brace mark\n");
    if (bracket != 0)
        printf("Mismatching bracket mark\n");
    if (bracket == 0 && brace == 0 && parenthesis == 0 && s_quote == 1 && d_quote == 1)
    {
        printf("Syntax appears to be correct.\n");
    }
    return 0;
}


int custom_getline(void)
{
    int c, i;

    for (i = 0; i < MAXLINE-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        line[i] = c;
    }

    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}