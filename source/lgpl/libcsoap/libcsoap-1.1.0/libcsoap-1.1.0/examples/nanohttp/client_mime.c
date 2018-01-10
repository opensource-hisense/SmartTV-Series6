/******************************************************************
*  $Id: client_mime.c 254826 2013-01-10 12:29:18Z akosteltsev $
*
* CSOAP Project:  A http client/server library in C (example)
* Copyright (C) 2003  Ferhat Ayaz
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA  02111-1307, USA.
* 
* Email: ferhatayaz@yahoo.com
******************************************************************/
#include <nanohttp/nanohttp-client.h>

#include <stdio.h>

#define MAX_BUFFER_SIZE 1024

static
void show_response(hresponse_t *res)
{
  hpair_t *pair;
  byte_t buffer[MAX_BUFFER_SIZE+1];
  int read;
	if (res == NULL) 
	{
	 log_error1("Response is NULL!");
	 return;
	}
	
  log_info2("Spec  : '%s'", res->spec);
  log_info2("Status: %d", res->errcode);
  log_info2("Desc  : '%s'", res->desc);

  pair = res->header;
  while (pair != NULL) {
		log_debug3("%s: %s", pair->key, pair->value);
		pair = pair->next;
	}

	if (res->in == NULL)
	{
	  log_warn1("No input stream!");
	  return;
	}

	
	while (http_input_stream_is_ready(res->in))
	{
	  read = http_input_stream_read(res->in, buffer, MAX_BUFFER_SIZE);
	  buffer[read] = '\0';
	  puts(buffer);
	}

}



static
int send_file(httpc_conn_t *conn, const char* filename, 
    const char* id, const char* content_type)
{
  int status, size;
  FILE *f = fopen(filename, "r");
  char buffer[MAX_BUFFER_SIZE];

  if (f == NULL)
  {
    log_error2("can not open file: '%s'", filename);
    return 0;
  }

	status = httpc_mime_next(conn, id, content_type, "binary");
	if (status != HSOCKET_OK) 
	 return status;
	
 	while (!feof(f)) {
 	  size = fread(buffer, 1, MAX_BUFFER_SIZE, f);
 	  if (size == -1)
 	  {
 	      log_error1("Can not read file!");
 	      fclose(f);
 	      return 0;
 	  }
 	  status = http_output_stream_write(conn->out, buffer, size);
 	  if (status != HSOCKET_OK) 
 	  {
 	    log_error1("Can not send data!");
 	    fclose(f);
	    return 0;
 	  }
 	}

 	fclose(f);
 	return 1;
}

int main(int argc, char *argv[])
{
	httpc_conn_t *conn; /* Client connection object */
	hresponse_t *res; /* Response object **/

	int status;
	FILE *f;
	size_t size;
	char url[50], file[50], id[50], content_type[50];
	
	char buffer[MAX_BUFFER_SIZE+1];


	/* Check usage */
	if (argc < 5) {
		fprintf(stderr, "usage %s <url> <file> <id> <content-type>\n", argv[0]);
		exit(1);
	}

	/* Set log level to see more information written by the library */
	log_set_level(HLOG_VERBOSE);

	/* Initialize httpc module */
	if (httpc_init(argc, argv))
	{
	 log_error1("Can not init httpc");
	 return 1;
	}

	/* Create the client connection object */
	conn = httpc_new();

	httpc_set_header(conn, "SOAPAction", "\"\"");
	httpc_set_header(conn, HEADER_TRANSFER_ENCODING, TRANSFER_ENCODING_CHUNKED);

	/*
	 Open connection for mime
	 */
	status = httpc_mime_begin(conn, argv[1], argv[3], "", argv[4]);
	if (status != HSOCKET_OK)
	{
	  log_error2("Can not start MIME: %d", status);
	  exit(1);
	}

	if (!send_file(conn,  argv[2], argv[3], argv[4]))
	 return 1;

	while (1)
	{
	  printf("Enter filename ['.' for finish]: ");
	  gets(file);
	  if (!strcmp(file, "."))
	     break;

	  printf("Enter part id:");
	  gets(id);
	  printf("Enter content-type:");
	  gets(content_type);

	  if (!send_file(conn, file, id, content_type))
	     return 1;
	}

 	res = httpc_mime_end(conn);

 	/* Show response */
	show_response(res);

	/* clean up*/
	hresponse_free(res);
	httpc_free(conn);
	return 0;
}



