
#ifndef _EX_UTILS_H_
#define _EX_UTILS_H_


void Writer_StartElement(const char* element_name, int attr_count, char **keys, char **values, void* userData);
void Writer_Characters(const char* element_name, const char* chars, void* userData);
void Writer_EndElement(const char* element_name, void* userData);


#endif
