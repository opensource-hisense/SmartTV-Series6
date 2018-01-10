/******************************************************************
*  $Id: client_post_chunked.c 254826 2013-01-10 12:29:18Z akosteltsev $
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



int main(int argc, char *argv[])
{
	httpc_conn_t *conn; /* Client connection object */
	hresponse_t *res; /* Response object **/
	char postdata[1054];

	/* Check usage */
	if (argc < 2) {
		fprintf(stderr, "usage %s <url> \n", argv[0]);
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

	/* Set header for chunked transport */
	httpc_set_header(conn, HEADER_TRANSFER_ENCODING, TRANSFER_ENCODING_CHUNKED);

	/* POSTing will be done in 3 steps
	 1. httpc_post_begin()
	 2. http_output_stream_write() 
	 3. httpc_post_end()
	*/

	/* (1) First step begin the post request*/
	if (httpc_post_begin(conn, argv[1]) != HSOCKET_OK)
	{
		log_error1("Can not begin posting\n");
		httpc_free(conn);
		exit(1);
	}

	/* (2) Post some data*/
	while (1)
	{
		 printf("\nEnter post data (max 1054). [Type '.' to end]: ");
		 gets(postdata);
		 if (!strcmp(postdata, "."))
		    break;
		 else if (http_output_stream_write(conn->out, postdata, strlen(postdata))
		     != HSOCKET_OK )
		 {
    		log_error1("Can not post\n");
    		httpc_free(conn);
    		exit(1);
		 }   
	}

	/* (3) End POSTing data and receive the response */
	printf("\nReceiving ... \n ");
	res = httpc_post_end(conn);
	if (res == NULL)
	{
	  log_error2("Error: %s", conn->errmsg);
	  httpc_free(conn);
	  exit(1);
	}

	show_response(res);

  /* Clean up */
	hresponse_free(res);
	httpc_free(conn);

	return 0;
}





