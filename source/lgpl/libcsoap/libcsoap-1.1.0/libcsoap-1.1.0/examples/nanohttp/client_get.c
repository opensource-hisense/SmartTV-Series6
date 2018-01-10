/******************************************************************
*  $Id: client_get.c 254826 2013-01-10 12:29:18Z akosteltsev $
*
* CSOAP Project:  A http client/server library in C (example)
* Copyright (C) 2003-2004  Ferhat Ayaz
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
#define MEM_DEBUG
#include <stdio.h>
#include <nanohttp/nanohttp-client.h>

#ifdef MEM_DEBUG
#include <utils/alloc.h>
#endif

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

	/* check usage */
	if (argc < 2) {
		fprintf(stderr, "usage %s <url>\n", argv[0]);
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
	
  /* Send GET method and receive response */
	res = httpc_get(conn, argv[1]);

	/* Show response */
	show_response(res);

	/* Clean up */
	hresponse_free(res);
	httpc_free(conn);

#ifdef MEM_DEBUG
  _mem_report();
#endif
	
	return 0;
}

