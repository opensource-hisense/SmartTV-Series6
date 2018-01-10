/* soapclient.c
// compile with
// gcc soapclient.c -o soapclient -lcsoap
*/
/* Author: Adrianus Warmenhoven */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <nanohttp/nanohttp-logging.h>
#include <libcsoap/soap-client.h>

#define MAX_LINE_LENGTH 65535

/* stripcslashes - unescapes the string */
void
stripcslashes(char *str, int *len)
{
  char *source, *target, *end;
  int nlen = *len, i;
  char numtmp[4];

  for (source = str, end = str + nlen, target = str; source < end; source++)
  {
    if (*source == '\\' && source + 1 < end)
    {
      source++;
      switch (*source)
      {
      case 'n':
        *target++ = '\n';
        nlen--;
        break;
      case 'r':
        *target++ = '\r';
        nlen--;
        break;
      case 'a':
        *target++ = '\a';
        nlen--;
        break;
      case 't':
        *target++ = '\t';
        nlen--;
        break;
      case 'v':
        *target++ = '\v';
        nlen--;
        break;
      case 'b':
        *target++ = '\b';
        nlen--;
        break;
      case 'f':
        *target++ = '\f';
        nlen--;
        break;
      case '\\':
        *target++ = '\\';
        nlen--;
        break;
      case 'x':
        if (source + 1 < end && isxdigit((int) (*(source + 1))))
        {
          numtmp[0] = *++source;
          if (source + 1 < end && isxdigit((int) (*(source + 1))))
          {
            numtmp[1] = *++source;
            numtmp[2] = '\0';
            nlen -= 3;
          }
          else
          {
            numtmp[1] = '\0';
            nlen -= 2;
          }
          *target++ = (char) strtol(numtmp, NULL, 16);
          break;
        }
      default:
        i = 0;
        while (source < end && *source >= '0' && *source <= '7' && i < 3)
        {
          numtmp[i++] = *source++;
        }
        if (i)
        {
          numtmp[i] = '\0';
          *target++ = (char) strtol(numtmp, NULL, 8);
          nlen -= i;
          source--;
        }
        else
        {
          *target++ = *source;
          nlen--;
        }
      }
    }
    else
    {
      *target++ = *source;
    }
  }

  if (nlen != 0)
    *target = '\0';
  *len = nlen;
}

/* ParseLine - gets a line, finds the commas, unescapes the value and adds it
//   to the SOAP request
*/
void
ParseLine(SoapCtx * ctx, char *Buffer, int LineLen)
{
  char *Line, *FirstCommaPos, *SecondCommaPos;
  int len;

  /* if wrong line length, return */
  if (LineLen <= 0)
    return;

  /* alloc buffer for the line, copy it */
  Line = (char *) malloc(LineLen + 1);
  memcpy(Line, Buffer, LineLen);
  Line[LineLen] = '\0';

  /* find first comma */
  FirstCommaPos = strchr(Line, ',');
  if (!FirstCommaPos)
    return;

  /* find second comma */
  SecondCommaPos = strchr(FirstCommaPos + 1, ',');
  if (!SecondCommaPos)
    return;

  /* separate the three strings */
  FirstCommaPos[0] = '\0';
  SecondCommaPos[0] = '\0';

  /* unescape */
  len = strlen(SecondCommaPos + 1);
  stripcslashes(SecondCommaPos + 1, &len);

  /* add to the request */
  soap_env_add_item(ctx->env, Line, FirstCommaPos + 1, SecondCommaPos + 1);

  /* free the buffer */
  free(Line);
}

void
printusage(char *FileName)
{
  printf("Usage: %s [URL] [URN] [SOAPMETHOD]\n\n", FileName);
  printf("- [URL] is the url of the SOAP server.\n");
  printf("- [URN] is the namespace for the method/webservice.\n");
  printf("- [SOAPMETHOD] is the method to call.\n\n");
  printf("All commandline paramaters are mandatory.\n\n");
  printf
    ("%s reads the parameters for the SOAPMETHOD from STDIN as a comma-separated list\n\n",
     FileName);
  printf("Each line is one parameter and has the following form:\n\n");
  printf("xsd:[TYPE],[PARAMETERNAME],[PARAMETERVALUE]\n\n");
  printf
    ("- [TYPE] is a basic type for SOAP or a complex type defined by the WSDL.\n");
  printf
    ("- [PARAMETERNAME] is the name for the parameter of the SOAPMETHOD on this line.\n");
  printf
    ("- [PARAMETERVALUE] is the value for the parameter. N.B. \nand other escapes are recognized.\n");
}

int
main(int argc, char *argv[])
{
  SoapCtx *ctx, *ctx2;
  herror_t err;

  /* create buffer */
  char Buffer[MAX_LINE_LENGTH];
  long bytes_read, bytes_left;

  char *EndLinePos;

  /* check the parameter count */
  if (argc != 4)
  {
    printusage(argv[0]);
    return 1;
  }

  /* init cSOAP client */
  err = soap_client_init_args(argc, argv);
  if (err != H_OK)
  {
    log_error4("%s():%s [%d]", herror_func(err),
               herror_message(err), herror_code(err));
    herror_release(err);
    return 1;
  }

  /* create a SoapCtx object */
  err = soap_ctx_new_with_method(argv[2], argv[3], &ctx);
  if (err != H_OK)
  {
    log_error4("%s():%s [%d]", herror_func(err),
               herror_message(err), herror_code(err));
    herror_release(err);
    return 1;
  }

  /* read from stdin until EOF */
  while (!feof(stdin))
  {
    bytes_read = fread(Buffer, 1, MAX_LINE_LENGTH, stdin);

    /* pass each line into ParseLine */
    while ((EndLinePos = strchr(Buffer, '\n')))
    {
      ParseLine(ctx, Buffer, EndLinePos - Buffer);
      memmove(Buffer, EndLinePos + 1, bytes_read - (EndLinePos - Buffer + 1));
      Buffer[bytes_read - (EndLinePos - Buffer + 1)] = '\0';
    }

    /* no '\n' found in the whole Buffer, that means line's too */ 
    bytes_left = strlen(Buffer);
    if (bytes_left == MAX_LINE_LENGTH)
    {
      log_error1("The parameter line is too long.");
      herror_release(err);
      soap_ctx_free(ctx);
      return 1;
    }
  }

  /* invoke */
  err = soap_client_invoke(ctx, &ctx2, argv[1], "");
  if (err != H_OK)
  {
    log_error4("[%d] %s(): %s ", herror_code(err),
               herror_func(err), herror_message(err));
    herror_release(err);
    soap_ctx_free(ctx);
    return 1;
  }

  /* print the result */
  soap_xml_doc_print(ctx2->env->root->doc);

  /* free the objects */
  soap_ctx_free(ctx2);
  soap_ctx_free(ctx);

  /* destroy the cSOAP client */
  soap_client_destroy();

  return 0;
}
