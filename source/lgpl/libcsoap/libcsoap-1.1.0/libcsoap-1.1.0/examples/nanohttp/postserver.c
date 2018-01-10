/******************************************************************
*  $Id: postserver.c 254826 2013-01-10 12:29:18Z akosteltsev $
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
#include <nanohttp/nanohttp-server.h>

#include <stdio.h>
/*
	Please ignore this file. This is just for me to test 
	some features and new functions. In the future this
	file will also be good start to learn nanohttp
*/
static 
void _print_binary_ascii(int n)
{
  int i,c=0;
  char ascii[36];

  for (i=0;i<32;i++) {
    ascii[34-i-c] = (n & (1<<i))?'1':'0';
    if ((i+1)%8 == 0) {
        c++;
        ascii[i+c] = ' ';
    }
  }

  ascii[35]='\0';

  log_verbose2("%s", ascii);
}


static 
void _print_binary_ascii2(unsigned char n)
{
  int i,c=0;
  char ascii[9];

  for (i=0;i<8;i++) {
    ascii[7-i] = (n & (1<<i))?'1':'0';
  }

  ascii[8]='\0';

  log_verbose2("%s", ascii);
}


void echomime_service(httpd_conn_t *conn, hrequest_t *req)
{
  part_t    *part;
  int status;
  char   *content_type , *transfer_encoding, 
         *content_id,  *root_content_type;

	if (!req->attachments || !req->content_type) 
	{
		httpd_send_header(conn, 200, "OK");
		http_output_stream_write_string(conn->out, "<html><body><h1>");
		http_output_stream_write_string(conn->out, 
		  "You do not posted a MIME message!<hr></h1></body></html>");
		return;
	}
	else
	{

	  root_content_type = hpairnode_get(req->content_type->params, "type");

	  status = 
	     httpd_mime_send_header(conn, req->attachments->root_part->id, "",
	      root_content_type, 200, "OK");

	  if (status != H_OK)
	   return;

	  part = req->attachments->parts;
	  while (part)
	  {
	     content_id = hpairnode_get(part->header, HEADER_CONTENT_ID);
	     content_type = hpairnode_get(part->header, HEADER_CONTENT_TYPE);
	     transfer_encoding = hpairnode_get(part->header, HEADER_TRANSFER_ENCODING);
	     status = httpd_mime_send_file(conn, content_id, 
	           content_type, transfer_encoding, part->filename);
	     if (status != H_OK)
	       return;
	     part = part->next;
	  }	  

	  httpd_mime_end(conn);
	}
		
}

/*
SERVICE: http://host:port/postserver
*/
void post_service(httpd_conn_t *conn, hrequest_t *req)
{
	unsigned char *postdata;
	long received, total=0;
	unsigned int tmp;
	char buffer[15];
	hpair_t *pair;
/*
	postdata = httpd_get_postdata(conn, req, &received, -1);
*/
	if (req->method == HTTP_REQUEST_POST) {

		httpd_send_header(conn, 200, "OK");
		http_output_stream_write_string(conn->out, "<html><body>\n");
		http_output_stream_write_string(conn->out, "<h3>You Posted:</h3><hr>\n");
		while (http_input_stream_is_ready(req->in))
		{
			received = http_input_stream_read(req->in, buffer, 10);
			http_output_stream_write(conn->out, buffer, received);
			total += received;
		}
		http_output_stream_write_string(conn->out, "<h3>Received size</h3><hr>\n");
		sprintf(buffer, "%d", total);
		http_output_stream_write_string(conn->out, buffer);

		_print_binary_ascii2(postdata[0]);
		_print_binary_ascii2(postdata[1]);
		_print_binary_ascii2(postdata[2]);
		_print_binary_ascii2(postdata[3]);
	/*	free(postdata);*/

	} else {

		httpd_send_header(conn, 200, "OK");
		http_output_stream_write_string(conn->out, "<html><body>");
		http_output_stream_write_string(conn->out, "<form action=\"/postserver\" method=\"POST\">");
		http_output_stream_write_string(conn->out, "Enter Postdata: <input name=\"field\" type=\"text\">");
		http_output_stream_write_string(conn->out, "<input type=\"submit\">");
		
	}

	http_output_stream_write_string(conn->out, "<hr><p><small>Content-Type:");
	if (req->content_type)
	{
  	http_output_stream_write_string(conn->out, req->content_type->type);
		http_output_stream_write_string(conn->out, "<br>");
		pair = req->content_type->params;
		while (pair)
		{
  		http_output_stream_write_string(conn->out, pair->key);
  		http_output_stream_write_string(conn->out, "=");
  		http_output_stream_write_string(conn->out, pair->value);
  		http_output_stream_write_string(conn->out, "<br>");
		  pair = pair->next;
		}
  }
  else
  {
		http_output_stream_write_string(conn->out, "Not available");
  }

	http_output_stream_write_string(conn->out, "</body></html>");

	
}

int main(int argc, char *argv[])
{
	log_set_level(HLOG_VERBOSE);

	if (httpd_init(argc, argv)) {
		fprintf(stderr, "can not init httpd");
		return 1;
	}

	if (!httpd_register("/postserver", post_service)) {
		fprintf(stderr, "Can not register service");
		return 1;
	}

	if (!httpd_register("/axis/services/urn:EchoAttachmentsService", echomime_service)) {
		fprintf(stderr, "Can not register service");
		return 1;
	}

	if (httpd_run()) {
		fprintf(stderr, "can not run httpd");
		return 1;
	}

	httpd_destroy();

#ifdef MEM_DEBUG
  _mem_report();
#endif

	return 0;
}
