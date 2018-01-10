
#include "utils.h"


int Writer_Tab = 0;
int Writer_Ret = 0;

void Writer_StartElement(const char* element_name, int attr_count, char **keys, char **values, void* userData)
{
  int i, j;
  if (Writer_Ret) printf("\n");
  for (j=0;j<Writer_Tab;j++) printf("\t");
  printf("<%s", element_name);
  for (i=0;i<attr_count;i++)
  {
    printf(" %s = \"%s\"", keys[i], values[i]);
  }
  printf(">");
  Writer_Tab++;
  Writer_Ret = 1;
}

void Writer_Characters(const char* element_name, const char* chars, void* userData)
{
  printf("%s", chars);
}

void Writer_EndElement(const char* element_name, void* userData)
{
  int j;
  Writer_Tab--;
  if (!Writer_Ret)
    for (j=0;j<Writer_Tab;j++) printf("\t");
  printf("</%s>\n", element_name);
  Writer_Ret = 0;
}

